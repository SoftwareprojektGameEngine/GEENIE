#ifndef SCENEEDITWIDGET_H
#define SCENEEDITWIDGET_H

#include <QWidget>
#include "enginewrapper.h"
#include "geenie.h"

namespace Ui {
class SceneEditWidget;
}

class SceneEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SceneEditWidget(GEENIE* geenie, QWidget *parent = 0);
    ~SceneEditWidget();

    inline EngineWidgetWrapper* GetEngineWidget() { return engineWidget; }

private:
    Ui::SceneEditWidget *ui;
    EngineWrapper* engine;
    EngineWidgetWrapper* engineWidget;
    Vector camPos;
    Vector camDir;
    Vector camUp;

protected:
    virtual void keyPressEvent(QKeyEvent* keyEvent);
};

#endif // SCENEEDITWIDGET_H
