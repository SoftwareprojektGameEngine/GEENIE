#include "components.h"

PositionComponent::PositionComponent(Vector pos, QUuid id) :
    _position(pos),
    _id(id)
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

LightComponent::LightComponent(LightSourceType lightType, Color ambient, Color diffuse, Color specular, Vector spotlightDir, QUuid id) :
    _id(id),
    _lightSourceType(lightType),
    _ambientColor(ambient),
    _diffuseColor(diffuse),
    _specularColor(specular),
    _spotlightDirection(spotlightDir)
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


ModelComponent::ModelComponent(QUuid modelID, QUuid id) :
    _id(id),
    _modelID(modelID)
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

MaterialComponent::MaterialComponent(QUuid matID, int matIndex, QUuid id) :
    _id(id),
    _materialID(matID),
    _materialIndex(matIndex)
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

ShaderComponent::ShaderComponent(QUuid id):
    _id(id)
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

TextureComponent::TextureComponent(QUuid texID, int texIndex, QUuid id) :
    _id(id),
    _textureID(texID),
    _textureIndex(texIndex)
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

ScriptTriggerComponent::ScriptTriggerComponent(ScriptTrigger trigger, QUuid scriptID, QUuid id):
    _id(id),
    _trigger(trigger),
    _scriptID(scriptID)
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

SoundComponent::SoundComponent(QUuid sound, QUuid id) :
    _id(id),
    _soundID(sound)
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
