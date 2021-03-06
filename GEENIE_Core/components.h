#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "core.h"

//TODO: add components
//! A position component.
/*!
 * This class represents a position component.
 */

class SHARED_EXPORT PositionComponent : public Component {
private:
    //!< The position vector (x, y, z)
    Vector _position;
    //!< The position component identifier
    QUuid _id;
    //!< The position component name
    QString _name;
public:
    //! The position component constructor
    PositionComponent(Vector pos, QUuid id = QUuid::createUuid(), QString name = QString("Position"));
    //! The position component destructor
    ~PositionComponent();

    //! Method to get the position component identifier
    QUuid GetID();
    //! Method which delivers you the position component type
    ComponentType GetType(); // <- gibt POSITION_COMPONENT zurück
    //! Method to get the position vector
    Vector GetPosition();
    //! Method to get type name, for entityview
    QString GetTypeName();
    //! Method to get component name
    QString name(){return _name;}
};

//! A light component.
/*!
 * This class represents a light component.
 */

class SHARED_EXPORT LightComponent : public Component {
private:
    //!< The light component identifier
    QUuid _id;
    //!< The light source type
    LightSourceType _lightSourceType;
    //!< The ambient color
    Color _ambientColor;
    //!< The diffuse color
    Color _diffuseColor;
    //!< The specular color
    Color _specularColor;
    //!< The spotlight direction vector
    Vector _spotlightDirection;
    //!< The light component name
    QString _name;
public:
    //! The light component constructor
    LightComponent(LightSourceType lightType, Color ambient, Color diffuse, Color specular, Vector spotlightDir = Vector{0.0f,0.0f,0.0f,0.0f}, QUuid id = QUuid::createUuid(), QString name = QString("Light"));
    ~LightComponent();

    //! Method to get the light component identifier
    QUuid GetID();
    //! Method to get the component type
    ComponentType GetType();
    //! Method which delivers you the ambient color
    Color GetAmbientColor();
    //! Method which delivers you the diffuse color
    Color GetDiffuseColor();
    //! Method which delivers you the specular color
    Color GetSpecularColor();
    //! Method which delivers you the spotlight direction vector
    Vector GetSpotlightDirection();
    //! Method which delivers you the light source type
    LightSourceType GetLightSourceType();
    //! Method to get type name, for entityview
    QString GetTypeName();
    //! Method to get component name
    QString name(){return _name;}
};

//! A model component.
/*!
 * This class represents a model component.
 */

class SHARED_EXPORT ModelComponent : public Component {
private:
    //!< The model component identifier
    QUuid _id;
    //!< The model identifier
    QUuid _modelID;
    //!< The model component name
    QString _name;
public:
    //! Constructor of the model components
    ModelComponent(QUuid modelID, QUuid id = QUuid::createUuid(), QString name = QString("Model"));
    ~ModelComponent();

    //! Method to get the model component id
    QUuid GetID();
    //! Method to get the component type
    ComponentType GetType();
    //! Method which delivers you the model id
    QUuid GetModel();
    //! Method to get type name, for entityview
    QString GetTypeName();
    //! Method to get component name
    QString name(){return _name;}
};

//! A material component.
/*!
 * This class represents a material component.
 */

class SHARED_EXPORT MaterialComponent : public Component {
private:
    //!< The material component id
    QUuid _id;
    //!< The material id
    QUuid _materialID;
    //!< The material index
    int _materialIndex;
    //!< The material component name
    QString _name;
public:
    //! Constructor of the material components
    MaterialComponent(QUuid matID, int matIndex, QUuid id = QUuid::createUuid(), QString name = QString("Material"));
    ~MaterialComponent();

    //! Method to get the material component id
    QUuid GetID();
    //! Method to get the component type
    ComponentType GetType();
    //! Method to get the material id
    QUuid GetMaterial();
    //! Method to get the material index
    int GetMaterialIndex();
    //! Method to get type name, for entityview
    QString GetTypeName();
    //! Method to get component name
    QString name(){return _name;}
};

//! A shader component.
/*!
 * This class represents a shader component.
 */

class SHARED_EXPORT ShaderComponent : public Component {
private:
    //!< The shader component id
    QUuid _id;
    //!< The shader id
    QUuid _shaderID;
    //!< The shader component name
    QString _name;
public:
    //! The constructor of the shader components
    ShaderComponent(QUuid shaderId,QUuid id = QUuid::createUuid(), QString name = QString("Shader"));
    ~ShaderComponent();

    //! Method to get the shader components id
    QUuid GetID();
    //! Method to get the component type
    ComponentType GetType();
    //! Method to get the shader id
    QUuid GetShader();
    //! Method to get type name, for entityview
    QString GetTypeName();
    //! Method to get component name
    QString name(){return _name;}
};

//! A texture component.
/*!
 * This class represents a texture component.
 */

class SHARED_EXPORT TextureComponent : public Component {
private:
    //!< The texture components id
    QUuid _id;
    //!< The texture id
    QUuid _textureID;
    //!< The texture index
    int _textureIndex;
    //!< The texture component name
    QString _name;
public:
    //! Constructor of the texture components
    TextureComponent(QUuid texID, int texIndex, QUuid id = QUuid::createUuid(),QString name = QString("Texture"));
    ~TextureComponent();

    //! Method to get the texture components id
    QUuid GetID();
    //! Method to get the component type
    ComponentType GetType();
    //! Method to get the texture id
    QUuid GetTexture();
    //! Method to get the texture index
    int GetTextureIndex();
    //! Method to get type name, for entityview
    QString GetTypeName();
    //! Method to get component name
    QString name(){return _name;}
};

enum ScriptTrigger {
    // TODO: insert plausible values
    SCRIPTTRIGGER_DEFAULT
};

//! A script-trigger component.
/*!
 * This class represents a script-trigger component.
 */

class SHARED_EXPORT ScriptTriggerComponent : public Component {
private:
    //!< The script-trigger component id
    QUuid _id;
    //!< The script-trigger
    ScriptTrigger _trigger;
    //!< The script-trigger id
    QUuid _scriptID;
    //!< The script trigger component name
    QString _name;
public:
    //! Constructor of the script-trigger components
    ScriptTriggerComponent(ScriptTrigger trigger, QUuid scriptID, QUuid id = QUuid::createUuid(), QString name = QString("Script"));
    ~ScriptTriggerComponent();

    //! Method to get the script-trigger components id
    QUuid GetID();
    //! Method to get the components type
    ComponentType GetType();
    //! Method to get the script-trigger type
    ScriptTrigger GetTriggerType();
    //! Method to get the script-trigger id
    QUuid GetScript();
    //! Method to get type name, for entityview
    QString GetTypeName();
    //! Method to get component name
    QString name(){return _name;}
};

//! A sound component.
/*!
 * This class represents a sound component.
 */

class SHARED_EXPORT SoundComponent : public Component {
private:
    //!< The sound component id
    QUuid _id;
    //!< The sound id
    QUuid _soundID;
    //!< The sound component name
    QString _name;
public:
    //!< Constructor of the sound components
    SoundComponent(QUuid sound, QUuid id = QUuid::createUuid(), QString name = QString("Sound"));
    ~SoundComponent();

    //! Method to get the sound components id
    QUuid GetID();
    //! Method to get the components type
    ComponentType GetType();
    //! Method to get the sound id
    QUuid GetSound();
    //! Method to get type name, for entityview
    QString GetTypeName();
    //! Method to get component name
    QString name(){return _name;}
};

#endif // COMPONENTS_H
