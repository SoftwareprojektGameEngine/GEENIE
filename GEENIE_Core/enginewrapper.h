#ifndef ENGINEWRAPPER_H
#define ENGINEWRAPPER_H

//#include "core.h"
#include "assets.h"
//#include "components.h"
#include <QtWidgets/QWidget>

/*!
 * \brief The Vector struct
 */
struct Vector {
    Vector(float _x = 0.0f,float _y = 0.0f,float _z = 0.0f,float _w = 1.0f) : x(_x),y(_y),z(_z),w(_w){}
    float x;
    float y;
    float z;
    float w = 1.0f;
};

/*!
 * \brief The Color struct
 */
struct Color {
    Color(float _r = 0.0f,float _g = 0.0f,float _b = 0.0f,float _a = 0.0f) : r(_r),g(_g),b(_b),a(_a){}
    float r;
    float g; //!< green
    float b; //!< blue
    float a; //!< alpha
};

/*!
 * \brief The Matrix struct
 */
struct Matrix {
    float data[16];
};

/*!
 * \brief ResHandle is a typedef of void*
 */
typedef void* ResHandle;

class EngineWidgetWrapper;

/*!
 * \brief The virtual EngineWrapper class
 */
class EngineWrapper {
public:
    /*!
     * \brief EngineWrapper constructor
     */
    EngineWrapper() {}
    /*!
     * \brief virtual EngineWrapper copy constructor
     */
    EngineWrapper(const EngineWrapper&) = delete;
    /*!
     * \brief virtual EngineWrapper copy constructor
     */
    EngineWrapper(EngineWrapper&&) = delete;
    /*!
     * \brief virtual destructor ~EngineWrapper
     */
    virtual ~EngineWrapper() {}

    /*!
     * \brief virtual operator =
     * \return 0
     */
    EngineWrapper& operator=(const EngineWrapper&) = delete;
    /*!
     * \brief virtual operator =
     * \return
     */
    EngineWrapper& operator=(EngineWrapper&&) = delete;

    /*!
     * \brief Creates a texture
     * \param textureAsset
     * \return
     */
    virtual ResHandle CreateTexture(const TextureAsset& textureAsset) = 0;
    /*!
     * \brief Updates a texture
     * \param texture
     * \param textureAsset
     * \return
     */
    virtual ResHandle UpdateTexture(ResHandle texture, const TextureAsset& textureAsset) = 0;
    /*!
     * \brief Destroys a texture
     * \param texture
     * \return Whether the texture was successfully destroyed or not
     */
    virtual bool DestroyTexture(ResHandle texture) = 0;

    /*!
     * \brief Creates a material
     * \param materialAsset
     * \return
     */
    virtual ResHandle CreateMaterial(const MaterialAsset& materialAsset) = 0;
    /*!
     * \brief Updates a material
     * \param material
     * \param materialAsset
     * \return
     */
    virtual ResHandle UpdateMaterial(ResHandle material, const MaterialAsset& materialAsset) = 0;
    /*!
     * \brief Destroys a material
     * \param material
     * \return Whether the material was successfully destroyed
     */
    virtual bool DestroyMaterial(ResHandle material) = 0;

    /*!
     * \brief Creates a model
     * \param modelAsset
     * \return
     */
    virtual ResHandle CreateModel(const ModelAsset& modelAsset) = 0;
    /*!
     * \brief Updates a model
     * \param model
     * \param modelAsset
     * \return
     */
    virtual ResHandle UpdateModel(ResHandle model, const ModelAsset& modelAsset) = 0;
    /*!
     * \brief Destroys a model
     * \param model
     * \return Whether the model was successfully destroyed
     */
    virtual bool DestroyModel(ResHandle model) = 0;

    /*!
     * \brief Creates the widget wrapper, which returns the visible widget
     * \return
     */
    virtual EngineWidgetWrapper* CreateWidget() = 0;
};

#include "core.h"

/*!
 * \brief The EngineWidgetWrapper class
 */
class EngineWidgetWrapper {
public:
    /*!
     * \brief Returns the widget depending
     * \return widget
     */
    virtual QWidget* GetWidget() = 0;
    /*!
     * \brief Sets the camera
     * \param eye
     * \param center
     * \param up
     * \return
     */
    virtual bool SetCamera(const Vector& eye, const Vector& center, const Vector& up) = 0;

    /*!
     * \brief Builds and previews the scene
     * \param scene
     * \return
     */
    virtual bool BuildSceneGraph(Scene* scene) = 0;
    /*!
     * \brief Updates the scene
     * \return
     */
    virtual bool UpdateSceneGraph() = 0;
};

#endif // ENGINEWRAPPER_H
