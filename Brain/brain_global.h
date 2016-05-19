#ifndef BRAIN_GLOBAL_H
#define BRAIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BRAIN_LIBRARY)
#  define BRAINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BRAINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BRAIN_GLOBAL_H
