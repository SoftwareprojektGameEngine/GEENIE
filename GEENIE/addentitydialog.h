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

private:
    Ui::AddEntityDialog *ui;
};

#endif // ADDENTITYDIALOG_H
