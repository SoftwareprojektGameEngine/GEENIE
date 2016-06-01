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
    //Opens File-Dialog and feeds the FileList
    Path = QFileDialog::getOpenFileName(this, tr("Load Assets"), "C://", "All Files (*.*)");
    FileList.append(Path);
    foreach (QString item, FileList) {
        ui->listWidget->update();
        ui->listWidget->addItem(item);
    }
}

void AssetWidget::on_DeleteButton_clicked()
{
    //qDeleteAll(ui->listWidget->selectedItems());
    int count = ui->listWidget->selectedItems().count();
    for(int i=0; i<count;i++)
    {
        FileList.removeAt(ui->listWidget->selectionModel()->selectedIndexes()[i].row());
    }
    ui->listWidget->update();
}

void AssetWidget::on_treeView_clicked(const QModelIndex &index)
{
    //Append ListView with FileList that gets data from the treeview
    FileList.clear();
    //FileList.append();//@Artem: HILFE!!!
    ui->listWidget->addItems(FileList);
    ui->listWidget->update();
}

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
