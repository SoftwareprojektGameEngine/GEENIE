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
    b = false;
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

void InspectorWidget::VectorToItem(QTreeWidgetItem* vector, Vector v)
{
    //QTreeWidgetItem* vector = new QTreeWidgetItem();
    QTreeWidgetItem* x = new QTreeWidgetItem(vector);
    x->setText(0,QString("X"));
    x->setData(1,Qt::DisplayRole,v.x);

    x->setData(0, Qt::UserRole, vector->data(0, Qt::UserRole));
    x->setData(0, Qt::UserRole+1, vector->data(0, Qt::UserRole+1));
    x->setData(0, Qt::UserRole+2, vector->data(0, Qt::UserRole+2));
    x->setData(1, Qt::UserRole, vector->data(1, Qt::UserRole));
    x->setData(1, Qt::UserRole+1, vector->data(1, Qt::UserRole+1));
    x->setData(1, Qt::UserRole+2, 0);

    QTreeWidgetItem* y = new QTreeWidgetItem(vector);
    y->setText(0,QString("Y"));
    y->setData(1,Qt::DisplayRole,v.y);

    y->setData(0, Qt::UserRole, vector->data(0, Qt::UserRole));
    y->setData(0, Qt::UserRole+1, vector->data(0, Qt::UserRole+1));
    y->setData(0, Qt::UserRole+2, vector->data(0, Qt::UserRole+2));
    y->setData(1, Qt::UserRole, vector->data(1, Qt::UserRole));
    y->setData(1, Qt::UserRole+1, vector->data(1, Qt::UserRole+1));
    y->setData(1, Qt::UserRole+2, 1);

    QTreeWidgetItem* z = new QTreeWidgetItem(vector);
    z->setText(0,QString("Z"));
    z->setData(1,Qt::DisplayRole,v.z);

    z->setData(0, Qt::UserRole, vector->data(0, Qt::UserRole));
    z->setData(0, Qt::UserRole+1, vector->data(0, Qt::UserRole+1));
    z->setData(0, Qt::UserRole+2, vector->data(0, Qt::UserRole+2));
    z->setData(1, Qt::UserRole, vector->data(1, Qt::UserRole));
    z->setData(1, Qt::UserRole+1, vector->data(1, Qt::UserRole+1));
    z->setData(1, Qt::UserRole+2, 2);

    QTreeWidgetItem* w = new QTreeWidgetItem(vector);
    w->setText(0,QString("W"));
    w->setData(1,Qt::DisplayRole,v.w);

    w->setData(0, Qt::UserRole, vector->data(0, Qt::UserRole));
    w->setData(0, Qt::UserRole+1, vector->data(0, Qt::UserRole+1));
    w->setData(0, Qt::UserRole+2, vector->data(0, Qt::UserRole+2));
    w->setData(1, Qt::UserRole, vector->data(1, Qt::UserRole));
    w->setData(1, Qt::UserRole+1, vector->data(1, Qt::UserRole+1));
    w->setData(1, Qt::UserRole+2, 3);

    //return vector;
}

