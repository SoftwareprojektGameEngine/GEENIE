#include "osgwrapper.h"

#include "osgDB/ReadFile"
#include "osgwidget.h"
#include <QDebug>

OSGWrapper::OSGWrapper() : models(), textures(), materials() {

}

OSGWrapper::~OSGWrapper() {

}

ResHandle OSGWrapper::CreateTexture(const TextureAsset &textureAsset) {
    osg::Image* image = osgDB::readImageFile(textureAsset.GetPath().toStdString());

    if (image != nullptr) {
        image->ref();
        textures.insert(textureAsset.GetID(), image);
        return (ResHandle)image;
    }

    return nullptr;
}

ResHandle OSGWrapper::UpdateTexture(ResHandle textureHandle, const TextureAsset &textureAsset) {
    osg::Image* texture = (osg::Image*)textureHandle;

    if (texture != nullptr && !textures.key(texture).isNull()) {
        bool needsUpdate = texture->getFileName() != textureAsset.GetPath().toStdString();

        if (needsUpdate) {
            DestroyTexture(textureHandle);
            return CreateTexture(textureAsset);
        }

        return textureHandle;
    }

    return nullptr;
}

bool OSGWrapper::DestroyTexture(ResHandle texture) {
    osg::Image* image = (osg::Image*)texture;
    QUuid key = textures.key(image);

    if (image != nullptr && !key.isNull()) {
        textures.remove(key);
        image->unref();

        return true;
    }

    return false;
}

ResHandle OSGWrapper::CreateModel(const ModelAsset& modelAsset) {
    //qDebug() << "creating model for asset " << modelAsset.GetID();
    osg::Node* model = dynamic_cast<osg::Node*>(osgDB::readNodeFile(modelAsset.GetPath().toStdString()));

    if (model != nullptr) {
        //qDebug() << "model was created!";
        model->ref();
        models.insert(modelAsset.GetID(), model);
        return (ResHandle)model;
    }
    //qDebug() << "ERROR: model could not be created!";

    return nullptr;
}

ResHandle OSGWrapper::UpdateModel(ResHandle modelHandle, const ModelAsset &modelAsset) {
    osg::Node* model = (osg::Node*)modelHandle;

    if(model != nullptr && !models.key(model).isNull()) {
        // TODO: find way to compare files
        DestroyModel(model);
        return CreateModel(modelAsset);
    }

    return nullptr;
}

bool OSGWrapper::DestroyModel(ResHandle modelHandle) {
    osg::Node* model = (osg::Node*)modelHandle;
    QUuid key = models.key(model);

    if (model != nullptr && !key.isNull()) {
        models.remove(key);
        model->unref();

        return true;
    }

    return false;
}

ResHandle OSGWrapper::CreateMaterial(const MaterialAsset &materialAsset) {
    osg::Material* material = new osg::Material();

    // TODO: initialise material
    material->ref();
    materials.insert(materialAsset.GetID(), material);

    return material;
}

ResHandle OSGWrapper::UpdateMaterial(ResHandle materialHandle, const MaterialAsset &materialAsset) {
    osg::Material* material = (osg::Material*)materialHandle;
    if (material != nullptr && !materials.key(material).isNull()) {
        DestroyMaterial(material);
        return CreateMaterial(materialAsset);
    }
    return nullptr;
}

bool OSGWrapper::DestroyMaterial(ResHandle materialHandle) {
    osg::Material* material = (osg::Material*)materialHandle;
    QUuid key = materials.key(material);

    if (material != nullptr && !key.isNull()) {
        materials.remove(key);
        material->unref();

        return true;
    }

    return false;
}

EngineWidgetWrapper* OSGWrapper::CreateWidget() {
    return new OSGWidget(this);
}
