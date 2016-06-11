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

    QTreeWidgetItem *itm = new QTreeWidgetItem();
    QTreeWidgetItem *child = new QTreeWidgetItem();
    child->setText(0,"Prop1");
    child->setText(1,"value1");
    itm->addChild(child);
    itm->setText(0,"Entity");
    itm->setText(1,"value1");
    t->addTopLevelItem(itm);
}
void InspectorWidget::InitializeTree()
{
    t->setColumnCount(2);
    t->setColumnWidth(0,100);
    t->setColumnWidth(1,100);
    SetHeaderText("Property", "Values");


    t->setStyleSheet("QTreeWidget::item { border-bottom: 1px solid black; border-top: 1px solid black; border-right: 1px solid black;border-left: 1px solid black;}");
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

void InspectorWidget::FillTree(Entity *e)
{

    QTreeWidgetItem *itm;
    itm->setText(1,"Entity");
    itm->setText(1,e->name());
    QHashIterator<QUuid, Component*> it = e->GetComponents();

    while(it.hasNext())
    {
        QTreeWidgetItem *c = new QTreeWidgetItem();
        Component *comp = it.value();
        switch(comp->GetType())
        {
        default:
            break;
        }
        itm->addChild(c);
        it.next();
    }
    QHashIterator<QUuid, Entity*> it2 = e->GetSubEntities();
}
void InspectorWidget::SetHeaderText(QString text1, QString text2)
{
    QTreeWidgetItem *header = t->headerItem();
    header->setText(0,text1);
    header->setText(1,text2);
}


void InspectorWidget::on_treeWidget_DoubleClicked(QTreeWidgetItem *item, int column)
{

}
