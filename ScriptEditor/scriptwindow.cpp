#include "scriptwindow.h"
#include "ui_scriptwindow.h"

ScriptWindow::ScriptWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScriptWindow)
{
    ui->setupUi(this);
}

ScriptWindow::~ScriptWindow()
{
    delete ui;
}
