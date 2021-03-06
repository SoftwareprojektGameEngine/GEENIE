#include "geeniemainwindow.h"
#include "ui_geeniemainwindow.h"
#include "exitdialog.h"
#include "sceneeditwidget.h"

#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>
#include <QFileDialog>
GEENIEMainWindow::GEENIEMainWindow(EngineWrapper* engine, QWidget *parent) :
    QMainWindow(parent),
    _projectSaved(true),
    _projectConfigured(false),
    ui(new Ui::GEENIEMainWindow)
{
    ui->setupUi(this);

    QProcessEnvironment env(QProcessEnvironment::systemEnvironment());
    this->userprofile = env.value("USERPROFILE") + "\\" + "GEENIE";

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    ui->scriptEditor->setFont(font);
    ui->scriptEditor->setStyleSheet(QString("background-color: black;color: white;"));
    ui->comboBox->addItem(QString("Python"));
    ui->comboBox->addItem(QString("Lua"));
    ui->comboBox->setCurrentIndex(0);

    //engineWidget = geenie->getEngine()->CreateWidget();
    //engineWidget->GetWidget()->setParent(this);
    _sceneEditWidget = new SceneEditWidget(engine);
    auto layout = new QVBoxLayout();
    layout->addWidget(_sceneEditWidget);
    layout->setContentsMargins(0,0,0,0);
    _sceneEditWidget->setLayout(layout);

    ui->tabWidget->addTab(_sceneEditWidget, QString("SceneEdit"));//engineWidget->GetWidget(), QString("scene edit"));
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
}

GEENIEMainWindow::~GEENIEMainWindow()
{
    delete ui;
}

void GEENIEMainWindow::closeEvent(QCloseEvent *event)
{
    emit onClose();
    if(!_projectSaved)
    {
        QMessageBox::StandardButton sBtn = QMessageBox::question(this,tr("Unsaved changes"),
                                                                 tr("There are unsaved changes.\nWould you like to save them before closing?"),
                                                                 QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                                                 QMessageBox::Yes);
        if(sBtn == QMessageBox::Yes)
        {
            emit saveProject();
        }
        else if(sBtn == QMessageBox::Cancel)
        {
            event->ignore();
            return;
        }
    }
#ifdef CAT_EXIT
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, tr("GEENIE"),
                                                                tr("Are you sure you want to leave?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn == QMessageBox::Cancel)
    {
        event->ignore();
    }
    else if (resBtn == QMessageBox::Yes)
    {
        emit saveSession();
        event->accept();
    }
    else if (resBtn == QMessageBox::No)
    {
        ExitDialog exitDialog;
        if(exitDialog.exec() == QDialog::Accepted)
        {
            event->ignore();
        }
        else
        {
            emit saveSession();
            event->accept();
        }
    }
#else
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, tr("GEENIE"),
                                                                tr("Are you sure you want to leave?\n"),
                                                                QMessageBox::Cancel | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn == QMessageBox::Cancel)
    {
        event->ignore();
    }
    else if (resBtn == QMessageBox::Yes)
    {
        emit saveSession();
        event->accept();
    }
#endif
}

QTextDocument* GEENIEMainWindow::scriptEditorDocument()
{
    return ui->scriptEditor->document();
}

void GEENIEMainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0)
    {
        emit changeScriptType(Highlighter::Types::Python);
    }
    else
    {
        emit changeScriptType(Highlighter::Types::Lua);
    }
}

void GEENIEMainWindow::setScriptType(Highlighter::Types type)
{
    if(type == Highlighter::Types::Python)
    {
        ui->comboBox->setCurrentIndex(0);
    }
    else
    {
        ui->comboBox->setCurrentIndex(1);
    }
}

void GEENIEMainWindow::setScript(QString &script)
{
    ui->scriptEditor->setText(script);
}

void GEENIEMainWindow::on_actionExit_triggered()
{
    close();
}

#include <QFileDialog>
#include <QDir>
#include <QDebug>

void GEENIEMainWindow::on_openScriptBtn_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,QString("Load Script ..."),QDir::homePath(),QString("Scripts (*.lua *.py)"));
    if(!file.isEmpty())
    {
        QFile scriptFile(file);
        if(scriptFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString script = QString::fromUtf8(scriptFile.readAll());
            setScript(script);
            scriptFile.close();
        }
    }
}

void GEENIEMainWindow::on_saveScriptBtn_clicked()
{
    QString file = QFileDialog::getSaveFileName(this,QString("Save Script ..."),QDir::homePath(),QString("Scripts (*.lua *.py)"));
    if(!file.isEmpty())
    {
        QFile scriptFile(file);
        if(scriptFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream ts(new QString(),QIODevice::Text);
            ts.setDevice(&scriptFile);
            ts << ui->scriptEditor->document()->toPlainText();
            scriptFile.close();
        }
    }
}

