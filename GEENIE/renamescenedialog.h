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
    explicit RenameSceneDialog(QWidget *parent = 0, QString name = QString());
    ~RenameSceneDialog();

    QString name();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QString _name;
    Ui::RenameSceneDialog *ui;
};

#endif // RENAMESCENEDIALOG_H
