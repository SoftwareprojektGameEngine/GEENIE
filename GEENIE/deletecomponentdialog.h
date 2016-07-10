#ifndef DELETECOMPONENTDIALOG_H
#define DELETECOMPONENTDIALOG_H

#include <QDialog>
#include <QList>
#include <QString>
#include <QUuid>

struct COMPONENT_DATA_DC
{
    QString name;
    QUuid id;
};

namespace Ui {
class DeleteComponentDialog;
}

class DeleteComponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteComponentDialog(QWidget *parent = 0);
    ~DeleteComponentDialog();

    void SetComponentList(QList<COMPONENT_DATA_DC>);

    QUuid SelectedId(){return selectedId;}

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::DeleteComponentDialog *ui;
    QList<COMPONENT_DATA_DC> data;
    QUuid selectedId;
};

#endif // DELETECOMPONENTDIALOG_H
