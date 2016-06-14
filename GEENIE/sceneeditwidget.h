#ifndef SCENEEDITWIDGET_H
#define SCENEEDITWIDGET_H

#include <QWidget>
#include "enginewrapper.h"

namespace Ui {
class SceneEditWidget;
}

/*!
 * \class SceneEditWidget sceneeditwidget.h
 * \brief The SceneEditWidget class
 */

class SceneEditWidget : public QWidget
{
    Q_OBJECT

public:

    //! Constructor.
    /*!
     * Creates a widget which shows the osg output.
     * \param engine The connection to osg.
     * \param parent The parent widget.
     */

    explicit SceneEditWidget(EngineWrapper* engine, QWidget *parent = 0);

    //! Deconstructor.
    /*!
     * Deletes the osg-widget and the whole ui.
     */

    ~SceneEditWidget();

private:

    //! Private variable that stores the sceneeditwidget ui.

    Ui::SceneEditWidget *ui;

    //! Private variable that stores the connection to osg.

    EngineWrapper* engine;

    //! Private variable that stores the connection to the osg-widget.

    EngineWidgetWrapper* engineWidget;
};

#endif // SCENEEDITWIDGET_H
