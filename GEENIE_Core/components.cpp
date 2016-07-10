#include "components.h"

PositionComponent::PositionComponent(Vector pos, QUuid id, QString name) :
    _position(pos),
    _id(id),
    _name(name)
{
}

PositionComponent::~PositionComponent(){}

QUuid PositionComponent::GetID()
{
    return _id;
}

ComponentType PositionComponent::GetType()
{
    return ComponentType::POSITION;
}

Vector PositionComponent::GetPosition()
{
    return _position;
}

QString PositionComponent::GetTypeName()
{
    return QString("Position");
}

LightComponent::LightComponent(LightSourceType lightType, Color ambient, Color diffuse, Color specular, Vector spotlightDir, QUuid id, QString name) :
    _id(id),
    _lightSourceType(lightType),
    _ambientColor(ambient),
    _diffuseColor(diffuse),
    _specularColor(specular),
    _spotlightDirection(spotlightDir),
    _name(name)
{
}

LightComponent::~LightComponent()
{
}

QUuid LightComponent::GetID()
{
    return _id;
}

ComponentType LightComponent::GetType()
{
    return ComponentType::LIGHT;
}

Color LightComponent::GetAmbientColor()
{
    return _ambientColor;
}

Color LightComponent::GetDiffuseColor()
{
    return _diffuseColor;
}

Color LightComponent::GetSpecularColor()
{
    return _specularColor;
}

Vector LightComponent::GetSpotlightDirection()
{
    return _spotlightDirection;
}

LightSourceType LightComponent::GetLightSourceType()
{
    return _lightSourceType;
}

QString LightComponent::GetTypeName()
{
    return QString("Light");
}

ModelComponent::ModelComponent(QUuid modelID, QUuid id, QString name) :
    _id(id),
    _modelID(modelID),
    _name(name)
{
}

ModelComponent::~ModelComponent()
{
}

QUuid ModelComponent::GetID()
{
    return _id;
}

QUuid ModelComponent::GetModel()
{
    return _modelID;
}

ComponentType ModelComponent::GetType()
{
    return ComponentType::MODEL;
}

QString ModelComponent::GetTypeName()
{
    return QString("Model");
}

MaterialComponent::MaterialComponent(QUuid matID, int matIndex, QUuid id, QString name) :
    _id(id),
    _materialID(matID),
    _materialIndex(matIndex),
    _name(name)
{
}

MaterialComponent::~MaterialComponent(){}

QUuid MaterialComponent::GetID()
{
    return _id;
}

ComponentType MaterialComponent::GetType()
{
    return ComponentType::MATERIAL;
}

QUuid MaterialComponent::GetMaterial()
{
    return _materialID;
}

int MaterialComponent::GetMaterialIndex()
{
    return _materialIndex;
}

QString MaterialComponent::GetTypeName()
{
    return QString("Material");
}

ShaderComponent::ShaderComponent(QUuid shaderId, QUuid id, QString name):
    _id(id),
    _shaderID(shaderId),
    _name(name)
{
}
ShaderComponent::~ShaderComponent(){}

QUuid ShaderComponent::GetID(){
    return _id;
}

ComponentType ShaderComponent::GetType(){
    return ComponentType::SHADER;
}

QUuid ShaderComponent::GetShader(){
    return _shaderID;
}

QString ShaderComponent::GetTypeName()
{
    return QString("Shader");
}

TextureComponent::TextureComponent(QUuid texID, int texIndex, QUuid id, QString name) :
    _id(id),
    _textureID(texID),
    _textureIndex(texIndex),
    _name(name)
{
}

TextureComponent::~TextureComponent()
{
}

QUuid TextureComponent::GetID()
{
    return _id;
}

ComponentType TextureComponent::GetType()
{
    return ComponentType::TEXTURE;
}

QUuid TextureComponent::GetTexture()
{
    return _textureID;
}

int TextureComponent::GetTextureIndex()
{
    return _textureIndex;
}

QString TextureComponent::GetTypeName()
{
    return QString("Texture");
}

ScriptTriggerComponent::ScriptTriggerComponent(ScriptTrigger trigger, QUuid scriptID, QUuid id, QString name):
    _id(id),
    _trigger(trigger),
    _scriptID(scriptID),
    _name(name)
{
}

ScriptTriggerComponent::~ScriptTriggerComponent()
{
}

QUuid ScriptTriggerComponent::GetID(){
 return _id;
}

ComponentType ScriptTriggerComponent::GetType(){
    return ComponentType::SCRIPT;
}

ScriptTrigger ScriptTriggerComponent::GetTriggerType(){
    return _trigger;
}

QUuid ScriptTriggerComponent::GetScript(){
    return _scriptID;
}

QString ScriptTriggerComponent::GetTypeName()
{
    return QString("Scripttrigger");
}

SoundComponent::SoundComponent(QUuid sound, QUuid id, QString name) :
    _id(id),
    _soundID(sound),
    _name(name)
{
}

SoundComponent::~SoundComponent(){}

QUuid SoundComponent::GetID()
{
    return _id;
}

ComponentType SoundComponent::GetType()
{
    return ComponentType::SOUND;
}

QUuid SoundComponent::GetSound()
{
    return _soundID;
}

QString SoundComponent::GetTypeName()
{
    return QString("Sound");
}
