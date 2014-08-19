#pragma once
#include "common_global.h"
#include <qsharedpointer.h>
#include <qmutex.h>
#include <qwaitcondition.h>

namespace cn {

	class COMMON_EXPORT FutureNotifier : public QObject {
		Q_OBJECT
	public:
signals:
		void processStarted();
		void processFinished();


	};

	enum FUTRURE_STATE{FS_EMPTY,FS_PROCEESSING,FS_READY};

	template <class T> class FutrueBase : public FutureNotifier {
	public:
		FutrueBase()
			:state(FS_EMPTY)
		{

		}
		~FutrueBase()
		{

		}

	protected:

		void setFinished(QSharedPointer<T> result)
		{
			mutex.lock();
			this->state = FS_READY;
			this->result = result;
			waitingLoading.wakeAll();
			mutex.unlock();
			emit this->processFinished();
		}

		void waitToFinish()
		{
			mutex.lock();
			if (this->state != FS_READY)
				waitingLoading.wait(&mutex);
			mutex.unlock();
		}

		void setBeginProcess()
		{
			mutex.lock();
			this->state = FS_PROCEESSING;
			mutex.unlock();
			emit this->processStarted();
		}

		FUTRURE_STATE getState()
		{
			return this->state;
		}

	protected://overwrite qobject's methods
		virtual void connectNotify(const char *signal)
		{
			if (QLatin1String(signal) == SIGNAL(processStarted())) {
				if (this->getState() != FS_EMPTY)
					emit this->processStarted();
			} else if (QLatin1String(signal) == SIGNAL(processFinished())) {
				if (this->getState() == FS_READY)
					emit this->processFinished();
			}
		}

	protected:
		QSharedPointer<T> result;

	private:
		FUTRURE_STATE state;
		QMutex mutex;
		QWaitCondition waitingLoading;

	};

	template <class T> class Futrure :public FutrueBase<T> {
	public:

		///if result is ready function will return pointer of the data,otherwise it return NULL
		QSharedPointer<T> queryResult()//customer thread
		{
			if (getState() != FS_READY)
				return QSharedPointer<T>();
			else
				return this->result;
		}
		///function always return the data if the result is not ready it will wait
		QSharedPointer<T> getResult()//customer thread
		{
			if (this->getState() != FS_READY)
				this->waitToFinish();
			return this->result;
		}

		void beginProcessing()//producter thread
		{
			this->setBeginProcess();
		}

		void setResult(QSharedPointer<T> result)//producter thread
		{
			this->setFinished(result);
		}

	};
}