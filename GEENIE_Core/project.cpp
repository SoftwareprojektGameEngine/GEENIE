#include "core.h"
#define CALC_INDEX(index) ((index) % (MAX_NUM_USERACTIONS + 1))

Project::Project(EngineWrapper* engine, QString name) : fastEntityLookup(), scenes(), assets(), projectName(name) {
    for(int i=0; i < MAX_NUM_USERACTIONS+1;i++) {
        this->userActions[i] = nullptr;
    }

    this->firstActionIndex = 0;
    this->currentActionIndex = 0;

    this->engine = engine;
}

Project::~Project() {
    for(int i=0; i < MAX_NUM_USERACTIONS + 1; i++) {
        if(this->userActions[i] != nullptr) {
            //this->userActions[i]->~UserAction();
            delete this->userActions[i];
        }
    }

    foreach(Scene* scene, this->scenes) {
        delete scene;
    }
}

void Project::AddUserAction(UserAction *newAction) {
    // clear useractions in front (if any)
    if (this->CanRedo()) {
        int index = CALC_INDEX(this->firstActionIndex - 1);

        while(index != this->currentActionIndex) {
            if (this->userActions[index] != nullptr) {
                delete this->userActions[index];
                this->userActions[index] = nullptr;
            }

            index = CALC_INDEX(index - 1);
        }
    }

    // advance current index to next slot
    this->currentActionIndex = CALC_INDEX(this->currentActionIndex + 1);
    // add action in current slot
    this->userActions[this->currentActionIndex] = newAction;

    int nextIndex = CALC_INDEX(this->currentActionIndex + 1);
    if(nextIndex == this->firstActionIndex) {
        delete this->userActions[nextIndex];
        this->userActions[nextIndex] = nullptr;
        this->firstActionIndex = CALC_INDEX(this->firstActionIndex + 1);
    }

    newAction->Do();
}

bool Project::CanUndo() {
    return this->userActions[this->currentActionIndex] != nullptr;
    //return false;
}

bool Project::CanRedo() {
    return this->userActions[CALC_INDEX(this->currentActionIndex + 1)] != nullptr;
    //return false;
}

void Project::Undo() {
    if(this->CanUndo()) {
        this->userActions[this->currentActionIndex]->Undo();
        this->currentActionIndex = CALC_INDEX(this->currentActionIndex - 1);
    }
}

void Project::Redo() {
    if(this->CanRedo()) {
        this->currentActionIndex = CALC_INDEX(this->currentActionIndex + 1);
        this->userActions[this->currentActionIndex]->Do();
    }
}

void Project::AddEntity(Entity* entity) {
    if (this->scenes.contains(entity->GetParentID())) {
        this->scenes.value(entity->GetParentID())->AddEntity(entity);
    } else if(this->fastEntityLookup.contains(entity->GetParentID())) {
        this->fastEntityLookup.value(entity->GetParentID())->AddSubEntity(entity);
    } else {
        return;
    }

    this->fastEntityLookup.insert(entity->GetID(), entity);
}

Entity* Project::RemoveEntity(const QUuid& entityID) {
    Entity* removedEntity = this->FindEntity(entityID);

    if (removedEntity != nullptr) {
        QUuid parentID = removedEntity->GetParentID();

        if (this->scenes.contains(parentID)) {
            this->scenes.value(parentID)->RemoveEntity(entityID);
        } else if(this->fastEntityLookup.contains(parentID)) {
            this->fastEntityLookup.value(parentID)->RemoveSubEntity(entityID);
        }
    }

    return removedEntity;
}

Entity* Project::FindEntity(const QUuid& entityID) {
    return this->fastEntityLookup.value(entityID, nullptr);
}

void Project::AddScene(Scene* scene) {
    if (scene == nullptr) return;

    this->scenes.insert(scene->GetID(), scene);
}

Scene* Project::RemoveScene(const QUuid& sceneID) {
    Scene* scene = this->scenes.value(sceneID, nullptr);

    if (scene != nullptr) {
        this->scenes.remove(sceneID);
    }

    return scene;
}

Scene* Project::GetScene(const QUuid &sceneID) {
    return this->scenes.value(sceneID, nullptr);
}

QHashIterator<QUuid, Scene*> Project::GetScenes() {
    return QHashIterator<QUuid, Scene*>(this->scenes);
}

