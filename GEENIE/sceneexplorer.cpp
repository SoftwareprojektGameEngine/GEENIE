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
    //TODO: Connect the UserAction with the Core. (Extra Useractionclass in core?)
    //connect(ui->treeWidget,ui->treeWidget->itemClicked,)
}

//!Cleans the used Storage.
SceneExplorer::~SceneExplorer()
{
    delete ui;
}

void SceneExplorer::setHeader(QString &name)
{
    ui->treeWidget->setHeaderLabel(name);
}

//!Add Scene in SceneExplorer. Returns the id of the Scene if no error occurs.
SCENEID SceneExplorer::AddScene(QString sceneName, QUuid id)
{
    if (sceneName == "")
    {
        return SE_INVALID_NAME;
    }

    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0,sceneName);
    itm->setData(0,Qt::UserRole,id.toByteArray());
    ui->treeWidget->addTopLevelItem(itm);

    return ui->treeWidget->indexOfTopLevelItem(itm);
}

//!Add Entity to Selected Scene in SceneExplorer. Returns the id of the Entity if no error occurs.
SCENEID SceneExplorer::AddEntity(QString entityName, SCENEID sceneId, QUuid id)
{
    if (entityName == "")
    {
        return SE_INVALID_NAME;
    }

    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0, entityName);
    itm->setData(0,Qt::UserRole,id.toByteArray());
    itm->setData(0,Qt::UserRole+1,false);

    if (ui->treeWidget->topLevelItemCount() >= sceneId && sceneId <= 0)
    {
        QTreeWidgetItem *parent = ui->treeWidget->topLevelItem(sceneId);
        parent->addChild(itm);
        return parent->indexOfChild(itm);
    }

    return SE_INVALID_SCENEID;
}

COMPONENTID SceneExplorer::AddComponent(QString componentName, SCENEID sceneIndex, ENTITYID entityIndex, QUuid id, QUuid entityId)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0,componentName);
    itm->setData(0,Qt::UserRole,id.toByteArray());
    itm->setData(0,Qt::UserRole+1,true);
    itm->setData(0,Qt::UserRole+2,entityId);

    if(componentName == "")
    {
        return SE_INVALID_NAME;
    }

    if(ui->treeWidget->topLevelItemCount()>= sceneIndex && sceneIndex>=0)
    {
        if(ui->treeWidget->topLevelItem(sceneIndex)->childCount()>= entityIndex && entityIndex >=0)
        {
            ui->treeWidget->topLevelItem(sceneIndex)->child(entityIndex)->addChild(itm);
            return ui->treeWidget->topLevelItem(sceneIndex)->child(entityIndex)->indexOfChild(itm);
        }
        return SE_INVALID_ENTITYID;
    }
    return SE_INVALID_SCENEID;
}

//!Delete Scene from SceneExplorer. Returns 0 if no Error occurs.
int SceneExplorer::DeleteScene(SCENEID id)
{
    if (id >= 0 && id < ui->treeWidget->topLevelItemCount())
    {
        if (ui->treeWidget->takeTopLevelItem(id) != 0)
        {
            return 0;
        }
        return SE_TAKE_ERROR;
    }
    return SE_INVALID_SCENEID;
}

//!Delete Entity from SceneExplorer. Returns 0 if no Error occurs.
int SceneExplorer::DeleteEntity(SCENEID sceneId, ENTITYID entityId)
{
    if (sceneId >= 0 && sceneId < ui->treeWidget->topLevelItemCount())
    {
        QTreeWidgetItem *scene = ui->treeWidget->topLevelItem(sceneId);

        if (entityId >= 0 && entityId < scene->childCount())
        {
            if (scene->takeChild(entityId) != 0)
            {
                return 0;
            }
            return SE_TAKE_ERROR;
        }
        //TODO: Use ErrorCode
        return SE_INVALID_ENTITYID;
    }
    //TODO: Use ErrorCode
    return SE_INVALID_SCENEID;
}

int SceneExplorer::DeleteComponent(SCENEID sceneIndex, ENTITYID entityIndex, COMPONENTID componentIndex)
{
    if(ui->treeWidget->topLevelItemCount()>= sceneIndex && sceneIndex>=0)
    {
        if(ui->treeWidget->topLevelItem(sceneIndex)->childCount()>= entityIndex && entityIndex >=0)
        {
            if(ui->treeWidget->topLevelItem(sceneIndex)->child(entityIndex)->childCount()>= componentIndex && componentIndex >= 0)
            {
                if(ui->treeWidget->topLevelItem(sceneIndex)->child(entityIndex)->takeChild(componentIndex) != 0)
                {
                   return 0;
                }
                return SE_TAKE_ERROR;
            }
            return SE_INVALID_COMPONENTID;
        }
        return SE_INVALID_ENTITYID;
    }
    return SE_INVALID_SCENEID;
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
