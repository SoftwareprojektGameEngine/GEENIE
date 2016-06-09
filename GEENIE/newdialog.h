#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>

namespace Ui {
class NewDialog;
}

class NewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDialog(QWidget *parent = 0, bool projectConfigured = false);
    ~NewDialog();
    bool type(){return _type;}

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::NewDialog *ui;
    bool _type;
};

#endif // NEWDIALOG_H