void Project::AddAsset(Asset *asset) {
    if (asset == nullptr) return;

    this->assets.insert(asset->GetID(), asset);
}

Asset* Project::GetAsset(const QUuid &assetID) {
    return this->assets.value(assetID, nullptr);
}

Asset* Project::RemoveAsset(const QUuid &assetID) {
    Asset* asset = this->assets.value(assetID, nullptr);

    if (asset != nullptr) {
        this->assets.remove(assetID);
    }

    return asset;
}

QHashIterator<QUuid, Asset*> Project::GetAssets() {
    return QHashIterator<QUuid, Asset*>(this->assets);
}

#include "../tinyxml/tinyxml.h"
#include <QFile>
#include "components.h"

void Project::load(QString &file)
{

}

void Project::ColorToXml(TiXmlElement *parent, Color color, QString &name)
{
    TiXmlElement* c = new TiXmlElement(name.toUtf8().data());
    c->SetAttribute("type","color");
    TiXmlElement* r = new TiXmlElement("r");
    TiXmlElement* g = new TiXmlElement("g");
    TiXmlElement* b = new TiXmlElement("b");
    TiXmlElement* a = new TiXmlElement("a");
    r->SetAttribute("value",QString::number(color.r).toUtf8().data());
    g->SetAttribute("value",QString::number(color.g).toUtf8().data());
    b->SetAttribute("value",QString::number(color.b).toUtf8().data());
    a->SetAttribute("value",QString::number(color.a).toUtf8().data());
    c->LinkEndChild(r);
    c->LinkEndChild(g);
    c->LinkEndChild(b);
    c->LinkEndChild(a);
    parent->LinkEndChild(c);
}

void Project::VectorToXml(TiXmlElement *parent, Vector vector, QString &name)
{
    TiXmlElement* v = new TiXmlElement(name.toUtf8().data());
    v->SetAttribute("type","vector");
    TiXmlElement* x = new TiXmlElement("x");
    TiXmlElement* y = new TiXmlElement("y");
    TiXmlElement* z = new TiXmlElement("z");
    TiXmlElement* w = new TiXmlElement("w");
    x->SetAttribute("value",QString::number(vector.x).toUtf8().data());
    y->SetAttribute("value",QString::number(vector.y).toUtf8().data());
    z->SetAttribute("value",QString::number(vector.z).toUtf8().data());
    w->SetAttribute("value",QString::number(vector.w).toUtf8().data());
    v->LinkEndChild(x);
    v->LinkEndChild(y);
    v->LinkEndChild(z);
    v->LinkEndChild(w);
    parent->LinkEndChild(v);
}

