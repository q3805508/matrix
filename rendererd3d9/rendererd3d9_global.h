#ifndef RENDERERD3D9_GLOBAL_H
#define RENDERERD3D9_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef RENDERERD3D9_LIB
# define RENDERERD3D9_EXPORT Q_DECL_EXPORT
#else
# define RENDERERD3D9_EXPORT Q_DECL_IMPORT
#endif

#ifdef RENDERERD3D9_LIB
# define INTERFACE_EXPORT extern "C" __declspec(dllexport)
#else
# define INTERFACE_EXPORT extern "C" __declspec(dllimport)
#endif

#endif // RENDERERD3D9_GLOBAL_H
