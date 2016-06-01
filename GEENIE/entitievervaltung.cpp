#include "entitievervaltung.h"
#include "ui_entitievervaltung.h"
#include "core.h"
#include <QDebug>

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
