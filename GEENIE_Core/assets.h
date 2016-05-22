#ifndef ASSETS_H
#define ASSETS_H

#include "core_base.h"

//! A texture asset.
/*!
 * This class represents a texture asset.
 */
class SHARED_EXPORT TextureAsset : public Asset {
private:
    QString path; //!< The path of the texture.
    QUuid id; //!< The id of the asset.
public:
    //! The texture asset constructor.
    TextureAsset(QString path, QUuid id = QUuid::createUuid());
    //! The texture asset destructor.
    ~TextureAsset();

    //! Returns the id of the asset.
    const QUuid GetID() const;
    //! Returns the type of the asset.
    const AssetType GetType() const;
    //! Returns the path of the texture.
    const QString GetPath() const;
};

//! A model asset.
/*!
 * This class represents a model asset.
 */
class SHARED_EXPORT ModelAsset : public Asset {
private:
    QString path; //!< The path of the model file.
    QUuid id; //!< The id of the asset.
public:
    //! The model asset constructor.
    ModelAsset(QString path, QUuid id = QUuid::createUuid());
    //! The model asset destructor.
    ~ModelAsset();

    //! Returns the id of the asset.
    const QUuid GetID() const;
    //! Returns the type of the asset.
    const AssetType GetType() const;
    //! Returns the path of the model file.
    const QString GetPath() const;
};

//! A material asset.
/*!
 * This class represents a material asset.
 */
class SHARED_EXPORT MaterialAsset : public Asset {
private:
    QString path; //!< The path of the material file.
    QUuid id; //!< The id of the asset.
public:
    //! The material asset constructor.
    MaterialAsset(QString path, QUuid id = QUuid::createUuid());
    //! The material asset destructor.
    ~MaterialAsset();

    //! Returns the id of the asset.
    const QUuid GetID() const;
    //! Returns the type of the asset.
    const AssetType GetType() const;
    //! Returns the path of the material file.
    const QString GetPath() const;
};

//! A script asset
/*!
 * This class represents a script asset.
 */
class SHARED_EXPORT ScriptAsset : public Asset {
private:
    QString path; //!< The path of the script file.
    QUuid id; //!< The id of the asset.
public:
    //! The script asset constructor
    ScriptAsset(QString path, QUuid id = QUuid::createUuid());
    //! The script asset destructor
    ~ScriptAsset();

    //! Returns the id of the asset.
    const QUuid GetID() const;
    //! Returns the type of the asset.
    const AssetType GetType() const;
    //! Returns the path of the script file.
    const QString GetPath() const;
};

// TODO: SoundAsset,  ShaderAsset

#endif // ASSETS_H
