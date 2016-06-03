#include "inspector.h"
#include "ui_inspector.h"

Inspector::Inspector(QWidget *parent, QUuid id) :
    InspectorParentWidget(parent,id),
    ui(new Ui::Inspector)
{
    ui->setupUi(this);
}

Inspector::~Inspector()
{
    delete ui;
}
