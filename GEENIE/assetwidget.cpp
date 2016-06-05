#include "assetwidget.h"
#include "ui_assetwidget.h"
#include <qfiledialog.h>
#include <core.h>
#include <components.h>

QString Path;
QList<QString> MaterialList;
QList<QString> TextureList;
QList<QString> ModelList;
QList<QString> ScriptList;
QList<QString> AudioList;
QList<QString> VideoList;

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
    int TabName = ui->AssetTabWidget->currentIndex();
    switch (TabName) {
    case 0:
        Path = QFileDialog::getOpenFileName(this, tr("Load Material"), "C:/", "All Files (*.*)");
        MaterialList.append(Path);
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
    //qDeleteAll(ui->listWidget->selectedItems());
    /*int count = ui->listWidget->selectedItems().count();
    for(int i=0; i<count;i++)
    {
        FileList.removeAt(ui->listWidget->selectionModel()->selectedIndexes()[i].row());
    }
    ui->listWidget->update();
*/}

void AssetWidget::FillAssetLists(){
    Project *CurrentProject;
    /*QList<Asset> iterator = CurrentProject->GetAssets();

    foreach (Asset item, iterator) {
        switch (item.GetType()) {
        case "Model":
            ModelList.append(item.GetPath());
            break;
        case "Material":
            MaterialList.append(item.GetPath());
            break;
        case "Texture":
            TextureList.append(item.GetPath());
            break;
        case "Audio":
            AudioList.append(item.GetPath());
            break;
        case "Video":
            VideoList.append(item.GetPath());
            break;
        case "Script":
            ScriptList.append(item.GetPath());
            break;
        default:
            break;
        }
    }*/
}
