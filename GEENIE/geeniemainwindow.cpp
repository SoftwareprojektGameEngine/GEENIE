#include "geeniemainwindow.h"
#include "ui_geeniemainwindow.h"
#include "exitdialog.h"

#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>

GEENIEMainWindow::GEENIEMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GEENIEMainWindow)
{
    ui->setupUi(this);
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    ui->scriptEditor->setFont(font);
    ui->scriptEditor->setStyleSheet(QString("background-color: black;color: white;"));
    ui->comboBox->addItem(QString("Python"));
    ui->comboBox->addItem(QString("Lua"));
    ui->comboBox->setCurrentIndex(0);
}

GEENIEMainWindow::~GEENIEMainWindow()
{
    delete ui;
}

void GEENIEMainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, tr("GEENIE"),
                                                                tr("Are you sure?\n"),
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
