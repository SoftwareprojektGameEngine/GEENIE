#ifndef GDOCKWIDGET_H
#define GDOCKWIDGET_H

#include <QDockWidget>

/*!
 * \class GDockWidget gdockwidget.h
 * \brief The GDockWidget class
 */

class GDockWidget : public QDockWidget
{
    Q_OBJECT

public:

    //! Constructor
    /*!
     * \brief Creates the dockable widgets.
     * \param title The title of the widget.
     * \param parent The parent-widget.
     * \param flags QT window-flags can be added. For more details watch the QT-Documentation.
     */

    GDockWidget(const QString &title, QWidget* parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());

protected:

    //! Slot for the resize-signal.
    /*!
     * \brief Will be executed if a widget is resized. Updates the size of the widget.
     * \param event Needs the resize-event.
     */

    void resizeEvent(QResizeEvent*event);

signals:

    //! Signal for the resize-event.
    /*!
     * \param h The height of the widget.
     * \param w The width of the widget.
     */

    void resizeSignal(int h, int w);
};

#endif // GDOCKWIDGET_H
