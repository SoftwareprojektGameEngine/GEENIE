#include "assetwidget.h"
#include "ui_assetwidget.h"
#include <qfiledialog.h>

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
    QString Path;
    AssetType type;
    switch (TabName) {
    case 0:
        Path = QFileDialog::getOpenFileName(this, tr("Load Material"), "C:/", "All Files (*.*)");
        type = AssetType::MATERIAL_ASSET;
        break;
    case 1:
        Path = QFileDialog::getOpenFileName(this, tr("Load Texture"), "C:/", "All Files (*.*)");
        type = AssetType::TEXTURE_ASSET;
        break;
    case 2:
        Path = QFileDialog::getOpenFileName(this, tr("Load Model"), "C:/", "All Files (*.*)");
        type = AssetType::MODEL_ASSET;
        break;
    case 3:
        Path = QFileDialog::getOpenFileName(this, tr("Load Script"), "C:/", "All Files (*.*)");
        type = AssetType::SCRIPT_ASSET;
        break;
    case 4:
        Path = QFileDialog::getOpenFileName(this, tr("Load Audio"), "C:/", "All Files (*.*)");
        type = AssetType::AUDIO_ASSET;
        break;
    case 5:
        Path = QFileDialog::getOpenFileName(this, tr("Load Video"), "C:/", "All Files (*.*)");
        type = AssetType::VIDEO_ASSET;
        break;
    default:
        break;
    }
    if(Path != QString())
    {
        emit AddAssetToProject(Path,type);
    }
}

void AssetWidget::on_DeleteButton_clicked()
{
    QListWidget* view;
    switch(ui->AssetTabWidget->currentIndex())
    {
    case 0:
        view = ui->MaterialListWidget;
        break;
    case 1:
        view = ui->TextureListWidget;
        break;
    case 2:
        view = ui->ModelListWidget;
        break;
    case 3:
        view = ui->ScriptListWidget;
        break;
    case 4:
        view = ui->AudioListWidget;
        break;
    case 5:
        view = ui->VideoListWidget;
        break;
    default:
        break;
    }
    if(view != 0 && !view->selectedItems().isEmpty())
    {

        emit DeleteAsset(QUuid(view->selectedItems().at(0)->data(Qt::UserRole).toByteArray()));
    }
}

void AssetWidget::clear()
{
    ui->ModelListWidget->clear();
    ui->TextureListWidget->clear();
    ui->MaterialListWidget->clear();
    ui->ScriptListWidget->clear();
    ui->AudioListWidget->clear();
    ui->VideoListWidget->clear();
}

void AssetWidget::AddAsset(Asset *asset)
{
    QListWidgetItem* item;
    switch(asset->GetType())
    {
    case MODEL_ASSET:
    {
        item = new QListWidgetItem(asset->GetPath(),ui->ModelListWidget);
        item->setData(Qt::UserRole,asset->GetID().toByteArray());
        ui->ModelListWidget->update();
        break;
    }
    case MATERIAL_ASSET:
    {
        item = new QListWidgetItem(asset->GetPath(),ui->MaterialListWidget);
        item->setData(Qt::UserRole,asset->GetID().toByteArray());
        ui->MaterialListWidget->update();
        break;
    }
    case TEXTURE_ASSET:
    {
        item = new QListWidgetItem(asset->GetPath(),ui->TextureListWidget);
        item->setData(Qt::UserRole,asset->GetID().toByteArray());
        ui->TextureListWidget->update();
        break;
    }
    case AUDIO_ASSET:
    {
        item = new QListWidgetItem(asset->GetPath(),ui->AudioListWidget);
        item->setData(Qt::UserRole,asset->GetID().toByteArray());
        ui->AudioListWidget->update();
        break;
    }
    case VIDEO_ASSET:
    {
        item = new QListWidgetItem(asset->GetPath(),ui->VideoListWidget);
        item->setData(Qt::UserRole,asset->GetID().toByteArray());
        ui->VideoListWidget->update();
        break;
    }
    case SCRIPT_ASSET:
    {
        item = new QListWidgetItem(asset->GetPath(),ui->ScriptListWidget);
        item->setData(Qt::UserRole,asset->GetID().toByteArray());
        ui->ScriptListWidget->update();
        break;
    }
    default:
        break;
    }
}
