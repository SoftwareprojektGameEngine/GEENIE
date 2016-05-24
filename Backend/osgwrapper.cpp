#include "osgwrapper.h"

#include "osgDB/ReadFile"
#include "osgwidget.h"

OSGWrapper::OSGWrapper() : models(), textures(), materials() {

}

OSGWrapper::~OSGWrapper() {

}

ResHandle OSGWrapper::CreateTexture(const TextureAsset &textureAsset) {
    osg::Image* image = osgDB::readImageFile(textureAsset.GetPath().toStdString());

    if (image != nullptr) {
        image->ref();
        textures.insert(image);
        return (ResHandle)image;
    }

    return nullptr;
}

ResHandle OSGWrapper::UpdateTexture(ResHandle textureHandle, const TextureAsset &textureAsset) {
    osg::Image* texture = (osg::Image*)textureHandle;

    if (textures.contains(texture)) {
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
    if (textures.contains(image)) {
        textures.remove(image);
        image->unref();

        return true;
    }

    return false;
}

ResHandle OSGWrapper::CreateModel(const ModelAsset& modelAsset) {
    osg::Geode* model = dynamic_cast<osg::Geode*>(osgDB::readNodeFile(modelAsset.GetPath().toStdString()));

    if (model != nullptr) {
        model->ref();
        models.insert(model);
        return (ResHandle)model;
    }

    return nullptr;
}

ResHandle OSGWrapper::UpdateModel(ResHandle modelHandle, const ModelAsset &modelAsset) {
    osg::Geode* model = (osg::Geode*)modelHandle;

    if(model != nullptr && models.contains(model)) {
        // TODO: find way to compare files
        DestroyModel(model);
        return CreateModel(modelAsset);
    }

    return nullptr;
}

bool OSGWrapper::DestroyModel(ResHandle modelHandle) {
    osg::Geode* model = (osg::Geode*)modelHandle;

    if (model != nullptr && models.contains(model)) {
        models.remove(model);
        model->unref();

        return true;
    }

    return false;
}

ResHandle OSGWrapper::CreateMaterial(const MaterialAsset &materialAsset) {
    osg::Material* material = new osg::Material();

    // TODO: initialise material
    material->ref();
    materials.insert(material);

    return material;
}

ResHandle OSGWrapper::UpdateMaterial(ResHandle materialHandle, const MaterialAsset &materialAsset) {
    osg::Material* material = (osg::Material*)materialHandle;
    if (material != nullptr && materials.contains(material)) {
        DestroyMaterial(material);
        return CreateMaterial(materialAsset);
    }
    return nullptr;
}

bool OSGWrapper::DestroyMaterial(ResHandle materialHandle) {
    osg::Material* material = (osg::Material*)materialHandle;

    if (material != nullptr && materials.contains(material)) {
        materials.remove(material);
        material->unref();

        return true;
    }

    return false;
}

EngineWidgetWrapper* OSGWrapper::CreateWidget() {
    return new OSGWidget(this);
}
