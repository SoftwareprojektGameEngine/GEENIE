#ifndef RENAMESCENEDIALOG_H
#define RENAMESCENEDIALOG_H

#include <QDialog>

namespace Ui {
class RenameSceneDialog;
}

class RenameSceneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RenameSceneDialog(QWidget *parent = 0);
    ~RenameSceneDialog();

private:
    Ui::RenameSceneDialog *ui;
};

#endif // RENAMESCENEDIALOG_H
