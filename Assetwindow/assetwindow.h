#ifndef ASSETWINDOW_H
#define ASSETWINDOW_H

#include <QMainWindow>

namespace Ui {
class AssetWindow;
}

class AssetWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AssetWindow(QWidget *parent = 0);
    ~AssetWindow();

private:
    Ui::AssetWindow *ui;
};

#endif // ASSETWINDOW_H
