#ifndef INSPECTORPARENTWIDGET_H
#define INSPECTORPARENTWIDGET_H

#include <QWidget>
#include <QUuid>
class InspectorParentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InspectorParentWidget(QWidget *parent = 0, QUuid id = QUuid());

    QUuid getID();
    void setID(QUuid id);

private:
    QUuid _id;

signals:

public slots:
};

#endif // INSPECTORPARENTWIDGET_H
