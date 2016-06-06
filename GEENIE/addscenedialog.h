#ifndef ADDSCENEDIALOG_H
#define ADDSCENEDIALOG_H

#include <QDialog>

namespace Ui {
class AddSceneDialog;
}

class AddSceneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSceneDialog(QWidget *parent = 0);
    ~AddSceneDialog();

    QString name(){return _name;}

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QString _name;
    Ui::AddSceneDialog *ui;
};

#endif // ADDSCENEDIALOG_H
