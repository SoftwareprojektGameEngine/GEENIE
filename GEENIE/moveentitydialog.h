#ifndef MOVEENTITYDIALOG_H
#define MOVEENTITYDIALOG_H

#include <QDialog>
#include <QUuid>
#include <QAbstractButton>
#include <QList>
#include <QString>

struct ENTITY_DATA_ME
{
    QString entityName;
    QUuid   entityId;
    QList<ENTITY_DATA_ME> entities;
};

namespace Ui {
class moveentitydialog;
}

class moveentitydialog : public QDialog
{
    Q_OBJECT

public:
    explicit moveentitydialog(QWidget *parent = 0);
    ~moveentitydialog();
    QUuid getEntityID(){return entityID;}
    QUuid getNewParentID(){return newParentID;}
    void FillComboBox(QList<ENTITY_DATA_ME> e, QUuid id);
private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QUuid entityID;
    QUuid newParentID;
    Ui::moveentitydialog *ui;
};

#endif // MOVEENTITYDIALOG_H
