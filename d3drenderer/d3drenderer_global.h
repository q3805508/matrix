#ifndef D3DRENDERER_GLOBAL_H
#define D3DRENDERER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef D3DRENDERER_LIB
# define D3DRENDERER_EXPORT Q_DECL_EXPORT
#else
# define D3DRENDERER_EXPORT Q_DECL_IMPORT
#endif

#endif // D3DRENDERER_GLOBAL_H