void InspectorWidget::ColorToItem(QTreeWidgetItem* color, Color c)
{
    //QTreeWidgetItem* color = new QTreeWidgetItem();
    QTreeWidgetItem* r = new QTreeWidgetItem(color);
    r->setText(0,QString("R"));
    r->setData(1,Qt::DisplayRole,c.r);

    r->setData(0, Qt::UserRole, color->data(0, Qt::UserRole));
    r->setData(0, Qt::UserRole+1, color->data(0, Qt::UserRole+1));
    r->setData(0, Qt::UserRole+2, color->data(0, Qt::UserRole+2));
    r->setData(1, Qt::UserRole, color->data(1, Qt::UserRole));
    r->setData(1, Qt::UserRole+1, color->data(1, Qt::UserRole+1));
    r->setData(1, Qt::UserRole+2, 0);

    QTreeWidgetItem* g = new QTreeWidgetItem(color);
    g->setText(0,QString("G"));
    g->setData(1,Qt::DisplayRole,c.g);

    g->setData(0, Qt::UserRole, color->data(0, Qt::UserRole));
    g->setData(0, Qt::UserRole+1, color->data(0, Qt::UserRole+1));
    g->setData(0, Qt::UserRole+2, color->data(0, Qt::UserRole+2));
    g->setData(1, Qt::UserRole, color->data(1, Qt::UserRole));
    g->setData(1, Qt::UserRole+1, color->data(1, Qt::UserRole+1));
    g->setData(1, Qt::UserRole+2, 1);

    QTreeWidgetItem* b = new QTreeWidgetItem(color);
    b->setText(0,QString("B"));
    b->setData(1,Qt::DisplayRole,c.b);

    b->setData(0, Qt::UserRole, color->data(0, Qt::UserRole));
    b->setData(0, Qt::UserRole+1, color->data(0, Qt::UserRole+1));
    b->setData(0, Qt::UserRole+2, color->data(0, Qt::UserRole+2));
    b->setData(1, Qt::UserRole, color->data(1, Qt::UserRole));
    b->setData(1, Qt::UserRole+1, color->data(1, Qt::UserRole+1));
    b->setData(1, Qt::UserRole+2, 2);

    QTreeWidgetItem* a = new QTreeWidgetItem(color);
    a->setText(0,QString("Alpha"));
    a->setData(1,Qt::DisplayRole,c.a);

    a->setData(0, Qt::UserRole, color->data(0, Qt::UserRole));
    a->setData(0, Qt::UserRole+1, color->data(0, Qt::UserRole+1));
    a->setData(0, Qt::UserRole+2, color->data(0, Qt::UserRole+2));
    a->setData(1, Qt::UserRole, color->data(1, Qt::UserRole));
    a->setData(1, Qt::UserRole+1, color->data(1, Qt::UserRole+1));
    a->setData(1, Qt::UserRole+2, 3);

    //return color;
}

