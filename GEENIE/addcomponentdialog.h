#ifndef ADDCOMPONENTDIALOG_H
#define ADDCOMPONENTDIALOG_H

#include <QDialog>


namespace Ui {
class AddComponentDialog;
}

class Component;

class AddComponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddComponentDialog(QWidget *parent = 0);
    ~AddComponentDialog();

    Component* component();

private slots:
    void on_createBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::AddComponentDialog *ui;
    Component* _component;
};

#endif // ADDCOMPONENTDIALOG_H
