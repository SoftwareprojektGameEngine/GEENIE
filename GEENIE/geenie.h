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

enum EInspectorTypes
{
    None = 0,
    Audio = 1,
    Camera = 2,
    Material = 3,
    Texture = 4,
    Transform = 5
};

class GEENIE : public QObject
{
    Q_OBJECT
public:
    explicit GEENIE(QObject *parent = 0);
    ~GEENIE();

    void insertDockWidget(EDockWidgetTypes type, QWidget* widget, bool show = false, Qt::DockWidgetArea area = Qt::BottomDockWidgetArea, bool floating = false, int width = 200, int height = 200);

private:


    void defaultSession(QWidget* inspector, QWidget* asset, QWidget* entities);
    void createDockWidgetTitles();

    QMap<EDockWidgetTypes, QDockWidget*> _dockWidgets;
    QMap<EDockWidgetTypes, QString> _dockWidgetsTitles;

    GEENIEMainWindow* _mainWindow;
    ScriptHighlighter* _highlighter;

    QString _layoutName;

    QTimer* _saveTimer;


private slots:
    void saveSession();
    void changeScriptType(Highlighter::Types type);

signals:

public slots:
};

#endif // GEENIE_H
