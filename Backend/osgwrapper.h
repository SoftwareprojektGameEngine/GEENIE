#ifndef OSGWRAPPER_H
#define OSGWRAPPER_H

#include "backend_global.h"
#include "enginewrapper.h"

#include <QSet>

#include "osg/Geode"
#include "osg/Material"

class BACKEND_EXPORT OSGWrapper : public EngineWrapper {
public:
    OSGWrapper();
    ~OSGWrapper();
    /*OSGWrapper(const OSGWrapper&) = delete;
    OSGWrapper(OSGWrapper&&) = delete;
    OSGWrapper& operator=(const OSGWrapper&) = delete;
    OSGWrapper& operator=(OSGWrapper&&) = delete;*/

    ResHandle CreateTexture(const TextureAsset& textureAsset);
    ResHandle UpdateTexture(ResHandle texture, const TextureAsset& textureAsset);
    bool DestroyTexture(ResHandle texture);

    ResHandle CreateMaterial(const MaterialAsset& materialAsset);
    ResHandle UpdateMaterial(ResHandle material, const MaterialAsset& materialAsset);
    bool DestroyMaterial(ResHandle material);

    ResHandle CreateModel(const ModelAsset& modelAsset);
    ResHandle UpdateModel(ResHandle model, const ModelAsset& modelAsset);
    bool DestroyModel(ResHandle model);

    EngineWidgetWrapper* CreateWidget();

private:
    QSet<osg::Geode*> models;
    QSet<osg::Image*> textures;
    QSet<osg::Material*> materials;
};

#endif // OSGWRAPPER_H
