#ifndef RESMGR_H
#define RESMGR_H

#include "resmgr_global.h"
#include <qobject.h>
#include <qhash.h>
#include "..\common\futrure.h"
#include <qthread.h>


namespace resmgr {
	class ResWorker;
	class RESMGR_EXPORT ResMgr : public QObject {
		Q_OBJECT
	public:
		ResMgr();
		~ResMgr();

		void setResourceRoot(QString resRoot);

		QSharedPointer<cn::Futrure<QByteArray>> getResource(QString resID);
		bool isResourceExist(QString resID);
		void updateResourceData(QString resID,QByteArray data);
		void removeResource(QString resID);

	private:
		ResWorker *resWorker;
		QThread WorkingThread;
	};

bool RESMGR_EXPORT initResMgr();
void RESMGR_EXPORT shutDownResMgr();

extern RESMGR_EXPORT ResMgr *theResMgr;
}

#endif // RESMGR_H
