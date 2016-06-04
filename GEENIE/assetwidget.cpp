#include "assetwidget.h"
#include "ui_assetwidget.h"
#include <qfiledialog.h>

QString Path;
QList<QString> FileList;

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
        FileList.append(Path);
        foreach (QString item, FileList) {
            ui->MaterialListWidget->addItem(item);
        }
        break;
    case 1:
        Path = QFileDialog::getOpenFileName(this, tr("Load Texture"), "C:/", "All Files (*.*)");
        FileList.append(Path);
        foreach (QString item, FileList) {
            ui->TextureListWidget->addItem(item);
        }
        break;
    case 2:
        Path = QFileDialog::getOpenFileName(this, tr("Load Model"), "C:/", "All Files (*.*)");
        FileList.append(Path);
        foreach (QString item, FileList) {
            ui->ModelListWidget->addItem(item);
        }
        break;
    case 3:
        Path = QFileDialog::getOpenFileName(this, tr("Load Script"), "C:/", "All Files (*.*)");
        FileList.append(Path);
        foreach (QString item, FileList) {
            ui->ScriptListWidget->addItem(item);
        }
        break;
    case 4:
        Path = QFileDialog::getOpenFileName(this, tr("Load Audio"), "C:/", "All Files (*.*)");
        FileList.append(Path);
        foreach (QString item, FileList) {
            ui->AudioListWidget->addItem(item);
        }
        break;
    case 5:
        Path = QFileDialog::getOpenFileName(this, tr("Load Video"), "C:/", "All Files (*.*)");
        FileList.append(Path);
        foreach (QString item, FileList) {
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

void AssetWidget::FillTreeView(QString _path){
    /*
    //filling the tree view with the root path
    QString _path;//root path of the project
    QString mPath;
    if(path==''){
        mPath = "C:/";
    }else{
        mPath = _path;
    }
    dirModel = new QFileSystemModel(this);
    dirModel->setRootPath(mPath);
    ui->treeView->setModel(dirModel);
    */
}
