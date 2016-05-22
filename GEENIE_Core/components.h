#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "core.h"

//TODO: add components

class SHARED_EXPORT PositionComponent {
private:
    Vector position;
    QUuid id;
public:
    PositionComponent(Vector pos, QUuid id = QUuid::createUuid());
    ~PositionComponent();

    QUuid GetID();
    ComponentType GetType(); // <- gibt POSITION_COMPONENT zurück
    Vector GetPosition();
};

class SHARED_EXPORT LightComponent {
private:
    QUuid id;
    LightSourceType lightSourceType;
    Color ambientColor;
    Color diffuseColor;
    Color specularColor;
    Vector spotlightDirection;
public:
    LightComponent(LightSourceType lightType, Color ambient, Color diffuse, Color specular, Vector spotlightDir = Vector{0.0f,0.0f,0.0f,0.0f}, QUuid id = QUuid::createUuid());
    ~LightComponent();

    QUuid GetID();
    ComponentType GetType();
    Color GetAmbientColor();
    Color GetDiffuseColor();
    Color GetSpecularColor();
    Vector GetSpotlightDirection();
    lightSourceType GetLightSourceType();
};

class SHARED_EXPORT ModelComponent {
private:
    QUuid id;
    QUuid modelID;
public:
    ModelComponent(QUuid modelID, QUuid id = QUuid::createUuid());
    ~ModelComponent();

    QUuid GetID();
    ComponentType GetType();
    QUuid GetModel();
};

class SHARED_EXPORT MaterialComponent {
private:
    QUuid id;
    QUuid materialID;
    int materialIndex;
public:
    MaterialComponent(QUuid matID, int matIndex, QUuid id = QUuid::createUuid());
    ~MaterialComponent();

    QUuid GetID();
    ComponentType GetType();
    QUuid GetMaterial();
    int GetMaterialIndex();
};

class SHARED_EXPORT ShaderComponent {
private:
    QUuid id;
    QUuid shaderID;
public:
    ShaderComponent(QUuid id = QUuid::createUuid());
    ~ShaderComponent();

    QUuid GetID();
    ComponentType GetType();
    QUuid GetShader();
};

class SHARED_EXPORT TextureComponent {
private:
    QUuid id;
    QUuid textureID;
    int textureIndex;
public:
    TextureComponent(QUuid texID, int texIndex, QUuid id = QUuid::createUuid());
    ~TextureComponent();

    QUuid GetID();
    ComponentType GetType();
    QUuid GetTexture();
    int GetTextureIndex();
};

enum ScriptTrigger {
    // TODO: insert plausible values
};

class SHARED_EXPORT ScriptTriggerComponent {
private:
    QUuid id;
    ScriptTrigger trigger;
    QUuid scriptID;
public:
    ScriptTriggerComponent(ScriptTrigger trigger, QUuid scriptID, QUuid id = QUuid::createUuid());
    ~ScriptTriggerComponent();

    QUuid GetID();
    ComponentType GetType();

    ScriptTrigger GetTriggerType();
    QUuid GetScript();
};

class SHARED_EXPORT SoundComponent {
private:
    QUuid id;
    QUuid soundID;
public:
    SoundComponent(QUuid sound, QUuid id = QUuid::createUuid());
    ~SoundComponent();

    QUuid GetID();
    ComponentType GetType();
    QUuid GetSound();
};

#endif // COMPONENTS_H
