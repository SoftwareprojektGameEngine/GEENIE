#ifndef CORE_H
#define CORE_H

#include "geenie_core_global.h"
#include "core_base.h"
#include <QString>
#include <QUuid>
#include <QHash>

#define MAX_NUM_USERACTIONS 20

/*!
 * \brief The ComponentType enum
 */
enum ComponentType {
    MODEL,
    MATERIAL,
    POSITION,
    LIGHT,
    TEXTURE,
    SOUND,
    SHADER,
    SCRIPT
};

/*!
 * \brief The LightSourceType enum
 */
enum LightSourceType : int {
    AMBIENT = 0x01, //!< The light source contains ambient light information
    DIFFUSE = 0x02, //!< The light source contains diffuse light information
    SPOT = 0x04,  //!< The light source contains spot light information
    SPECULAR = 0x08, //!< The light source contains specular light information
};

/*!
 * \brief The UserAction class
 *
 * The UserAction class is an interface for state-changing operations on a Project instance.
 */
class SHARED_EXPORT UserAction {
public:
    //! The constructor.
    UserAction() {}
    //! The destructor.
    virtual ~UserAction() {}

    //! Executes the action.
    virtual void Do() = 0;
    //! Reverts the action.
    virtual void Undo() = 0;
};

/*!
 * \brief The Component class
 *
 * Note: This is an abstract base class and can't be instantiated directly.
 */
class SHARED_EXPORT Component {
public:
    //! The constructor
    Component() {}
    //! The destructor
    virtual ~Component() {}

    //! GetID returns the component's ID
    virtual QUuid GetID() = 0;
    //! GetType returns the component's type
    virtual ComponentType GetType() = 0;
    //! GetTypeName returns the component's type name
    virtual QString GetTypeName() = 0;
    //! name returns the component's name
    virtual QString name() = 0;
};

/*!
 * \brief The Entity class
 */
class SHARED_EXPORT Entity {
private:
    //! id is the id of the entity
    QUuid id;
    //! parentID is the id of the parent of the entity
    QUuid parentID;

    //! components contains all the components associated with this entity
    QHash<QUuid, Component*> components;
    //! subEntities contains all direct subentities of this entity
    QHash<QUuid, Entity*> subEntities;
    //! name contains entity name
    QString _name;
public:
    /*!
     * \brief Entity
     * \param parentID the id of the parent entity
     * \param id the id of this entity (for serialization purposes)
     * \param name for display purposes
     */
    Entity(QUuid parentID, QUuid id = QUuid::createUuid(), QString name = QString("Entity"));
    //! The destructor
    ~Entity();

    //! GetID returns the id of this entity
    QUuid GetID();
    //! GetParentID returns the id of the parent entity
    QUuid GetParentID();

    /*!
     * \brief GetSubEntity tries to find a subentity by its id
     * \param entityID the id of the subentity
     * \return the subentity if found, otherwise nullptr
     */
    Entity* GetSubEntity(const QUuid& entityID);
    /*!
     * \brief GetSubEntities
     * \return a java-style iterator over all subEntities
     */
    QHashIterator<QUuid, Entity*> GetSubEntities();
    /*!
     * \brief HasSubEntities
     * \return true if this entity has subentities
     */
    bool HasSubEntities();
    /*!
     * \brief AddSubEntity adds a subentity to this entity
     * \param entity the subentity to be added
     */
    void AddSubEntity(Entity* entity);
    /*!
     * \brief RemoveSubEntity removes a subentity from this entity
     * \param entityID the id of the subentity to be removed
     * \return the removed entity
     */
    Entity* RemoveSubEntity(const QUuid& entityID);

    /*!
     * \brief GetComponent tries to find a component of this entity by id
     * \param componentID the component's id
     * \return the component if found, otherwise nullptr
     */
    Component* GetComponent(const QUuid& componentID);
    /*!
     * \brief GetComponents
     * \return a java-style iterator over all components of this entity
     */
    QHashIterator<QUuid, Component*> GetComponents();
    /*!
     * \brief AddComponent adds a component to this entity
     * \param component the component to be added
     */
    void AddComponent(Component* component);
    /*!
     * \brief RemoveComponent removes a component from this entity
     * \param componentID the component's id
     * \return the removed component
     */
    Component* RemoveComponent(const QUuid& componentID);
    /*!
     * \brief HasComponents
     * \return true if this entity has any components
     */
    bool HasComponents();
    /*!
     * \brief Returns the name of the entity
     * \return name
     */
    QString name(){return _name;}
    /*!
     * \brief Sets the entity name
     * \param name
     */
    void setName(QString name){_name = name;}
};

/*!
 * \brief The Scene class
 */
class SHARED_EXPORT Scene {
private:
    /*!
     * \brief id
     */
    QUuid id;
    /*!
     * \brief entities
     */
    QHash<QUuid, Entity*> entities;
    /*!
     * \brief _name
     */
    QString _name;
public:
    /*!
     * \brief Scene
     * \param id
     * \param name
     */
    Scene(QUuid id = QUuid::createUuid(), QString name = QString("Scene"));
    //! The destructor
    ~Scene();

