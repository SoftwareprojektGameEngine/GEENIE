#ifndef SCENEEDITWIDGET_H
#define SCENEEDITWIDGET_H

#include <QWidget>
#include "enginewrapper.h"
#include "geenie.h"

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

    inline EngineWidgetWrapper* GetEngineWidget() { return engineWidget; }

private:

    //! Private variable that stores the sceneeditwidget ui.

    Ui::SceneEditWidget *ui;

    //! Private variable that stores the connection to osg.

    EngineWrapper* engine;

    //! Private variable that stores the connection to the osg-widget.

    EngineWidgetWrapper* engineWidget;
    Vector camPos;
    Vector camDir;
    Vector camUp;

protected:
    virtual void keyPressEvent(QKeyEvent* keyEvent);

private slots:
    void setScene(QUuid sceneID);
};

#endif // SCENEEDITWIDGET_H
