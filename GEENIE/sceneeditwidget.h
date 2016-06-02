#ifndef SCENEEDITWIDGET_H
#define SCENEEDITWIDGET_H

#include <QWidget>
#include "enginewrapper.h"

namespace Ui {
class SceneEditWidget;
}

class SceneEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SceneEditWidget(EngineWrapper* engine, QWidget *parent = 0);
    ~SceneEditWidget();

private:
    Ui::SceneEditWidget *ui;
    EngineWrapper* engine;
    EngineWidgetWrapper* engineWidget;
};

#endif // SCENEEDITWIDGET_H