    /*!
     * \brief GetID
     * \return
     */
    QUuid GetID();

    /*!
     * \brief GetEntity
     * \param entityID
     * \return
     */
    Entity* GetEntity(const QUuid& entityID);
    /*!
     * \brief GetEntities
     * \return
     */
    QHashIterator<QUuid, Entity*> GetEntities();
    /*!
     * \brief AddEntity
     * \param entity
     */
    void AddEntity(Entity* entity);
    /*!
     * \brief RemoveEntity
     * \param entityID
     * \return
     */
    Entity* RemoveEntity(const QUuid& entityID);
    /*!
     * \brief HasEntities
     * \return
     */
    bool HasEntities();
    /*!
     * \brief Returns the name of the scene
     * \return name
     */
    QString name(){return _name;}
    /*!
     * \brief Sets the scene name
     * \param name
     */
    void setName(QString name){_name = name;}
};

#include "enginewrapper.h"
#include <QObject>

class TiXmlElement;

/*!
  The Project class. Used to contain all state of a project.
  */
class SHARED_EXPORT Project : public QObject {

    Q_OBJECT

private:
    //! Ringbuffer structure of UserActions
    UserAction* userActions[MAX_NUM_USERACTIONS + 1];
    //! The index of the last action done
    int currentActionIndex;
    //! The index of the "first" (= current oldest) action in the ringbuffer
    int firstActionIndex;
    //! The collection of scenes.
    QHash<QUuid, Scene*> scenes;
    //! A collection of entities (used to speed up entity lookup).
    QHash<QUuid, Entity*> fastEntityLookup;
    //! The collection of assets.
    QHash<QUuid, Asset*> assets;
    EngineWrapper* engine;
    //! The project name
    QString projectName;
    //! The project directory
    QString projectPath;
    //! The project save status
    bool saved;
    //! Helper function for subentities
    TiXmlElement *SubEntitiesToXml(Entity* entity);
    //! Helper function for components
    void AddComponentInformationToXml(TiXmlElement* componentNode, Component* component);
    //! Helper function for vectors
    void VectorToXml(TiXmlElement* parent, Vector vector, QString& name);
    //! Helper function for colors
    void ColorToXml(TiXmlElement* parent, Color color, QString& name);
    //! Helper function for loading entities
    void XmlToEntity(TiXmlElement* e);
    //! Helper function for loading components
    void XmlToComponent(TiXmlElement* c, Entity* e);
    //! Helper function for loading vectors
    Vector XmlToVector(TiXmlElement* parent, QString& name);
    //! Helper function for loading colors
    Color XmlToColor(TiXmlElement* parent, QString& name);

public:
    //! The project constructor.
    Project(EngineWrapper* engine, QString name = QString("untitled"), QString path = QString(""));
    //! The project destructor.
    ~Project();

    //! Adds a UserAction.
    //! \param newAction the action to be added
    void AddUserAction(UserAction* newAction);
    //! Signals whether a UserAction can be undone.
    bool CanUndo();
    //! Signals whether a UserAction can be redone.
    bool CanRedo();
    //! Executes the next UserAction.
    void Redo();
    //! Reverts the previous UserAction.
    void Undo();

    //! Adds an entity to the project.
    //! \param entity the entity to be added
    void AddEntity(Entity* entity);
    //! Removes the specified entity from the project.
    //! \param entityID the id of the entity to be removed
    Entity* RemoveEntity(const QUuid& entityID);
    //! Searches the specified entity in the project.
    //! \param entityID the id of the entity
    Entity* FindEntity(const QUuid& entityID);

    //! Adds a scene to the project.
    //! \param scene a pointer to the scene
    void AddScene(Scene* scene);
    //! Returns the specified scene.
    //! \param sceneID the id of the scene
    //! \return a pointer to the scene if found, nullptr otherwise
    Scene* GetScene(const QUuid& sceneID);
    //! Removes the specified scene from the project.
    //! \param sceneID the id of the scene object
    //! \return a pointer to the removed scene
    Scene* RemoveScene(const QUuid& sceneID);
    //! Returns an iterator over all scenes.
    QHashIterator<QUuid, Scene*> GetScenes();

    //! Adds an asset to the project.
    void AddAsset(Asset* asset);
    //! Returns the specified asset.
    Asset* GetAsset(const QUuid& assetID);
    //! Removes the specified asset from the project.
    Asset* RemoveAsset(const QUuid& assetID);
    //! Returns an iterator over all assets.
    QHashIterator<QUuid, Asset*> GetAssets();
    //! Loads project from specified file
    void load(QString& file);
    //! Saves project to specified file
    void save(QString& file = QString(""));
    //! Returns project name
    QString name();
    //! Returns project path
    QString path();
    //! Returns project path with filename
    QString file();
    //! Returns asset path
    QString assetPath();
    //! Returns if there are unsaved changes
    bool unsavedChanges(){return !saved;}

public slots:
private slots:
signals:
    /*!
     * \brief Signals if there can be something done
     */
    void CanRedoSignal(bool);
    /*!
     * \brief Signals if there can be something done
     */
    void CanUndoSignal(bool);
};

#endif // CORE_H