void GEENIEMainWindow::setDockActionsChecked(EDockWidgetTypes type, bool checked)
{
    switch(type)
    {
    case EDockWidgetTypes::InspectorWidget:
    {
        ui->actionInspector->setChecked(checked);
        break;
    }
    case EDockWidgetTypes::EntitiesWidget:
    {
        ui->actionExplorer->setChecked(checked);
        break;
    }
    case EDockWidgetTypes::AssetsWidget:
    {
        ui->actionAssets->setChecked(checked);
        break;
    }
    case EDockWidgetTypes::LoggerWidget:
    {
        ui->actionConsole_2->setChecked(checked);
        break;
    }
    case EDockWidgetTypes::ScriptEditorWidget:
    default: break;
    }
}

#include <QDebug>

void GEENIEMainWindow::on_actionInspector_toggled(bool arg1)
{
    emit toggleDock(EDockWidgetTypes::InspectorWidget,arg1);
}

void GEENIEMainWindow::on_actionConsole_2_toggled(bool arg1)
{
    emit toggleDock(EDockWidgetTypes::LoggerWidget,arg1);
}

void GEENIEMainWindow::on_actionExplorer_toggled(bool arg1)
{
    emit toggleDock(EDockWidgetTypes::EntitiesWidget,arg1);
}

void GEENIEMainWindow::on_actionAssets_toggled(bool arg1)
{
    emit toggleDock(EDockWidgetTypes::AssetsWidget,arg1);
}

void GEENIEMainWindow::on_actionRedo_triggered()
{
    emit redo();
}

void GEENIEMainWindow::on_actionUndo_triggered()
{
    emit undo();
}

void GEENIEMainWindow::CanRedo(bool redo)
{
    ui->actionRedo->setEnabled(redo);
}

void GEENIEMainWindow::CanUndo(bool undo)
{
    ui->actionUndo->setEnabled(undo);
}

void GEENIEMainWindow::on_actionSave_triggered()
{
    emit saveLayout();
}

void GEENIEMainWindow::on_actionLoad_triggered()
{
    emit loadLayout();
}

#include "newdialog.h"
void GEENIEMainWindow::on_actionNew_triggered()
{
    emit checkIfProjectConfigured();
    NewDialog nd(this,_projectConfigured);
    if(nd.exec() == QDialog::Accepted)
    {
        if(nd.type())
        {
            emit newProject();
        }
        else
        {
            emit newScene();
        }
    }
}

void GEENIEMainWindow::setProjectSaved(bool saved)
{
    _projectSaved = saved;
}

void GEENIEMainWindow::setProjectConfigured(bool configured)
{
    _projectConfigured = configured;
}

void GEENIEMainWindow::on_actionLoad_default_layout_triggered()
{
    emit setLayoutToDefault();
}

void GEENIEMainWindow::on_actionOpen_2_triggered()
{
    emit onClose();
    if(!_projectSaved)
    {
        QMessageBox::StandardButton sBtn = QMessageBox::question(this,tr("Unsaved changes"),
                                                                 tr("There are unsaved changes.\nWould you like to save them before closing?"),
                                                                 QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                                                 QMessageBox::Yes);
        if(sBtn == QMessageBox::Yes)
        {
            emit saveProject();
        }
        else if(sBtn == QMessageBox::Cancel)
        {
            return;
        }
    }


    QString file = QFileDialog::getOpenFileName(this,QString("Load project ..."),this->userprofile,QString("GEENIE project files (*.geenie)"));
    if(file.isEmpty())
    {
        return;
    }
    emit loadProject(file);
}

void GEENIEMainWindow::on_actionSave_As_triggered()
{
    emit checkIfProjectConfigured();
    if(!_projectConfigured)return;
    QFileDialog dia;
    dia.setNameFilter("GEENIE project file (*.geenie)");
    dia.setDirectory(this->userprofile);
    dia.setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
    //dia.setLabelText(0,"Select project file");
    dia.setFileMode(QFileDialog::AnyFile);

    if(dia.exec() == QDialog::Rejected)
    {
        return;
    }
    else
    {
        if(dia.selectedFiles().at(0) == QString(""))
        {
            ERROR_MSG("Save as: Empty File path.");
        }
        emit saveProject(dia.selectedFiles().at(0));
    }
}

void GEENIEMainWindow::on_actionSave_2_triggered()
{
    emit checkIfProjectConfigured();
    if(!_projectConfigured)return;
    emit saveProject();
}

void GEENIEMainWindow::on_actionCreate_triggered()
{
    emit createAsset();
}


void GEENIEMainWindow::on_actionDelete_triggered()
{
    emit deleteAsset();
}

void GEENIEMainWindow::on_actionClose_Project_triggered()
{
    if(!_projectSaved)
    {
        QMessageBox::StandardButton sBtn = QMessageBox::question(this,tr("Unsaved changes"),
                                                                 tr("There are unsaved changes.\nWould you like to save them before closing?"),
                                                                 QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                                                 QMessageBox::Yes);
        if(sBtn == QMessageBox::Yes)
        {
            emit saveProject();
        }
        else if(sBtn == QMessageBox::Cancel)
        {
            return;
        }
    }
    emit closeProject();
}

void GEENIEMainWindow::on_LoadTemplateButton_clicked()
{
    QString script = "--Declare your variables here\n--Put your code here";
    setScript(script);
}
