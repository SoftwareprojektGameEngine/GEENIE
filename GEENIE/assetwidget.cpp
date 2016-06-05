#include "assetwidget.h"
#include "ui_assetwidget.h"
#include <qfiledialog.h>
#include <core.h>
#include <components.h>
#include <useractions.h>

QString Path;
QList<QString> MaterialList;
QList<QString> TextureList;
QList<QString> ModelList;
QList<QString> ScriptList;
QList<QString> AudioList;
QList<QString> VideoList;
Project *CurrentProject;

AssetWidget::AssetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AssetWidget)
{
    ui->setupUi(this);
}

AssetWidget::~AssetWidget()
{
    delete ui;
}

void AssetWidget::on_LoadButton_clicked()
{
    //TODO: datei in richtigen ordner kopieren, asset registrieren
    int TabName = ui->AssetTabWidget->currentIndex();
    switch (TabName) {
    case 0:
        Path = QFileDialog::getOpenFileName(this, tr("Load Material"), "C:/", "All Files (*.*)");
        MaterialList.append(Path);
        //QFile.copy(Path, );
        //MaterialAsset* asset = new MaterialAsset(Path);
        //CurrentProject->AddUserAction(new AddAssetAction(CurrentProject, asset));
        ui->MaterialListWidget->clear();
        foreach (QString item, MaterialList) {
            ui->MaterialListWidget->addItem(item);
        }
        break;
    case 1:
        Path = QFileDialog::getOpenFileName(this, tr("Load Texture"), "C:/", "All Files (*.*)");
        TextureList.append(Path);
        ui->TextureListWidget->clear();
        foreach (QString item, TextureList) {
            ui->TextureListWidget->addItem(item);
        }
        break;
    case 2:
        Path = QFileDialog::getOpenFileName(this, tr("Load Model"), "C:/", "All Files (*.*)");
        ModelList.append(Path);
        ui->ModelListWidget->clear();
        foreach (QString item, ModelList) {
            ui->ModelListWidget->addItem(item);
        }
        break;
    case 3:
        Path = QFileDialog::getOpenFileName(this, tr("Load Script"), "C:/", "All Files (*.*)");
        ScriptList.append(Path);
        ui->ScriptListWidget->clear();
        foreach (QString item, ScriptList) {
            ui->ScriptListWidget->addItem(item);
        }
        break;
    case 4:
        Path = QFileDialog::getOpenFileName(this, tr("Load Audio"), "C:/", "All Files (*.*)");
        AudioList.append(Path);
        ui->AudioListWidget->clear();
        foreach (QString item, AudioList) {
            ui->AudioListWidget->addItem(item);
        }
        break;
    case 5:
        Path = QFileDialog::getOpenFileName(this, tr("Load Video"), "C:/", "All Files (*.*)");
        VideoList.append(Path);
        ui->VideoListWidget->clear();
        foreach (QString item, VideoList) {
            ui->VideoListWidget->addItem(item);
        }
        break;
    default:
        break;
    }
}

void AssetWidget::on_DeleteButton_clicked()
{
    QListWidget *view;
    QList<QString> *list;
    int row = 0;
    switch(ui->AssetTabWidget->currentIndex())
    {
    case 0:
        view = ui->MaterialListWidget;
        list = &MaterialList;
        row = view->selectionModel()->selectedRows(0).at(0).row();
        break;
    case 1:
        view = ui->TextureListWidget;
        list = &TextureList;
        row = view->selectionModel()->selectedRows(1).at(1).row();
        break;
    case 2:
        view = ui->ModelListWidget;
        list = &ModelList;
        row = view->selectionModel()->selectedRows(2).at(2).row();
        break;
    case 3:
        view = ui->ScriptListWidget;
        list = &ScriptList;
        row = view->selectionModel()->selectedRows(3).at(3).row();
        break;
    case 4:
        view = ui->AudioListWidget;
        list = &AudioList;
        row = view->selectionModel()->selectedRows(4).at(4).row();
        break;
    case 5:
        view = ui->VideoListWidget;
        list = &VideoList;
        row = view->selectionModel()->selectedRows(5).at(5).row();
        break;
    default:
        break;
    }
    qDeleteAll(view->selectedItems());
    list->removeAt(row);
    view->update();

}

void AssetWidget::FillAssetLists(){
    QHashIterator<QUuid, Asset*> iterator = CurrentProject->GetAssets();

    while(iterator.hasNext())
    {
        iterator.next();
        switch(iterator.value()->GetType())
        {
        case MODEL_ASSET:
            ModelList.append(iterator.value()->GetPath());
            break;
        case MATERIAL_ASSET:
            MaterialList.append(iterator.value()->GetPath());
            break;
        case TEXTURE_ASSET:
            TextureList.append(iterator.value()->GetPath());
            break;
        case AUDIO_ASSET:
            AudioList.append(iterator.value()->GetPath());
            break;
        case VIDEO_ASSET:
            VideoList.append(iterator.value()->GetPath());
            break;
        case SCRIPT_ASSET:
            ScriptList.append(iterator.value()->GetPath());
            break;
        default:
            break;
        }
    }
}
