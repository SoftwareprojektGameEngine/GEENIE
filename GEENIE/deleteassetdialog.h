#ifndef DELETEASSETDIALOG_H
#define DELETEASSETDIALOG_H

#include <QDialog>
#include <QUuid>
#include <QString>
#include <QList>

struct ASSET_LIST_DA
{
    QString name;
    QUuid id;
};

namespace Ui {
class DeleteAssetDialog;
}

class DeleteAssetDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DeleteAssetDialog(QWidget *parent = 0);
    ~DeleteAssetDialog();

    QUuid getAssetID();
    void setAssetList(QList<ASSET_LIST_DA>);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::DeleteAssetDialog *ui;
    QUuid assetID;
};

#endif // DELETEASSETDIALOG_H
