#ifndef TAEVALCOMMONS_GLOBAL_H
#define TAEVALCOMMONS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TAEVALCOMMONS_LIBRARY)
#  define TAEVALCOMMONSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TAEVALCOMMONSSHARED_EXPORT Q_DECL_IMPORT
#endif


#endif // TAEVALCOMMONS_GLOBAL_H
