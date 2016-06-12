#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H
#include "geenie.h"

#include <QWidget>

namespace Ui {
class InspectorWidget;
}

class InspectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InspectorWidget(QWidget *parent = 0);
    ~InspectorWidget();

    void addWidget(QWidget* widget);
    void removeWidget(QWidget* widget);
    void FillTree(Entity*, bool sub = false);


public slots:
    void resizeSlot(int h, int w);

private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::InspectorWidget *ui;
    QTreeWidget *t;
    void SetHeaderText(QString, QString);
    void InitializeTree();
};

#endif // INSPECTORWIDGET_H

