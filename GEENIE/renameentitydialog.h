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
    explicit RenameEntityDialog(QWidget *parent = 0);
    ~RenameEntityDialog();

private:
    Ui::RenameEntityDialog *ui;
};

#endif // RENAMEENTITYDIALOG_H