void Project::AddComponentInformationToXml(TiXmlElement *componentNode, Component *component)
{
    ComponentType type = component->GetType();
    switch(type)
    {
    case ComponentType::MODEL:
    {
        ModelComponent* c = dynamic_cast<ModelComponent*>(component);
        TiXmlElement* model = new TiXmlElement("model");
        model->SetAttribute("id",c->GetModel().toByteArray().data());
        componentNode->LinkEndChild(model);
        break;
    }
    case ComponentType::MATERIAL:
    {
        MaterialComponent* c = dynamic_cast<MaterialComponent*>(component);
        TiXmlElement* material = new TiXmlElement("material");
        material->SetAttribute("id",c->GetMaterial().toByteArray().data());
        material->SetAttribute("index",c->GetMaterialIndex());
        componentNode->LinkEndChild(material);
        break;
    }
    case ComponentType::POSITION:
    {
        PositionComponent* c = dynamic_cast<PositionComponent*>(component);
        VectorToXml(componentNode,c->GetPosition(),QString("position"));
        break;
    }
    case ComponentType::LIGHT:
    {
        LightComponent* c = dynamic_cast<LightComponent*>(component);
        ColorToXml(componentNode,c->GetAmbientColor(),QString("ambient"));
        ColorToXml(componentNode,c->GetDiffuseColor(),QString("diffuse"));
        ColorToXml(componentNode,c->GetSpecularColor(),QString("specular"));
        VectorToXml(componentNode,c->GetSpotlightDirection(),QString("spotlight"));
        TiXmlElement* lightSource = new TiXmlElement("lightsource");
        lightSource->SetAttribute("type",(int)c->GetLightSourceType());
        componentNode->LinkEndChild(lightSource);
        break;
    }
    case ComponentType::TEXTURE:
    {
        TextureComponent* c = dynamic_cast<TextureComponent*>(component);
        TiXmlElement* texture = new TiXmlElement("texture");
        texture->SetAttribute("id",c->GetTexture().toByteArray().data());
        texture->SetAttribute("index",c->GetTextureIndex());
        componentNode->LinkEndChild(texture);
        break;
    }
    case ComponentType::SOUND:
    {
        SoundComponent* c = dynamic_cast<SoundComponent*>(component);
        TiXmlElement* sound = new TiXmlElement("sound");
        sound->SetAttribute("id",c->GetSound().toByteArray().data());
        componentNode->LinkEndChild(sound);
        break;
    }
    case ComponentType::SHADER:
    {
        ShaderComponent* c = dynamic_cast<ShaderComponent*>(component);
        TiXmlElement* shader = new TiXmlElement("shader");
        shader->SetAttribute("id",c->GetShader().toByteArray().data());
        componentNode->LinkEndChild(shader);
        break;
    }
    case ComponentType::SCRIPT:
    {
        ScriptTriggerComponent* c = dynamic_cast<ScriptTriggerComponent*>(component);
        TiXmlElement* trigger = new TiXmlElement("trigger");
        trigger->SetAttribute("type",(int)c->GetTriggerType());
        TiXmlElement* script = new TiXmlElement("script");
        script->SetAttribute("id",c->GetScript().toByteArray().data());
        componentNode->LinkEndChild(trigger);
        componentNode->LinkEndChild(script);
        break;
    }
    }
}

TiXmlElement *Project::SubEntitiesToXml(Entity *entity)
{
    TiXmlElement* e = new TiXmlElement("entity");
    e->SetAttribute("id",entity->GetID().toByteArray().data());
    e->SetAttribute("parent",entity->GetParentID().toByteArray().data());
    if(entity->HasSubEntities())
    {
        TiXmlElement* subWrapper = new TiXmlElement("subentities");
        e->LinkEndChild(subWrapper);
        QHashIterator<QUuid, Entity*> it = entity->GetSubEntities();
        while(it.hasNext())
        {
            it.next();
            TiXmlElement* sub = SubEntitiesToXml(it.value());
            subWrapper->LinkEndChild(sub);
        }
    }
    if(entity->HasComponents())
    {
        QHashIterator<QUuid, Component*> it = entity->GetComponents();
        while(it.hasNext())
        {
            it.next();
            TiXmlElement* comp = new TiXmlElement("component");
            comp->SetAttribute("id",it.value()->GetID().toByteArray().data());
            comp->SetAttribute("type",(int)it.value()->GetType());
            AddComponentInformationToXml(comp,it.value());
            e->LinkEndChild(comp);
        }
    }
    return e;
}

void Project::save(QString &file)
{
    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0","utf8","");
    doc.LinkEndChild(decl);
    TiXmlElement* root = new TiXmlElement("project");
    root->SetAttribute("name",this->projectName.toUtf8().data());
    doc.LinkEndChild(root);
    for(const auto &scene: scenes)
    {
        TiXmlElement* sceneElement = new TiXmlElement("scene");
        sceneElement->SetAttribute("id",scene->GetID().toByteArray().data());
        QHashIterator<QUuid, Entity*> it = scene->GetEntities();
        if(scene->HasEntities())
        {
            while(it.hasNext())
            {
                it.next();
                TiXmlElement* entityElement = SubEntitiesToXml(it.value());
                sceneElement->LinkEndChild(entityElement);
            }
        }
        root->LinkEndChild(sceneElement);

    }
    for(const auto &asset : assets)
    {
        TiXmlElement* assetElement = new TiXmlElement("asset");
        assetElement->SetAttribute("id",asset->GetID().toByteArray().data());
        assetElement->SetAttribute("type",(int)asset->GetType());
        TiXmlElement* assetPath = new TiXmlElement("path");
        assetPath->LinkEndChild(new TiXmlText(asset->GetPath().toUtf8().data()));
        assetElement->LinkEndChild(assetPath);
        root->LinkEndChild(assetElement);
    }
    doc.SaveFile(file.toUtf8().data());
}
