#include "inspectorwidget.h"
#include "ui_inspectorwidget.h"
#include <QVBoxLayout>
#include <QDebug>

InspectorWidget::InspectorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InspectorWidget)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout(ui->scrollAreaWidgetContents));
    t = ui->treeWidget;

    InitializeTree();
}
void InspectorWidget::InitializeTree()
{
    t->setColumnCount(2);
    t->setColumnWidth(0,100);
    t->setColumnWidth(1,100);
    SetHeaderText("Property", "Values");


   // t->setStyleSheet("QTreeWidget::item { border-bottom: 1px solid black; border-top: 1px solid black; border-right: 1px solid black;border-left: 1px solid black;}");
}

InspectorWidget::~InspectorWidget()
{
    delete ui;
}

void InspectorWidget::addWidget(QWidget *widget)
{
    widget->setParent(ui->scrollAreaWidgetContents);
    widget->setGeometry(widget->x(),widget->y(),ui->scrollAreaWidgetContents->width(),widget->height());
    ui->scrollAreaWidgetContents->layout()->addWidget(widget);
}
void InspectorWidget::removeWidget(QWidget* widget)
{
    ui->scrollAreaWidgetContents->layout()->removeWidget(widget);
}

void InspectorWidget::resizeSlot(int h, int w)
{
    setGeometry(this->x(),this->y(),w,h);
}

#include <QDebug>

void InspectorWidget::FillTree(Entity *e, bool sub)
{

    if(!sub)
    {
        ui->treeWidget->clear();
    }
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setFlags(itm->flags() | Qt::ItemIsEditable);
    itm->setText(0,"Entity");
    itm->setText(1,e->name());
    itm->setData(1,Qt::UserRole,e->GetID().toByteArray());

    QHashIterator<QUuid, Component*> it = e->GetComponents();
    while(it.hasNext())
    {
        it.next();
        QTreeWidgetItem *c = new QTreeWidgetItem();
        Component *comp = it.value();
        c->setFlags(c->flags() | Qt::ItemIsEditable);
        c->setText(0,comp->GetTypeName());
        c->setData(1,Qt::UserRole,comp->GetID().toByteArray());
        c->setData(1,Qt::UserRole+1,e->GetID().toByteArray());
        c->setText(1,comp->name());
        switch(comp->GetType())
        {
        default:
            break;
        }
        itm->addChild(c);
    }
    QHashIterator<QUuid, Entity*> it2 = e->GetSubEntities();
    while(it2.hasNext())
    {
        it2.next();
        FillTree(it2.value(),true);
    }
}
void InspectorWidget::SetHeaderText(QString text1, QString text2)
{
    QTreeWidgetItem *header = t->headerItem();
    header->setText(0,text1);
    header->setText(1,text2);
}


void InspectorWidget::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(column == 0)
    {
        return;
    }
    ui->treeWidget->editItem(item,column);
}

void InspectorWidget::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    if(column == 0)
    {
        return;
    }
    if(item->data(1,Qt::UserRole+1) == QVariant()) // Entity name changed
    {
        emit RenameEntity(QUuid(item->data(1,Qt::UserRole).toByteArray()),item->data(1,Qt::DisplayRole).toString());
    }
    else // Component name changed
    {

    }

}
