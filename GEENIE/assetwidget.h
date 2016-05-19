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

private:
    Ui::AssetWidget *ui;
};

#endif // ASSETWINDOW_H
