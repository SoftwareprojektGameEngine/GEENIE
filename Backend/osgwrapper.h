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

    EngineWidgetWrapper* CreateWidget(QWidget* parent);

private:
    QHash<QUuid, osg::Geode*> models;
    QHash<QUuid, osg::Image*> textures;
    QHash<QUuid, osg::Material*> materials;
};

#endif // OSGWRAPPER_H
