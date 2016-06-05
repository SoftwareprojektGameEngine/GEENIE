#ifndef INSPECTORPARENTWIDGET_H
#define INSPECTORPARENTWIDGET_H

#include <QWidget>
#include <QUuid>
class InspectorParentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InspectorParentWidget(QWidget *parent = 0, QUuid id = QUuid(), QUuid parentId = QUuid(),QString name = QString());

    QUuid getID();
    void setID(QUuid id);
    QUuid getParentID();
    void setParentID(QUuid id);

protected:
    QUuid _id;
    QUuid _parentId;
    QString _name;

signals:

public slots:
};

#endif // INSPECTORPARENTWIDGET_H
