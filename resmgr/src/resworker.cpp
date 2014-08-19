#include "resworker.h"
#include <qfile.h>
#include <QMutexLocker>
#include <qcoreapplication.h>
#include <qdebug.h>

namespace resmgr {

	ResWorker::ResWorker()
		:busy(false)
		//:nTask(0)
		//,running(false)
	{

	}

	ResWorker::~ResWorker()
	{

	}

	void ResWorker::setRoot(QString root)
	{
		this->root = root;
	}

	void ResWorker::loadResource(QString resID,QSharedPointer<cn::Futrure<QByteArray>> future)
	{
		queueGuard.lock();
		this->busy = true;
		taskQueue.push_back(Task(resID,future));
		qDebug()<<"add load res "<<resID<<" to task queue";
		queueGuard.unlock();
	}

	void ResWorker::updateResource(QString resID,QByteArray data)
	{
		queueGuard.lock();
		this->busy = true;
		taskQueue.push_back(Task(resID,data));
		queueGuard.unlock();
	}

	void ResWorker::removeResource(QString resID)
	{
		queueGuard.lock();
		this->busy = true;
		taskQueue.push_back(resID);
		queueGuard.unlock();
	}

	bool ResWorker::isResourceExist(QString resID)
	{
		QMutexLocker locker(&this->queueGuard);
		Task *lastTask = NULL;
		queueGuard.lock();
		// check if there is task of this resID in queue
		ResTaskQueue::Iterator it = this->taskQueue.begin();
		while(it != this->taskQueue.end())
		{ 
			if ((it->type == TT_UPDATE || it->type == TT_REMOVE)
				&& it->resID == resID)
			{
				lastTask = &(*it);
			}
			it++;
		}

		if (lastTask != NULL)
			return lastTask->type == TT_UPDATE;
		else
			return QFile::exists(this->makeResourcePath(resID));
	}

	void ResWorker::tick()
	{
		Task currTask(TT_FLUSH);
		ResTaskQueue workingQueue;
		this->queueGuard.lock();
		if (!this->taskQueue.size())
		{
			this->busy = false;
			this->queueGuard.unlock();
			return ;
		} else {
			workingQueue = this->taskQueue;
			this->taskQueue.clear();
			this->queueGuard.unlock();
		}

		for (int i = 0 ; i < workingQueue.size() ;i++)
		{
			Task currTask = workingQueue[i];


			switch (currTask.type)
			{
			case TT_LOAD:
				processLoadTask(&currTask);
				break;
			case TT_UPDATE:
				processUpdateTask(&currTask);
				break;
			case TT_REMOVE:
				processRemoveTask(&currTask);
				break;
			case TT_FLUSH:
				processFlushTask();
				break;
			case TT_SHUTDOWN:
				processShutDownTask();
				break;
			}
		}
	}

	void ResWorker::processLoadTask(ResWorker::Task *task)
	{
		qDebug()<<"process load res "<<task->resID<<" to task queue";
		CacheMap::Iterator it = this->resCache.find(task->resID);
		if (it != this->resCache.end())
		{
			// if data in cache directly return 
			task->future->setResult(it->data);
		} else {
			QFile file(this->makeResourcePath(task->resID));
			if (file.open(QIODevice::ReadOnly))
			{
				QByteArray fileData = file.readAll();
				QByteArray* resData = new QByteArray(fileData);
				QSharedPointer<QByteArray> dataPtr(resData);

				//add cache data
				ResCache cache;
				cache.data = dataPtr;
				cache.dirty = false;
				this->resCache[task->resID] = cache;
				task->future->setResult(dataPtr);
			} else {
				QByteArray* resData = new QByteArray();
				QSharedPointer<QByteArray> dataPtr(resData);
				task->future->setResult(dataPtr);
			}
		}
	}

	void ResWorker::processUpdateTask(ResWorker::Task *task)
	{
		CacheMap::Iterator it = this->resCache.find(task->resID);
		if (it != this->resCache.end())
		{
			*(it->data) = task->uploadData;
			it->dirty = true;
		} else {
			//add this to resource cache
			QByteArray *data = new QByteArray(task->uploadData);
			QSharedPointer<QByteArray> dataPtr(data);
			ResCache cache;
			cache.data = dataPtr;
			cache.dirty = true;
			this->resCache[task->resID] = cache;
		}
	}

	void ResWorker::processRemoveTask(Task *task)
	{
		CacheMap::Iterator it = this->resCache.find(task->resID);
		if (it != this->resCache.end())
			this->resCache.erase(it);
		QFile::remove(this->makeResourcePath(task->resID));
	}

	void ResWorker::processFlushTask()
	{
		CacheMap::Iterator it = this->resCache.begin();
		while (it != this->resCache.end())
		{
			if (it->dirty)
			{
				QFile file(this->makeResourcePath(it.key()));
				if (file.open(QIODevice::WriteOnly))
				{
					file.write(*it->data);
					file.close();
				}
				it->dirty = false;
			}
			it++;
		}
	}

	void ResWorker::processShutDownTask()
	{
		qDebug() << "resource worker shut down";
		this->stopTicking();
		this->busy = false;
	}

	bool ResWorker::isBusy()
	{
		return this->busy;
	}

	void ResWorker::startWorkingAtThread(QThread *thread)
	{
		this->moveToThread(thread);
		this->startTicking(thread);
	}

	void ResWorker::startTicking(QThread *thread)
	{
		this->timer.setInterval(0);
		this->timer.start();
		this->timer.moveToThread(thread);
		QObject::connect(&this->timer,SIGNAL(timeout()),SLOT(tick()));
	}

	void ResWorker::stopTicking()
	{
		this->timer.stop();
		QObject::disconnect(&this->timer,SIGNAL(timeout()));
	}

	void ResWorker::stopWorking()
	{
		this->flush();
		//post shutdown msg
		this->queueGuard.lock();
		this->busy = true;
		this->taskQueue.push_back(Task(TT_SHUTDOWN));
		this->queueGuard.unlock();
		// wait until finishing worker's job
		while (this->busy)
			QCoreApplication::processEvents();
	}




	QString ResWorker::makeResourcePath(QString resID)
	{
		return this->root + resID;
	}

	void ResWorker::flush()
	{
		queueGuard.lock();
		this->busy = true;
		taskQueue.push_back(Task(TT_FLUSH));
		queueGuard.unlock();
	}

}