void InspectorWidget::FillTree(Entity *entity, bool sub)
{
    b = false;
    if(!sub)
    {
        ui->treeWidget->clear();
    }
    if(entity == nullptr) return;
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setFlags(itm->flags() | Qt::ItemIsEditable);
    itm->setText(0,"Entity");
    itm->setText(1,entity->name());

    itm->setData(0, Qt::UserRole, 0);
    itm->setData(0, Qt::UserRole+1, entity->GetID().toByteArray());
    itm->setData(1, Qt::UserRole, -1);

    //itm->setData(1,Qt::UserRole,entity->GetID().toByteArray());

    QHashIterator<QUuid, Component*> it = entity->GetComponents();
    while(it.hasNext())
    {
        it.next();
        QTreeWidgetItem *c = new QTreeWidgetItem();
        Component *comp = it.value();

        c->setFlags(c->flags() | Qt::ItemIsEditable);
        c->setText(0,comp->GetTypeName());

        c->setData(0, Qt::UserRole, 1);
        c->setData(0, Qt::UserRole+1, entity->GetID().toByteArray());
        c->setData(0, Qt::UserRole+2, comp->GetID().toByteArray());
        c->setData(1, Qt::UserRole, (int)comp->GetType());
        c->setData(1, Qt::UserRole+1, -1);
        c->setData(1, Qt::UserRole+2, -1);
        //c->setData(0,Qt::UserRole,(int)comp->GetType());
        //c->setData(1,Qt::UserRole,comp->GetID().toByteArray());
        //c->setData(1,Qt::UserRole+1,entity->GetID().toByteArray());
        c->setText(1,comp->name());
        c->setExpanded(true);

        switch(comp->GetType())
        {
        case ComponentType::MODEL:
        {
        }
            break;
        case ComponentType::MATERIAL:
        {
        }
            break;
        case ComponentType::POSITION:
        {
            PositionComponent* co = dynamic_cast<PositionComponent*>(comp);
            c->setData(1, Qt::UserRole+1, 0);
            VectorToItem(c, co->GetPosition());
            c->setData(1, Qt::UserRole+1, -1);
            c->setExpanded(true);
        }
            break;
        case ComponentType::LIGHT:
        {
            LightComponent* co = dynamic_cast<LightComponent*>(comp);

            if((co->GetLightSourceType() & AMBIENT) != 0) {
                QTreeWidgetItem* ambient = new QTreeWidgetItem(c); //ColorToItem(co->GetAmbientColor());
                ambient->setText(0,QString("Ambient"));

                ambient->setData(0, Qt::UserRole, 1);;
                ambient->setData(0, Qt::UserRole+1, entity->GetID().toByteArray());
                ambient->setData(0, Qt::UserRole+2, comp->GetID().toByteArray());
                ambient->setData(1, Qt::UserRole, (int)comp->GetType());
                ambient->setData(1, Qt::UserRole+1, 0);
                ambient->setData(1, Qt::UserRole+2, -1);

                ColorToItem(ambient, co->GetAmbientColor());
                c->addChild(ambient);
            }

            if((co->GetLightSourceType() & DIFFUSE) != 0) {
                QTreeWidgetItem* diffuse = new QTreeWidgetItem(c);
                diffuse->setText(0,QString("Diffuse"));

                diffuse->setData(0, Qt::UserRole, 1);;
                diffuse->setData(0, Qt::UserRole+1, entity->GetID().toByteArray());
                diffuse->setData(0, Qt::UserRole+2, comp->GetID().toByteArray());
                diffuse->setData(1, Qt::UserRole, (int)comp->GetType());
                diffuse->setData(1, Qt::UserRole+1, 1);
                diffuse->setData(1, Qt::UserRole+2, -1);

                ColorToItem(diffuse, co->GetDiffuseColor());
                c->addChild(diffuse);
            }

            if((co->GetLightSourceType() & SPECULAR) != 0) {
                QTreeWidgetItem* specular = new QTreeWidgetItem(c);
                specular->setText(0,QString("Specular"));

                specular->setData(0, Qt::UserRole, 1);;
                specular->setData(0, Qt::UserRole+1, entity->GetID().toByteArray());
                specular->setData(0, Qt::UserRole+2, comp->GetID().toByteArray());
                specular->setData(1, Qt::UserRole, (int)comp->GetType());
                specular->setData(1, Qt::UserRole+1, 2);
                specular->setData(1, Qt::UserRole+2, -1);

                ColorToItem(specular, co->GetSpecularColor());
                c->addChild(specular);
            } else if((co->GetLightSourceType() & SPOT) != 0) {
                QTreeWidgetItem* spotLightColor = new QTreeWidgetItem(c);
                spotLightColor->setText(0, QString("Spotlight color"));

                spotLightColor->setData(0, Qt::UserRole, 1);;
                spotLightColor->setData(0, Qt::UserRole+1, entity->GetID().toByteArray());
                spotLightColor->setData(0, Qt::UserRole+2, comp->GetID().toByteArray());
                spotLightColor->setData(1, Qt::UserRole, (int)comp->GetType());
                spotLightColor->setData(1, Qt::UserRole+1, 2);
                spotLightColor->setData(1, Qt::UserRole+2, -1);

                ColorToItem(spotLightColor, co->GetSpecularColor());
                c->addChild(spotLightColor);


                QTreeWidgetItem* prop = new QTreeWidgetItem(c);
                prop->setText(0,QString("Spotlight direction"));

                prop->setData(0, Qt::UserRole, 1);;
                prop->setData(0, Qt::UserRole+1, entity->GetID().toByteArray());
                prop->setData(0, Qt::UserRole+2, comp->GetID().toByteArray());
                prop->setData(1, Qt::UserRole, (int)comp->GetType());
                prop->setData(1, Qt::UserRole+1, 3);
                prop->setData(1, Qt::UserRole+2, -1);

                VectorToItem(prop, co->GetSpotlightDirection());
                c->addChild(prop);
            }

            QTreeWidgetItem* sourceType = new QTreeWidgetItem(c);
            sourceType->setText(0,QString("Light source type"));
            sourceType->setData(1,Qt::DisplayRole,(int)co->GetLightSourceType());

            sourceType->setData(0, Qt::UserRole, 1);;
            sourceType->setData(0, Qt::UserRole+1, entity->GetID().toByteArray());
            sourceType->setData(0, Qt::UserRole+2, comp->GetID().toByteArray());
            sourceType->setData(1, Qt::UserRole, (int)comp->GetType());
            sourceType->setData(1, Qt::UserRole+1, 4);
            sourceType->setData(1, Qt::UserRole+2, 0);
        }
            break;
        case ComponentType::TEXTURE:
        {
        }
            break;
        case ComponentType::SOUND:
        {
        }
            break;
        case ComponentType::SHADER:
        {
        }
            break;
        case ComponentType::SCRIPT:
        {
        }
            break;
        default:
            break;
        }

        bool inserted = false;
        for(int i = 0; i < itm->childCount(); i++) {
            if(c->data(1, Qt::DisplayRole).toString() < itm->child(i)->data(1, Qt::DisplayRole).toString()) {
                itm->insertChild(i, c);
                inserted = true;
                break;
            }
        }
        if(!inserted) itm->addChild(c);
    }
    QHashIterator<QUuid, Entity*> it2 = entity->GetSubEntities();
    while(it2.hasNext())
    {
        it2.next();
        FillTree(it2.value(),true);
    }

    itm->setExpanded(true);
    ui->treeWidget->expandAll();
    if(!sub) b = true;
}
void InspectorWidget::SetHeaderText(QString text1, QString text2)
{
    QTreeWidgetItem *header = t->headerItem();
    header->setText(0,text1);
    header->setText(1,text2);
}


