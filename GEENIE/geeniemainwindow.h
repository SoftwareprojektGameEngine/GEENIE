#ifndef GEENIEMAINWINDOW_H
#define GEENIEMAINWINDOW_H

#include <QMainWindow>
#include "scripthighlighter.h"
#include "logger.h"

class QTextDocument;
class Project;

namespace Ui {
class GEENIEMainWindow;
}

class GEENIEMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GEENIEMainWindow(QWidget *parent = 0);
    ~GEENIEMainWindow();

    void setScriptType(Highlighter::Types type);
    void setScript(QString& script);
    void setDockActionsChecked(EDockWidgetTypes type,bool checked);

    void setProjectSaved(bool saved);
    void setProjectConfigured(bool configured);

    QTextDocument* scriptEditorDocument();

protected:
    void closeEvent(QCloseEvent* event);

signals:
    void saveSession();
    void changeScriptType(Highlighter::Types);
    void toggleDock(EDockWidgetTypes,bool);
    void redo();
    void undo();
    void saveLayout();
    void loadLayout();
    void newProject();
    void newScene();
    void checkIfProjectConfigured();
    void onClose();
    void saveProject();
    void saveProject(QString path);
    void loadProject(QString path);
    void setLayoutToDefault();

public slots:
    void CanUndo(bool undo);
    void CanRedo(bool redo);

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

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void on_actionNew_triggered();

    void on_actionLoad_default_layout_triggered();

private:
    bool _projectSaved;
    bool _projectConfigured;
    Ui::GEENIEMainWindow *ui;
};

#endif // GEENIEMAINWINDOW_H
