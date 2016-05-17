#include "geeniemainwindow.h"
#include "ui_geeniemainwindow.h"

#include <QMessageBox>
#include <QCloseEvent>

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
}

GEENIEMainWindow::~GEENIEMainWindow()
{
    delete ui;
}

void GEENIEMainWindow::on_pushButton_clicked()
{
    DEBUG_MSG(QString("Test DEBUG"));
    ERROR_MSG(QString("Test ERROR"));
}

void GEENIEMainWindow::on_pushButton_2_clicked()
{
    ERROR_MSG(QString("Test ERROR"));
}


void GEENIEMainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, tr("GEENIE"),
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        emit saveSession();
        event->accept();
    }
}

QTextDocument* GEENIEMainWindow::scriptEditorDocument()
{
    return ui->scriptEditor->document();
}
