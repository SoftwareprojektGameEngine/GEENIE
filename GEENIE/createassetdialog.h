#ifndef CREATEASSETDIALOG_H
#define CREATEASSETDIALOG_H

#include <QDialog>
#include <QString>
#include <QDir>
#include <QList>
#include "assets.h"
#include "QFileDialog"
#include "QMessageBox"
namespace Ui {
class createassetdialog;
}

class createassetdialog : public QDialog
{
    Q_OBJECT

public:
    explicit createassetdialog(QWidget *parent = 0);
    ~createassetdialog();
    QString getFile();
    QString getName();
    AssetType getType();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::createassetdialog *ui;
    QString file;
    QString name;
    QWidget *p;
    AssetType type;
};

#endif // CREATEASSETDIALOG_H
