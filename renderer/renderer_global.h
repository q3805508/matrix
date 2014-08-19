#ifndef RENDERER_GLOBAL_H
#define RENDERER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef RENDERER_LIB
# define RENDERER_EXPORT Q_DECL_EXPORT
#else
# define RENDERER_EXPORT Q_DECL_IMPORT
#endif

#endif // RENDERER_GLOBAL_H
