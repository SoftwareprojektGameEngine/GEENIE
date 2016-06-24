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

/*!
 * \class GEENIEMainWindow geeniemainwindow.h
 * \brief The GEENIEMainWindow class.
 */

class GEENIEMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Constructor.
    /*!
      Setting the font, some settings for the scripteditor and the undo and redo button as not clickable.
     * \param parent The parent widget.
     */

    explicit GEENIEMainWindow(EngineWrapper *engine, QWidget *parent = 0);

    //! Destructor.
    /*!
     * Destroys the mainwindow ui.
     */
    ~GEENIEMainWindow();

    //! Set script type for the scipteditor.
    /*!
     * \param type Python or Lua for example.
     */

    void setScriptType(Highlighter::Types type);

    //! Filling the script-editor with a script.
    /*!
     * \param script The script.
     */

    void setScript(QString& script);

    //! Method to set the widgets in the menu, if they are docked, as checked.
    /*!
     * \param type The widget type (assetwidget, ...).
     * \param checked Is the widget docked?
     */

    void setDockActionsChecked(EDockWidgetTypes type,bool checked);

    //! Sets the current project as saved or not.
    /*!
     * \param saved Is the project saved?
     */

    void setProjectSaved(bool saved);

    //! Sets the project as configured or not.
    /*!
     * \param configured Is the current project configured (not empty)?
     */

    void setProjectConfigured(bool configured);

    //! Gets the current script in the scripteditor as a textdocument.

    QTextDocument* scriptEditorDocument();
    inline SceneEditWidget* getSceneEditWidget() { return _sceneEditWidget; }

protected:

    //! Emits on-close.
    /*!
     * If the user want to exit GEENIE, he will be asked, if there are unsaved changes, to save them. Otherwise he will be asked if he or she is shure to leave the editor.
     */
    void closeEvent(QCloseEvent* event);

signals:

    //! Signal for save-session slot.

    void saveSession();

    //! Signal for changing scripttype.

    void changeScriptType(Highlighter::Types);

    //! Signal for toggling dockable.

    void toggleDock(EDockWidgetTypes,bool);

    //! Signal for redo-slot.

    void redo();

    //! Signal for undo-slot.

    void undo();

    //! Signal for save-layout slot.

    void saveLayout();

    //! Signal for load-layout slot.

    void loadLayout();

    //! Signal for new-project slot.

    void newProject();

    //! Signal for new-scene slot.

    void newScene();

    //! Signal for project-configured slot.

    void checkIfProjectConfigured();

    //! Signal for on-close slot.

    void onClose();

    //! Signal for saveing project.

    void saveProject();

    //! Signal for saving project.

    void saveProject(QString path);

    //! Signal for loading a project.

    void loadProject(QString path);

    //! Signal for default-layout slot.

    void setLayoutToDefault();

public slots:

    //! Slot for the undo signal.
    /*!
      If undo is possible, the undo button will be clickable.
     * \param undo Is undo possible?
     */

    void CanUndo(bool undo);

    //! Slot for the redo signal.
    /*!
      If redo is possible, the redo button will be clickable.
     * \param redo Is redo possible?
     */

    void CanRedo(bool redo);

private slots:

    //! Slot for the change script type signal.
    /*!
      If a user selects lua or python in the scripteditor, this slot will be called.
     * \param index The index of the combobox.
     */

    void on_comboBox_currentIndexChanged(int index);

    //! Closes the widget and so GEENIE.

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

    //! Slot to toggle the inspector as docked.
    /*!
     * \param arg1 Is docked?
     */

    void on_actionInspector_toggled(bool arg1);

    //! Slot to toggle the console as docked.
    /*!
     * \param arg1 Is docked?
     */

    void on_actionConsole_2_toggled(bool arg1);

    //! Slot to toggle the explorer as docked.
    /*!
     * \param arg1 Is docked?
     */

    void on_actionExplorer_toggled(bool arg1);

    //! Slot to toggle the assetwindow as docked.
    /*!
     * \param arg1 Is docked?
     */

    void on_actionAssets_toggled(bool arg1);

    //! Slot emits redo.

    void on_actionRedo_triggered();

    //! Slot emits undo.

    void on_actionUndo_triggered();

    //! Slot emits savelayout.

    void on_actionSave_triggered();

    //! Slot emits loadlayout.

    void on_actionLoad_triggered();

    //! Slot to create a new project or a new scene.

    void on_actionNew_triggered();

    //! Slot emits set layout to default.

    void on_actionLoad_default_layout_triggered();

    //! Emits on close.
    /*!
     * If the project is not saved yet, the user has now the option to do this.
     */

    void on_actionOpen_2_triggered();

    //! Emits check if project is configured and save project.
    /*!
     * If the project is or the directory in it is not empty, the project will be saved.
     */

    void on_actionSave_As_triggered();

    //! Checks if the project is configured and saves it.

    void on_actionSave_2_triggered();

private:

    //! Private variable stores if the current project is saved.

    bool _projectSaved;

    //! Private variable stores if the current project is configured.

    bool _projectConfigured;

    //! Private variable stores the mainwindow ui.

    Ui::GEENIEMainWindow *ui;
    SceneEditWidget* _sceneEditWidget;
};

#endif // GEENIEMAINWINDOW_H
