#ifndef ENGINEWRAPPER_H
#define ENGINEWRAPPER_H

//#include "core.h"
#include "assets.h"
//#include "components.h"
#include <QtWidgets/QWidget>

struct Vector {
    Vector(float _x = 0.0f,float _y = 0.0f,float _z = 0.0f,float _w = 1.0f) : x(_x),y(_y),z(_z),w(_w){}
    float x;
    float y;
    float z;
    float w = 1.0f;
};

struct Color {
    Color(float _r = 0.0f,float _g = 0.0f,float _b = 0.0f,float _a = 0.0f) : r(_r),g(_g),b(_b),a(_a){}
    float r;
    float g; //!< green
    float b; //!< blue
    float a; //!< alpha
};

struct Matrix {
    float data[16];
};

typedef void* ResHandle;

class EngineWidget;

class EngineWrapper {
public:
    EngineWrapper() {}
    EngineWrapper(const EngineWrapper&) = delete;
    EngineWrapper(EngineWrapper&&) = delete;
    virtual ~EngineWrapper() {}

    EngineWrapper& operator=(const EngineWrapper&) = delete;
    EngineWrapper& operator=(EngineWrapper&&) = delete;

    virtual ResHandle CreateTexture(const TextureAsset& textureAsset) = 0;
    virtual ResHandle UpdateTexture(ResHandle texture, const TextureAsset& textureAsset) = 0;
    virtual bool DestroyTexture(ResHandle texture) = 0;

    virtual ResHandle CreateMaterial(const MaterialAsset& materialAsset) = 0;
    virtual ResHandle UpdateMaterial(ResHandle material, const MaterialAsset& materialAsset) = 0;
    virtual bool DestroyMaterial(ResHandle material) = 0;

    virtual ResHandle CreateModel(const ModelAsset& modelAsset) = 0;
    virtual ResHandle UpdateModel(ResHandle model, const ModelAsset& modelAsset) = 0;
    virtual bool DestroyModel(ResHandle model) = 0;

    virtual EngineWidget* CreateWidget() = 0;
};

#include "core.h"

class EngineWidget : public QWidget {
    virtual void Destroy() = 0;

    virtual bool SetCamera(const Vector& position, const Vector& up) = 0;

    virtual bool BuildSceneGraph(Scene* scene) = 0;
    virtual bool UpdateSceneGraph() = 0;
};

#endif // ENGINEWRAPPER_H
