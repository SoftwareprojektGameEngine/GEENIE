#ifndef GEENIE_CORE_GLOBAL_H
#define GEENIE_CORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GEENIE_CORE_LIBRARY)
#  define SHARED_EXPORT Q_DECL_EXPORT
#else
#  define SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GEENIE_CORE_GLOBAL_H
