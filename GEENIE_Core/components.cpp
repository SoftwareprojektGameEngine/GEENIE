#include "components.h"

ModelComponent::ModelComponent(QUuid modelID, QUuid id) :
    _id(id),
    _modelID(modelID)
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

LightComponent::LightComponent(LightSourceType lightType, Color ambient, Color diffuse, Color specular, Vector spotlightDir, QUuid id) :
    _id(id),
    _lightSourceType(lightType),
    _ambientColor(ambient),
    _diffuseColor(diffuse),
    _specularColor(specular),
    _spotlightDirection(spotlightDir)
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

QUuid ScriptTriggerComponent::GetID(){
 return _id;
}

ComponentType ScriptTriggerComponent::GetType(){
    return ComponentType::ScriptTrigger;
}

ScriptTrigger ScriptTriggerComponent::GetTriggerType(){
    return _trigger;
}

QUuid ScriptTriggerComponent::GetScript(){
    return _scriptID;
}

ScriptTriggerComponent::ScriptTriggerComponent(ScriptTrigger trigger, QUuid scriptID, QUuid id):
    _id(id),
    _trigger(trigger),
    _scriptID(scriptID)
{
}
