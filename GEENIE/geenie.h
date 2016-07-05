#ifndef GEENIE_H
#define GEENIE_H

#include <QObject>
#include <QMap>
#include <QString>
#include "common.h"
#include "scripthighlighter.h"
#include "sceneexplorer.h"
#include "enginewrapper.h"
#include "components.h"
#include "addcomponentdialog.h"
#include "moveentitydialog.h"

class GEENIEMainWindow;
class QDockWidget;
class Project;
class Entity;

/*!
 * \class GEENIE geenie.h
 * \brief The GEENIE class. Controls the data-exchange between core and widgets.
 */

class GEENIE : public QObject
{
    Q_OBJECT
public:

    //! Constructor
    /*!
     * The "main"-method of our editor. Creates the dockable-widgets, set their titles, creates a log-path, loads the session-save file and connects all signals and slots.
     * \param parent The parent object.
     */

    explicit GEENIE(QObject *parent = 0);

    //! Deconstructor.
    /*!
    Deletes the timer of the autosave.
    */

    ~GEENIE();

    //! Insert dockable-widget.
    /*!
     * Create and insert a dockable widget to the editor.
     * \param type Available options: AssetsWidget, EntitiesWidget, InspectorWidget, LoggerWidget, ScriptEditorWidget.
     * \param widget The needed child-widget. Note that a dockable-widget is just a wrappe for the child-widget.
     * \param show Shows or hides the dockable-widget.
     * \param area The area where the widget is docked in.
     * \param floating Should the widget be docked or floated(an independend window)?
     * \param width The width of the widget.
     * \param height The height of the widget.
     * \param x The x location.
     * \param y The y location.
     */

    void insertDockWidget(EDockWidgetTypes type, QWidget* widget, bool show = false, Qt::DockWidgetArea area = Qt::BottomDockWidgetArea, bool floating = false, int width = 200, int height = 200, int x = 0, int y = 0);

    //! Moving method for the dockable-widgets.
    /*!
     * Destroys and creates a new widget on the given coordinates.
     * \param type Available options: AssetsWidget, EntitiesWidget, InspectorWidget, LoggerWidget, ScriptEditorWidget.
     * \param show Shows or hides the dockable-widget.
     * \param area The area where the widget is docked in.
     * \param floating Should the widget be docked or floated(an independend window)?
     * \param width The width of the widget.
     * \param height The height of the widget.
     * \param x The x location.
     * \param y The y location.
     */

    void moveDockWidget(EDockWidgetTypes type, bool show = false, Qt::DockWidgetArea area = Qt::BottomDockWidgetArea, bool floating = false, int width = 200, int height = 200, int x = 0, int y = 0);

private:
    ENTITY_DATA_ME GetEntities(Entity *e,QUuid id);
    int MapType(int);

    //! Entity to inspector method.
    /*!
     * Adds an entity to the inspector.
     * \param e An entity.
     */

    void EntityToInspector(Entity* e);

    //! Default-session method.
    /*!
     * Restores all widgets to its default places.
     * \param inspector The inspector-widget.
     * \param asset The asset-widget.
     * \param entities The entity-widget.
     */

    void defaultSession(QWidget* inspector, QWidget* asset, QWidget* entities);

    //! Create the titles of the dock-widgets.

    void createDockWidgetTitles();

    //! Method to fill the sceneexplorer for the first time.
    /*!
     * Reads the current project. If it's empty, the sceneexplorer will show "(No project configured)". Else it will read the GEENIE-file and fills the sceneexplorer with all available scenes and entities.
     */

    void fillSceneExplorer();

    //! Fills the sceneexplorer with subentities and components.

    ENTITY_DATA fillSceneExplorerWithEntities(Entity* e);

    //! Fills and the Assetwidget with assets.
    /*!
     * Gets its data from the current project file. Is used for initially filling the assetwidget with assets or to update it.
     */

    void fillAssetWidget();

    //! List for the dock-widgets.

    QMap<EDockWidgetTypes, QDockWidget*> _dockWidgets;

    //! List for the dock-widget coordinates.

    QMap<EDockWidgetTypes, QRect> _dockWidgetsCoords;

    //! List for the dock-widget titles.

    QMap<EDockWidgetTypes, QString> _dockWidgetsTitles;

    //! Private variable for the mainwindow.

    GEENIEMainWindow* _mainWindow;

    //! Private variable for the scripthighlighter.

    ScriptHighlighter* _highlighter;

    //! Private string for the current layoutname.

    QString _layoutName;

