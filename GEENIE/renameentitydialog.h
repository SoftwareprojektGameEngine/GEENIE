#ifndef RENAMEENTITYDIALOG_H
#define RENAMEENTITYDIALOG_H

#include <QDialog>

namespace Ui {
class RenameEntityDialog;
}

class RenameEntityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RenameEntityDialog(QWidget *parent = 0, QString name = QString());
    ~RenameEntityDialog();

    QString name();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QString _name;
    Ui::RenameEntityDialog *ui;
};

#endif // RENAMEENTITYDIALOG_H
