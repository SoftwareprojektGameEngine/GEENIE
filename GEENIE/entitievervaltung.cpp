#include "entitievervaltung.h"
#include "ui_entitievervaltung.h"

Entitievervaltung::Entitievervaltung(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Entitievervaltung)
{
    ui->setupUi(this);
}

Entitievervaltung::~Entitievervaltung()
{
    delete ui;
}
