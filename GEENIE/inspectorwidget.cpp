#include "inspectorwidget.h"
#include "ui_inspectorwidget.h"
#include <QVBoxLayout>
#include <QDebug>

InspectorWidget::InspectorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InspectorWidget)
{
    ui->setupUi(this);
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

void InspectorWidget::resizeSlot(int h, int w)
{
    setGeometry(this->x(),this->y(),w,h);
}

#include <QDebug>

QTreeWidgetItem* InspectorWidget::VectorToItem(Vector v)
{
    QTreeWidgetItem* vector = new QTreeWidgetItem();
    QTreeWidgetItem* x = new QTreeWidgetItem(vector);
    x->setText(0,QString("X"));
    x->setData(1,Qt::DisplayRole,v.x);
    QTreeWidgetItem* y = new QTreeWidgetItem(vector);
    y->setText(0,QString("Y"));
    y->setData(1,Qt::DisplayRole,v.y);
    QTreeWidgetItem* z = new QTreeWidgetItem(vector);
    z->setText(0,QString("Z"));
    z->setData(1,Qt::DisplayRole,v.z);
    QTreeWidgetItem* w = new QTreeWidgetItem(vector);
    w->setText(0,QString("W"));
    w->setData(1,Qt::DisplayRole,v.w);
    return vector;
}

QTreeWidgetItem* InspectorWidget::ColorToItem(Color c)
{
    QTreeWidgetItem* color = new QTreeWidgetItem();
    QTreeWidgetItem* r = new QTreeWidgetItem(color);
    r->setText(0,QString("R"));
    r->setData(1,Qt::DisplayRole,c.r);
    QTreeWidgetItem* g = new QTreeWidgetItem(color);
    g->setText(0,QString("G"));
    g->setData(1,Qt::DisplayRole,c.g);
    QTreeWidgetItem* b = new QTreeWidgetItem(color);
    b->setText(0,QString("B"));
    b->setData(1,Qt::DisplayRole,c.b);
    QTreeWidgetItem* a = new QTreeWidgetItem(color);
    a->setText(0,QString("Alpha"));
    a->setData(1,Qt::DisplayRole,c.a);
    return color;
}

void InspectorWidget::FillTree(Entity *entity, bool sub)
{

    if(!sub)
    {
        ui->treeWidget->clear();
    }
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setFlags(itm->flags() | Qt::ItemIsEditable);
    itm->setText(0,"Entity");
    itm->setText(1,entity->name());
    itm->setData(1,Qt::UserRole,entity->GetID().toByteArray());

    QHashIterator<QUuid, Component*> it = entity->GetComponents();
    while(it.hasNext())
    {
        it.next();
        QTreeWidgetItem *c = new QTreeWidgetItem();
        Component *comp = it.value();
        c->setFlags(c->flags() | Qt::ItemIsEditable);
        c->setText(0,comp->GetTypeName());
        c->setData(0,Qt::UserRole,(int)comp->GetType());
        c->setData(1,Qt::UserRole,comp->GetID().toByteArray());
        c->setData(1,Qt::UserRole+1,entity->GetID().toByteArray());
        c->setText(1,comp->name());
        switch(comp->GetType())
        {
        case ComponentType::MODEL:
        {
            break;
        }
        case ComponentType::MATERIAL:
        {
            break;
        }
        case ComponentType::POSITION:
        {
            PositionComponent* co = dynamic_cast<PositionComponent*>(comp);
            QTreeWidgetItem* prop = VectorToItem(co->GetPosition());
            prop->setText(0,QString("Position"));
            c->addChild(prop);
            break;
        }
        case ComponentType::LIGHT:
        {
            LightComponent* co = dynamic_cast<LightComponent*>(comp);
            QTreeWidgetItem* ambient = ColorToItem(co->GetAmbientColor());
            ambient->setText(0,QString("Ambient"));
            c->addChild(ambient);
            QTreeWidgetItem* diffuse = ColorToItem(co->GetDiffuseColor());
            diffuse->setText(0,QString("Diffuse"));
            c->addChild(diffuse);
            QTreeWidgetItem* specular = ColorToItem(co->GetSpecularColor());
            specular->setText(0,QString("Specular"));
            c->addChild(specular);
            QTreeWidgetItem* prop = VectorToItem(co->GetSpotlightDirection());
            prop->setText(0,QString("Spotlight"));
            c->addChild(prop);
            QTreeWidgetItem* sourceType = new QTreeWidgetItem(c);
            sourceType->setText(0,QString("Light source type"));
            sourceType->setData(1,Qt::DisplayRole,(int)co->GetLightSourceType());
            break;
        }
        case ComponentType::TEXTURE:
        {
            break;
        }
        case ComponentType::SOUND:
        {
            break;
        }
        case ComponentType::SHADER:
        {
            break;
        }
        case ComponentType::SCRIPT:
        {
            break;
        }
        default:
            break;
        }
        itm->addChild(c);
    }
    QHashIterator<QUuid, Entity*> it2 = entity->GetSubEntities();
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
void InspectorWidget::clear()
{
    ui->treeWidget->clear();
}
