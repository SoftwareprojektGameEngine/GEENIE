#include "inspector.h"
#include "ui_inspector.h"

Inspector::Inspector(QWidget *parent, QUuid id, QUuid parentId) :
    InspectorParentWidget(parent,id,parentId),
    ui(new Ui::Inspector)
{
    ui->setupUi(this);
}

Inspector::~Inspector()
{
    delete ui;
}
