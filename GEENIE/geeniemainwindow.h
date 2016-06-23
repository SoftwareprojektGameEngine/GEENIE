#ifndef GEENIEMAINWINDOW_H
#define GEENIEMAINWINDOW_H

#include <QMainWindow>
#include "scripthighlighter.h"
#include "logger.h"
#include "geenie.h"
#include "sceneeditwidget.h"

class QTextDocument;
class Project;

namespace Ui {
class GEENIEMainWindow;
}

class GEENIEMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GEENIEMainWindow(GEENIE* geenie, QWidget *parent = 0);
    ~GEENIEMainWindow();

    void setScriptType(Highlighter::Types type);
    void setScript(QString& script);
    void setDockActionsChecked(EDockWidgetTypes type,bool checked);

    QTextDocument* scriptEditorDocument();
    inline SceneEditWidget* getSceneEditWidget() { return _sceneEditWidget; }

protected:
    void closeEvent(QCloseEvent* event);

signals:
    void saveSession();
    void changeScriptType(Highlighter::Types);
    void toggleDock(EDockWidgetTypes,bool);

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_actionExit_triggered();

    /*!
     * \fn void on_openScriptBtn_clicked()
     * \brief Load script on button click
     * \bug https://bugreports.qt.io/browse/QTBUG-52618
     */
    void on_openScriptBtn_clicked();

    /*!
     * \fn void on_saveScriptBtn_clicked()
     * \brief Save script on button click
     * \bug https://bugreports.qt.io/browse/QTBUG-52618
     */
    void on_saveScriptBtn_clicked();

    void on_actionInspector_toggled(bool arg1);

    void on_actionConsole_2_toggled(bool arg1);

    void on_actionExplorer_toggled(bool arg1);

    void on_actionAssets_toggled(bool arg1);

private:
    Ui::GEENIEMainWindow *ui;
    SceneEditWidget* _sceneEditWidget;
};

#endif // GEENIEMAINWINDOW_H
