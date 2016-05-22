#ifndef CORE_BASE_H
#define CORE_BASE_H

#include "geenie_core_global.h"
#include <QUuid>
#include <QString>

/*!
 * \brief The AssetType enum
 */
enum AssetType {
    TEXTURE_ASSET,
    MODEL_ASSET,
    MATERIAL_ASSET,
    SCRIPT_ASSET,
};

/*!
 * \brief The Asset class
 *
 * Note: This is an abstract base class and can't be instantiated directly.
 */
class Asset {
public:
    Asset() {}
    //! Destructor (to make sure any resources will be released correctly)
    virtual ~Asset() {}

    //! Returns the id of the asset
    virtual const QUuid GetID() const = 0;
    //! Returns the path of the asset.
    virtual const QString GetPath() const = 0;
    //! Returns the type of the asset.
    virtual const AssetType GetType() const = 0;
};



#endif // CORE_BASE_H
