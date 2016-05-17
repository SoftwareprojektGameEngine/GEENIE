#ifndef GEENIE_H
#define GEENIE_H

#include <QObject>
#include <QMap>
#include <QString>
#include "common.h"
#include "scripthighlighter.h"

class GEENIEMainWindow;
class QDockWidget;

enum class EDockWidgetTypes
{
    LoggerWidget,
    InspectorWidget,
    AssetsWidget,
    EntitiesWidget,
    ScriptEditorWidget
};

class GEENIE : public QObject
{
    Q_OBJECT
public:
    explicit GEENIE(QObject *parent = 0);

    void insertDockWidget(EDockWidgetTypes type, QWidget* widget, bool show = false, Qt::DockWidgetArea area = Qt::BottomDockWidgetArea);

private:

    void createDockWidgetTitles();

    QMap<EDockWidgetTypes, QDockWidget*> _dockWidgets;
    QMap<EDockWidgetTypes, QString> _dockWidgetsTitles;

    GEENIEMainWindow* _mainWindow;
    ScriptHighlighter* _highlighter;

    QString _layoutName;


private slots:
    void saveSession();

signals:

public slots:
};

#endif // GEENIE_H
