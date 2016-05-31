#ifndef ASSETWIDGET_H
#define ASSETWIDGET_H

#include <QWidget>

namespace Ui {
class AssetWidget;
}

class AssetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AssetWidget(QWidget *parent = 0);
    ~AssetWidget();
    void FillTreeView(QString _path);

private slots:
    void on_LoadButton_clicked();

    void on_DeleteButton_clicked();

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::AssetWidget *ui;
};

#endif // ASSETWINDOW_H
