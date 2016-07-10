#ifndef OSGWRAPPER_H
#define OSGWRAPPER_H

#include "backend_global.h"
#include "enginewrapper.h"

#include <QHash>

#include "osg/Geode"
#include "osg/Material"

class BACKEND_EXPORT OSGWidget;

class BACKEND_EXPORT OSGWrapper : public EngineWrapper {
    friend class OSGWidget;
public:
    //!Constructor, which initializes the attributes of the object.
    OSGWrapper();
    //!Destructor, which cleans the used storage of the object.
    ~OSGWrapper();
    /*OSGWrapper(const OSGWrapper&) = delete;
    OSGWrapper(OSGWrapper&&) = delete;
    OSGWrapper& operator=(const OSGWrapper&) = delete;
    OSGWrapper& operator=(OSGWrapper&&) = delete;*/

    //!Creates a texture object and returns a ResHandle to it.
    ResHandle CreateTexture(const TextureAsset& textureAsset);
    //!Updates a texture Returns the ResHandle to it if it exists.
    ResHandle UpdateTexture(ResHandle texture, const TextureAsset& textureAsset);
    //!Cleans the used space of a texture and deletes it if it exists. Returns true if the object has been deleted correctly.
    bool DestroyTexture(ResHandle texture);

    //!Creates a material object and returns a ResHandle to it.
    ResHandle CreateMaterial(const MaterialAsset& materialAsset);
    //!Updates a material Returns the ResHandle to it if it exists.
    ResHandle UpdateMaterial(ResHandle material, const MaterialAsset& materialAsset);
    //!Cleans the used space of a material and deletes it if it exists. Returns true if the object has been deleted correctly.
    bool DestroyMaterial(ResHandle material);

    //!Creates a model object and returns a ResHandle to it.
    ResHandle CreateModel(const ModelAsset& modelAsset);
    //!Updates a model Returns the ResHandle to it if it exists.
    ResHandle UpdateModel(ResHandle model, const ModelAsset& modelAsset);
    //!Cleans the used space of a model and deletes it if it exists. Returns true if the object has been deleted correctly.
    bool DestroyModel(ResHandle model);

    //!Creates and returns a new EngineWidgetWrapper object.
    EngineWidgetWrapper* CreateWidget();

private:
    QHash<QUuid, osg::Node*> models;
    QHash<QUuid, osg::Image*> textures;
    QHash<QUuid, osg::Material*> materials;
};

#endif // OSGWRAPPER_H
