#include "npwizard.h"
#include "ui_npwizard.h"

NPWizard::NPWizard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NPWizard)
{
    ui->setupUi(this);
}

NPWizard::~NPWizard()
{
    delete ui;
}
