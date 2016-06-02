#ifndef SCENEEXPLORER_H
#define SCENEEXPLORER_H

#include <QWidget>
#include <qtreewidget.h>

typedef  int SCENEID;
typedef  int ENTITYID;

namespace Ui {
class SceneExplorer;
}

class SceneExplorer : public QWidget
{
    Q_OBJECT

public:

    explicit SceneExplorer(QWidget *parent = 0);

    ~SceneExplorer();

    SCENEID AddScene(QString);
    int DeleteScene(SCENEID);

    SCENEID AddEntity(QString entityName, SCENEID index);
    int DeleteEntity(SCENEID, ENTITYID);
public slots:

private:
    Ui::SceneExplorer *ui;
};
#endif // SCENEEXPLORER_H
