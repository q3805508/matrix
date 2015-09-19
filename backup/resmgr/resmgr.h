#pragma once
#include "module.h"
#include <qobject.h>
#include <qstring.h>

namespace resmgr {

	class RESMGR_EXPORT ResMgr : public QObject {
		Q_OBJECT
	public:
		ResMgr(){}
		~ResMgr(){}

		bool isResourceExist(QString resID){return false;}

	};
}