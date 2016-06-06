#ifndef ADDENTITYDIALOG_H
#define ADDENTITYDIALOG_H

#include <QDialog>

namespace Ui {
class AddEntityDialog;
}

class AddEntityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEntityDialog(QWidget *parent = 0);
    ~AddEntityDialog();

    QString name(){return _name;}

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QString _name;
    Ui::AddEntityDialog *ui;
};

#endif // ADDENTITYDIALOG_H