void InspectorWidget::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item == nullptr)
    {
        return;
    }

    if(item->data(0, Qt::UserRole).toInt() == 0) {
        // Entity
    } else {
        // Component
        if(item->data(1, Qt::UserRole+1).toInt() == -1) return;

        switch(item->data(1, Qt::UserRole).toInt()) {
        case 2:
            break;
        case 3:
        {
            int index = item->data(1, Qt::UserRole+1).toInt();
            qDebug() << index;
            if(index == 3 || index == 4 || item->data(1, Qt::UserRole+2).toInt() == 3) {
                if(index == 3 && item->data(1, Qt::UserRole+2).toInt() == -1) return;
                Qt::ItemFlags flags = item->flags();
                item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                ui->treeWidget->editItem(item, 1);
                item->setFlags(flags);
                return;
            }

            QColorDialog colorDialog;
            //colorDialog.setCurrentColor(QColor());

            if(colorDialog.exec() == QDialog::Accepted) {
                auto compNode = item;
                while(compNode->data(1, Qt::UserRole+1).toInt() != -1) compNode = compNode->parent();
                qDebug() << compNode->data(0, Qt::DisplayRole);

                auto color = colorDialog.currentColor();

                Color ambientColor;
                Color diffuseColor;
                Color specularColor;
                Vector dir = Vector(0.f,0.f,0.f,0.f);
                LightSourceType type = (LightSourceType)compNode->child(compNode->childCount()-1)->data(1, Qt::DisplayRole).toInt();

                int attrIndex = 0;
                if((type & AMBIENT) != 0) {
#define GETCOLOR(colorVar, ind) \
                    if(item->data(1, Qt::UserRole+1).toInt() == (ind)) {\
                        colorVar.r = color.red() / 255.0f;\
                        colorVar.g = color.green() / 255.0f;\
                        colorVar.b = color.blue() / 255.0f;\
                    } else {\
                        colorVar.r = compNode->child(attrIndex)->child(0)->data(1, Qt::DisplayRole).toFloat();\
                        colorVar.g = compNode->child(attrIndex)->child(1)->data(1, Qt::DisplayRole).toFloat();\
                        colorVar.b = compNode->child(attrIndex)->child(2)->data(1, Qt::DisplayRole).toFloat();\
                    }\
                    colorVar.a = compNode->child(attrIndex)->child(3)->data(1, Qt::DisplayRole).toFloat();\
                    attrIndex++;
                    GETCOLOR(ambientColor, 0)
                }

                if((type & DIFFUSE) != 0) {
                    GETCOLOR(diffuseColor, 1)
                }

                if((type & SPECULAR) != 0) {
                    GETCOLOR(specularColor, 2)
                } else if((type & SPOT) != 0) {
                    dir.x = compNode->child(attrIndex+1)->child(0)->data(1, Qt::DisplayRole).toFloat();
                    dir.y = compNode->child(attrIndex+1)->child(1)->data(1, Qt::DisplayRole).toFloat();
                    dir.z = compNode->child(attrIndex+1)->child(2)->data(1, Qt::DisplayRole).toFloat();
                    dir.w = compNode->child(attrIndex+1)->child(3)->data(1, Qt::DisplayRole).toFloat();

                    GETCOLOR(specularColor, 2);
                }
#undef GETCOLOR

                LightComponent *lightComp = new LightComponent(type, ambientColor, diffuseColor, specularColor, dir);
                emit ModifyComponent(QUuid(item->data(0, Qt::UserRole+2).toByteArray()), QUuid(item->data(0, Qt::UserRole+1).toByteArray()), lightComp);
            }
            return;
        }
            break;
        default:
            return;
        }
    }

    Qt::ItemFlags flags = item->flags();
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    ui->treeWidget->editItem(item, 1);
    item->setFlags(flags);
    /*if(     item->text(0) == "R"
        ||  item->text(0) == "G"
        ||  item->text(0) == "B")
    {
        QColorDialog dia;
        if(dia.exec() == QDialog::Accepted)
        {
            QTreeWidgetItem *itm = item->parent();
            QTreeWidgetItem *child = itm->child(0);
            QColor color = dia.currentColor();

            child->setText(1,QString::number(color.red()));
            child = itm->child(1);
            child->setText(1,QString::number(color.green()));
            child = itm->child(2);
            child->setText(1,QString::number(color.blue()));

        }
    }
    else
    {
        if(item->text(0) == "Entity")
        {
            Qt::ItemFlags flag = item->flags();
            item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            ui->treeWidget->editItem(item,column);
            item->setFlags(flag);
        }
        else if(item->childCount() == 0
                && !(item->text(0) == "Model"
                    || item->text(0) == "Texture"
                    || item->text(0) == "Script"
                    || item->text(0) == "Material"
                    || item->text(0) == "Audio"
                    || item->text(0) == "Video"))
        {
            Qt::ItemFlags flag = item->flags();
            item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            ui->treeWidget->editItem(item,column);
            item->setFlags(flag);
        }
    }*/
}

