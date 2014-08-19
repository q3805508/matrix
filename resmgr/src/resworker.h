#pragma once
#include "..\..\common\futrure.h"
#include <qthread.h>
#include <qhash.h>
#include <qmutex.h>
#include <qwaitcondition.h>
#include <qstring.h>
#include <qbytearray.h>
#include <qlist.h>
#include <qtimer.h>

namespace resmgr {

	class ResWorker : public QObject {
		Q_OBJECT
	public:
		ResWorker();
		~ResWorker();

		void setRoot(QString root);
		
		bool isBusy();
		void startWorkingAtThread(QThread *thread);
		void stopWorking();

		void flush();

		void loadResource(QString resID,QSharedPointer<cn::Futrure<QByteArray>> future);
		///if resource not exist create it
		void updateResource(QString resID,QByteArray data);
		void removeResource(QString resID);
		bool isResourceExist(QString resID);

	public slots:
		void tick();

	private:
		void startTicking(QThread *thread);
		void stopTicking();

	private:
		enum TASK_TYPE{TT_LOAD,TT_UPDATE,TT_REMOVE,TT_FLUSH,TT_SHUTDOWN};
		struct Task{
			Task(const QString &resID,QSharedPointer<cn::Futrure<QByteArray>> future)
				:type(TT_LOAD)
				,resID(resID)
				,future(future)
			{
			}

			Task(const QString &resID,const QByteArray &data)
				:type(TT_UPDATE)
				,resID(resID)
				,uploadData(data)
			{
			}

			Task(const QString &resID)
				:type(TT_REMOVE)
				,resID(resID)
			{
			}
			Task(TASK_TYPE _type)
				:type(_type)
			{

			}

			TASK_TYPE type;
			QString resID;
			QSharedPointer<cn::Futrure<QByteArray>> future;
			QByteArray uploadData;
		};

		typedef QList<Task> ResTaskQueue;

		struct ResCache {
			QSharedPointer<QByteArray> data;
			bool dirty;
		};

		typedef QHash<QString,ResCache> CacheMap;

	private:
		void processTask(Task task);

		void processLoadTask(Task *task);
		void processUpdateTask(Task *task);
		void processRemoveTask(Task *task);
		void processFlushTask();
		void processShutDownTask();

		void flushResourceCache();

		QString makeResourcePath(QString resID);

	private:
		QString root;
		QMutex queueGuard;
		ResTaskQueue taskQueue;
		QMutex jobMutex;
		QWaitCondition jobCondition;
		CacheMap resCache;
		bool busy;
		QTimer timer;
	};
}