    //! The private timer for autosaving.

    QTimer* _saveTimer;

    //! Private variable for the current project.

    Project* _project;
    EngineWrapper* _engine;


private slots:

    //! Slot for saving the session file.
    /*!
     * Saves the session file in a html document.
     */

    void saveSession();

    //! Slot for loading an assetlist.
    /*!
     * Loads an assetlist from a project for the assetwindow.
     * \param dialog Not needed yet.
     * \param type The assettype.
     */

    void LoadAssetList(AddComponentDialog* dialog,int type);

    //! Slot for set all widgets to default.

    void SetDefaultLayout();

    //! Slot for closing GEENIE.
    /*!
     * If there are some unsaved changes in a project the user has the option now to save them.
     */

    void mainWindowOnClose();

    //! Slot for the setting the current project as configured.

    void ProjectConfigured();

    //! Slot for saving a layout.
    /*!
     * Saves layout in a html-file
     */

    void saveLayout();

    //! Loads layout from a html-file.

    void loadLayout();

    //! Unsets the inspector.

    void UnsetInspector();

    //! Changes the script-type for the script highlighting.
    /*!
     * type The highlighter type.
     */

    void changeScriptType(Highlighter::Types type);

    //! Explorer-inspector synchronisation.
    /*!
     * Pushes entity-data to the inspector.
     * \param id The id of the entity.
     */

    void ExplorerClicked(QUuid id,se::ItemType);

    //! Slot for toggling inspector to be docked.
    /*!
     * \param show Is the inspector visible?
     */

    void toggleInspectorDock(bool show);

    //! Slot for toggling explorer to be docked.
    /*!
     * \param show Is the explorer visible?
     */

    void toggleExplorerDock(bool show);

    //! Slot for toggling console to be docked.
    /*!
     * \param show Is the console visible?
     */

    void toggleConsoleDock(bool show);

    //! Slot for toggling assetwindow to be docked.
    /*!
     * \param show Is the assetwindow visible?
     */

    void toggleAssetDock(bool show);

    //! Slot for toggling all widgets to be docked.
    /*!
     * \param show Is the widget visible?
     */

    void toggleDock(EDockWidgetTypes type,bool show);

    //! Undo method.

    void undo();

    //! Redo method.

    void redo();

    //! Dialog for adding an entity
    /*!
     * Addind an entity to the explorer.
     * \param parentId The id of the parent entity.
     * \param type Not used yet.
     */

    void AddEntity(QUuid parentId,se::ItemType type);

    //! Dialog for moving an entity
    void MoveEntity(QUuid id);

    //! Dialog for adding a new scene to explorer.

    void AddScene();

    //! Dialog for renaming a scene.
    /*!
     * \param id The id of the scene.
     */

    void RenameScene(QUuid id);

    //! Dialog for deleting a scene.
    /*!
     * \param id The id of the scene.
     */

    void DeleteScene(QUuid id);


    //! Dialog for deleting a component of an entity.
    /*!
     * \param id The id of the component.
     * \param parentId The parent id.
     */

    void DeleteComponent(QUuid id, QUuid parentId);

    //! Dialog for changing components values.
    /*!
     * \param id The component id.
     * \param parentId The parent id.
     * \param component The component itself.
     */

    void ModifyComponent(QUuid id, QUuid parentId, Component* component);

    //! Dialog for adding a component.
    /*!
     * \param parentId The parent id (entity).
     */

    void AddComponent(QUuid parentId);

    //! Dialog for deleting an entity.
    /*!
     * \param id The entity id.
     */

    void DeleteEntity(QUuid id);

    //! Dialog for renaming an entity.
    /*!
     * \param id The entity id.
     * \param name The new name.
     */

    void RenameEntity(QUuid id, QString name);

    //! Dialog for creating a new project.

    void NewProject();

    //! Slot for saving an almost saved project.

    void SaveProject();

    //! Slot for saving a never saved project.
    /*!
     * \param path The location of the project.
     */

    void SaveProject(QString path);

    //! Slot for loading a project from a specific location.
    /*!
     * \param path The location of the project.
     */

    void LoadProject(QString path);

    //! Slot for adding an asset to the project.
    /*!
     * \param path The path to the asset.
     * \param type The asset type.
     */

    void AddAsset(QString path, AssetType type);

    //! Slot for deleting an asset from the project.
    /*!
     * \param id The id of the asset.
     */

    void DeleteAsset(QUuid id);

signals:
public slots:
};

#endif // GEENIE_H