void InspectorWidget::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    if(!b) return;
    if(column != 1) return;

    if(item->data(0, Qt::UserRole).toInt() == 0) {
        // Entity
        emit RenameEntity(QUuid(item->data(0, Qt::UserRole+1).toByteArray()), item->data(1, Qt::DisplayRole).toString());
    } else {
        // Component
        QUuid entityID = QUuid(item->data(0, Qt::UserRole+1).toByteArray());
        QUuid compID = QUuid(item->data(0, Qt::UserRole+2).toByteArray());

        switch (item->data(1, Qt::UserRole).toInt()) {
        case 2: // POSITION
        {
            if(item->data(1, Qt::UserRole+1).toInt() == -1) return;

            auto compNode = item;
            while(compNode->data(1, Qt::UserRole+1).toInt() != -1) compNode = compNode->parent();

            Vector pos;
            pos.x = compNode->child(0)->data(1, Qt::DisplayRole).toFloat();
            pos.y = compNode->child(1)->data(1, Qt::DisplayRole).toFloat();
            pos.z = compNode->child(2)->data(1, Qt::DisplayRole).toFloat();
            pos.w = compNode->child(3)->data(1, Qt::DisplayRole).toFloat();
            PositionComponent *pcomp = new PositionComponent(pos);

            //emit ModifyEntityComponent(entityID, compID, pcomp);
            emit ModifyComponent(compID, entityID, pcomp);
        }
            break;
        case 3: // LIGHT
        {
            if(item->data(1, Qt::UserRole+1).toInt() == -1) return;
            if(item->data(1, Qt::UserRole+1).toInt() == 4) {
                Color c = Color(0.f, 0.f, 0.f, 1.f);
                Vector v = Vector(0.f, 0.f, 0.f, 0.f);

                LightComponent *lightComp = new LightComponent((LightSourceType)item->data(1, Qt::DisplayRole).toInt(), c, c, c, v);
                emit ModifyComponent(compID, entityID, lightComp);
                return;
            }

            auto compNode = item;
            while(compNode->data(1, Qt::UserRole+1).toInt() != -1) compNode = compNode->parent();
            qDebug() << compNode->data(1, Qt::DisplayRole);

            Color ambient;
            Color diffuse;
            Color specular;
            Vector dir = Vector(0.f,0.f,0.f,0.f);

            LightSourceType type = (LightSourceType)compNode->child(compNode->childCount()-1)->data(1, Qt::DisplayRole).toInt();
            qDebug() << type;
            int attrIndex = 0;

#define clamp(a, b, c) ((a) < (b)) ? (b) : ((a) > (c)) ? (c) : (a)
#define GETCOLOR(colorVar) \
    colorVar.r = compNode->child(attrIndex)->child(0)->data(1, Qt::DisplayRole).toFloat();\
    colorVar.g = compNode->child(attrIndex)->child(1)->data(1, Qt::DisplayRole).toFloat();\
    colorVar.b = compNode->child(attrIndex)->child(2)->data(1, Qt::DisplayRole).toFloat();\
    colorVar.a = clamp(compNode->child(attrIndex)->child(3)->data(1, Qt::DisplayRole).toFloat(), 0.f, 1.f);\
    attrIndex++;

            if((type & AMBIENT) != 0) {
                qDebug() << "has ambient";
                GETCOLOR(ambient)
            }

            if((type & DIFFUSE) != 0) {
                qDebug() << "has diffuse";
                GETCOLOR(diffuse)
            }

            if((type & SPECULAR) != 0) {
                qDebug() << "has specular";
                GETCOLOR(specular)
            } else if((type & SPOT) != 0) {
                qDebug() << "has spot light";
                GETCOLOR(specular);

                dir.x = compNode->child(attrIndex)->child(0)->data(1, Qt::DisplayRole).toFloat();
                dir.y = compNode->child(attrIndex)->child(1)->data(1, Qt::DisplayRole).toFloat();
                dir.z = compNode->child(attrIndex)->child(2)->data(1, Qt::DisplayRole).toFloat();
                dir.w = compNode->child(attrIndex)->child(3)->data(1, Qt::DisplayRole).toFloat();
            }
#undef GETCOLOR
#undef clamp
            qDebug() << "collected data";
            LightComponent *lightComp = new LightComponent(type, ambient, diffuse, specular, dir);
            qDebug() << "light component created";
            emit ModifyComponent(compID, entityID, lightComp);
        }
            break;
        default:
            qDebug() << "entity: " << entityID;
            qDebug() << "component: " << compID;
            qDebug() << "component type: " << item->data(1, Qt::UserRole).toInt();
            qDebug() << "component index: " << item->data(1, Qt::UserRole+1).toInt();
            break;
        }
    }

    /*if(b)
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
    }*/
}
void InspectorWidget::clear()
{
    ui->treeWidget->clear();
}

Color InspectorWidget::ColorPicker()
{
    QColorDialog *dia = new QColorDialog(this);
    dia->exec();
    QColor col = dia->currentColor();
    Color color;
    color.a = col.alpha();
    color.b = col.blue();
    color.g = col.green();
    color.r = col.red();
    return color;

}
