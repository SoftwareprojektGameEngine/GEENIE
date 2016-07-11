#include "sceneexplorer.h"
#include "ui_sceneexplorer.h"
#include "core.h"
#include <QDebug>
#include <qdrag.h>
#include <QMimeData>

//!Initializes the SceneExplorer.
SceneExplorer::SceneExplorer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneExplorer)
{
    ui->setupUi(this);
    tree = ui->treeWidget;
    tree->setColumnCount(1);
    //tree->setAcceptDrops(true);
    //tree->setDragEnabled(true);
    //tree->setDragDropMode(QAbstractItemView::InternalMove);
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

#include <QDebug>

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
    ui->treeWidget->expandAll();
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
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        if(item == ui->treeWidget->topLevelItem(i))
        {
            emit sceneClicked(QUuid(item->data(0,Qt::UserRole).toByteArray()));
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
    if(ui->treeWidget->headerItem()->data(0,Qt::DisplayRole) == QString("(No project configured)"))
    {
        return;
    }
    QTreeWidgetItem* item = ui->treeWidget->itemAt(pos);

    QMenu* menu = new QMenu(this);
    if(item == 0)
    {
        menu->addAction(QString("AddScene"), this, SLOT(ContextMenuAddScene()));
    }
    else
    {
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
                menu->addAction(QString("Delete entity"),this,SLOT(ContextMenuDeleteEntity()));
                menu->addAction(QString("Move Entity"),this,SLOT(ContextMenuMoveEntity()));
                menu->addAction(QString("Add Component"),this,SLOT(ContextMenuAddComponent()));
                menu->addAction(QString("Delete Component"),this,SLOT(ContextMenuDeleteComponent()));
            }
        }
    }
    menu->popup(ui->treeWidget->viewport()->mapToGlobal(pos));
}

void SceneExplorer::ContextMenuAddScene()
{
    emit CMAddScene();
}

void SceneExplorer::ContextMenuMoveEntity()
{
    emit CMMoveEntity(QUuid(ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole).toByteArray()));
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
    emit CMDeleteComponent(QUuid(ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole).toByteArray()));
}

void SceneExplorer::ContextMenuAddComponent()
{
    emit CMAddComponent(QUuid(ui->treeWidget->selectedItems().at(0)->data(0,Qt::UserRole).toByteArray()));
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


void SceneExplorer::on_treeWidget_itemPressed(QTreeWidgetItem *item, int column)
{
/*
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    mimeData->setText("Text");
    drag->setMimeData(mimeData);
    QPixmap map;


    Qt::DropAction dropAction = drag->exec();
*/
}
