#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "inspectorparentwidget.h"

namespace Ui {
class Inspector;
}

class Inspector : public InspectorParentWidget
{
    Q_OBJECT

public:
    explicit Inspector(QWidget *parent = 0, QUuid id = QUuid(), QUuid parentId = QUuid());
    ~Inspector();

private:
    Ui::Inspector *ui;
};

#endif // INSPECTOR_H
