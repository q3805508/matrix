#ifndef RENDER_ENGINE_GLOBAL_H
#define RENDER_ENGINE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef RENDER_ENGINE_LIB
# define RENDER_ENGINE_EXPORT Q_DECL_EXPORT
#else
# define RENDER_ENGINE_EXPORT Q_DECL_IMPORT
#endif

#endif // RENDER_ENGINE_GLOBAL_H
