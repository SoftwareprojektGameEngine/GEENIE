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


    SCENEID id = AddScene("Scene1");
    ENTITYID id2 = AddEntity("Entity1", id);
    AddEntity("Entity2", id);

    DeleteEntity(id,id2);

    //TODO: Connect the UserAction with the Core. (Extra Useractionclass in core?)
    //connect(ui->treeWidget,ui->treeWidget->itemClicked,)
}

//!Cleans the used Storage.
SceneExplorer::~SceneExplorer()
{
    delete ui;
}

//!Add Scene in SceneExplorer. Returns the id of the Scene if no error occurs.
SCENEID SceneExplorer::AddScene(QString sceneName)
{
    if (sceneName == "")
    {
        //TODO: Use ErrorCode
        return -2;
    }

    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0,sceneName);
    ui->treeWidget->addTopLevelItem(itm);

    return ui->treeWidget->indexOfTopLevelItem(itm);
}

//!Add Entity to Selected Scene in SceneExplorer. Returns the id of the Entity if no error occurs.
SCENEID SceneExplorer::AddEntity(QString entityName, SCENEID sceneId)
{
    if (entityName == "")
    {
        //TODO: Use ErrorCode
        return -2;
    }

    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0, entityName);

    if (ui->treeWidget->topLevelItemCount() >= sceneId && sceneId <= 0)
    {
        QTreeWidgetItem *parent = ui->treeWidget->topLevelItem(sceneId);
        parent->addChild(itm);
        return parent->indexOfChild(itm);
    }

    //TODO: Use ErrorCode
    return -1;
}

//!Delete Scene from SceneExplorer. Returns 0 if no Error occurs.
int SceneExplorer::DeleteScene(SCENEID sceneId)
{
    if (sceneId >= 0 && sceneId < ui->treeWidget->topLevelItemCount())
    {
        if (ui->treeWidget->takeTopLevelItem(sceneId) != 0)
        {
            return 0;
        }
        //TODO: Use ErrorCode
        return -1;
    }
    //TODO: Use ErrorCode
    return -2;
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
            //TODO: Use ErroCode
            return -3;
        }
        //TODO: Use ErrorCode
        return -1;
    }
    //TODO: Use ErrorCode
    return -2;
}

