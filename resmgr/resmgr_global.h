#ifndef RESMGR_GLOBAL_H
#define RESMGR_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef RESMGR_LIB
# define RESMGR_EXPORT Q_DECL_EXPORT
#else
# define RESMGR_EXPORT Q_DECL_IMPORT
#endif

#endif // RESMGR_GLOBAL_H
