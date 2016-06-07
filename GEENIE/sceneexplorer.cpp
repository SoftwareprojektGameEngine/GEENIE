#include "sceneexplorer.h"
#include "ui_sceneexplorer.h"
#include "core.h"
#include <QDebug>

//!Initializes the SceneExplorer.
SceneExplorer::SceneExplorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneExplorer)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(1);
	/* SceneExplorer Test
    SCENE_DATA scene;
    scene.sceneName = "Scene1";
    scene.sceneId = 0;

	ENTITY_DATA e;
	e.entityName = "Entity1";
	e.entityId = 0;

	ENTITY_DATA e2;
	e2.entityName = "Entity2";
	e2.entityId = 0;

	ENTITY_DATA e3;
	e3.entityName = "Entity3";
	e3.entityId = 0;

	COMPONENT_DATA c;
	c.componentName = "Comp1";
	c.entityId = 0;

	e.components.append(c);
	e2.components.append(c);
	e3.components.append(c);
	e2.entities.append(e3);
	e.entities.append(e2);
	scene.entities.append(e);
    QList<SCENE_DATA> scenes;
    scenes.append(scene);
	scene.sceneName = "Scene2";
	scenes.append(scene);

    FillTree(&scenes);*/
}

//!Cleans the used Storage.
SceneExplorer::~SceneExplorer()
{
    delete ui;
}

//!Sets the Title of the columns.
void SceneExplorer::setHeader(QString &name)
{
    ui->treeWidget->setHeaderLabel(name);
}



int SceneExplorer::FillTree(QList<SCENE_DATA> *scenes)
{
 //TODO: ERRORCODE
    if(scenes->count() == 0)
    {
        return 0;
    }
    for(int i=0; i<scenes->count();i++)
    {
        //Add new scene
        this->AddScene(scenes->at(i).sceneName, scenes->at(i).sceneId );

        //Add Entities with Components to Scene
        this->AddEntitys(this->ui->treeWidget->topLevelItem(i),scenes->at(i).entities);
    }
	return 0;
}

int SceneExplorer::AddScene(QString sceneName, QUuid sceneId)
{
    if(sceneName == "")
    {
        return SE_INVALID_NAME;
    }
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0,sceneName);
	itm->setData(0, Qt::UserRole, sceneId.toByteArray());
	itm->setData(0, Qt::UserRole + 1, false);
    ui->treeWidget->addTopLevelItem(itm);
	return 0;
}

int SceneExplorer::AddEntitys(QTreeWidgetItem *parent,QList<ENTITY_DATA> entities)
{
   for(int i=0 ; i<entities.count();i++)
   {
       QTreeWidgetItem *itm = new QTreeWidgetItem();
       itm->setText(0,entities.at(i).entityName);
	   itm->setData(0, Qt::UserRole, entities.at(i).entityId.toByteArray());
	   itm->setData(0, Qt::UserRole + 1, false);

	   parent->addChild(itm);

       //Add Components to Entity
       for(int j = 0; j<entities.at(i).components.count();j++)
       {
           QTreeWidgetItem *comp = new QTreeWidgetItem();
           comp->setText(0,entities.at(i).components.at(j).componentName);

		   itm->setData(0, Qt::UserRole, entities.at(i).components.at(j).componentId.toByteArray());
		   itm->setData(0, Qt::UserRole + 1, true);
		   itm->setData(0, Qt::UserRole + 2, entities.at(i).components.at(j).entityId.toByteArray());

		   parent->child(parent->indexOfChild(itm))->addChild(comp);
       }
       //Add SubEntitys recursivly
       AddEntitys(parent->child(parent->indexOfChild(itm)),entities.at(i).entities);
   }
   return 0;
}

void SceneExplorer::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if(column > 0)
    {
        return;
    }
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        if(item == ui->treeWidget->topLevelItem(i))
        {
            emit sceneClicked();
            return;
        }
    }
    if(item->data(0,Qt::UserRole+1).toBool())
    {
        emit clicked(QUuid(item->data(0,Qt::UserRole).toByteArray()),se::ItemType::COMPONENT,QUuid(item->data(0,Qt::UserRole+2).toByteArray()));
    }
    else
    {
        emit clicked(QUuid(item->data(0,Qt::UserRole).toByteArray()),se::ItemType::ENTITY);
    }
}

void SceneExplorer::clear()
{
    ui->treeWidget->clear();
}

#include <QMenu>
void SceneExplorer::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem* item = ui->treeWidget->itemAt(pos);
    QMenu* menu = new QMenu(this);
    bool top = false;
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        if(item == ui->treeWidget->topLevelItem(i))
        {
            top = true;
        }
    }
    if(top)
    {
        menu->addAction(QString("Add entity"),this,SLOT(ContextMenuAddEntityToScene()));
        menu->addAction(QString("Preview scene"),this,SLOT(ContextMenuPreviewScene()));
        menu->addAction(QString("Delete scene"),this,SLOT(ContextMenuDeleteScene()));
        menu->addAction(QString("Rename scene"),this,SLOT(ContextMenuRenameScene()));
    }
    else
    {
        if(item->data(0,Qt::UserRole+1).toBool())
        {
            menu->addAction(QString("Delete component"),this,SLOT(ContextMenuDeleteComponent()));
        }
        else
        {
            menu->addAction(QString("Add entity"),this,SLOT(ContextMenuAddEntityToEntity()));
            menu->addAction(QString("Rename entity"),this,SLOT(ContextMenuRenameEntity()));
            menu->addAction(QString("Delete entity"),this,SLOT(ContextMenuDeleteEntity()));
            menu->addAction(QString("Add Component"),this,SLOT(ContextMenuAddComponent()));
        }
    }
    menu->popup(ui->treeWidget->viewport()->mapToGlobal(pos));
}

void SceneExplorer::ContextMenuAddEntityToScene()
{
    emit CMAddEntity(QUuid(ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole).toByteArray()),se::ItemType::SCENE);
}

void SceneExplorer::ContextMenuAddEntityToEntity()
{
    emit CMAddEntity(QUuid(ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole).toByteArray()),se::ItemType::ENTITY);
}

void SceneExplorer::ContextMenuRenameScene()
{
    emit CMRenameScene(QUuid(ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole).toByteArray()));
}

void SceneExplorer::ContextMenuDeleteScene()
{
    emit CMDeleteScene(QUuid(ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole).toByteArray()));
}

void SceneExplorer::ContextMenuDeleteComponent()
{
    emit CMDeleteComponent(QUuid(ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole).toByteArray()),QUuid(ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole+2).toByteArray()));
}

void SceneExplorer::ContextMenuAddComponent()
{
    emit CMAddComponent(QUuid(ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole+2).toByteArray()));
}

void SceneExplorer::ContextMenuPreviewScene()
{
    emit CMPreviewScene(QUuid(ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole).toByteArray()));
}

void SceneExplorer::ContextMenuDeleteEntity()
{
    emit CMDeleteEntity(QUuid(ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole).toByteArray()));
}

void SceneExplorer::ContextMenuRenameEntity()
{
    emit CMRenameEntity(QUuid(ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole).toByteArray()));
}
