#include "..\resmgr.h"
#include "resworker.h"


namespace resmgr {

	ResMgr *theResMgr = NULL;

	bool initResMgr()
	{
		Q_ASSERT(theResMgr == NULL);
		theResMgr = new ResMgr();
		return true;
	}

	void shutDownResMgr()
	{
		delete theResMgr;
		theResMgr = NULL;
	}

	ResMgr::ResMgr()
	{
		this->resWorker = new ResWorker();
		//this->resWorker->moveToThread(&this->WorkingThread);
		this->WorkingThread.start();
		this->resWorker->startWorkingAtThread(&this->WorkingThread);
	}

	ResMgr::~ResMgr()
	{
		this->resWorker->stopWorking();
		this->WorkingThread.quit();
		this->WorkingThread.wait();
		delete this->resWorker;
	}

	void ResMgr::setResourceRoot(QString resRoot)
	{
		this->resWorker->setRoot(resRoot);
	}

	QSharedPointer<cn::Futrure<QByteArray>> ResMgr::getResource(QString resID)
	{
		QSharedPointer<cn::Futrure<QByteArray>> ptrResource(new cn::Futrure<QByteArray>());
		this->resWorker->loadResource(resID,ptrResource);
		return ptrResource;
	}

	bool ResMgr::isResourceExist(QString resID)
	{
		return this->resWorker->isResourceExist(resID);
	}

	void ResMgr::updateResourceData(QString resID,QByteArray data)
	{
		this->resWorker->updateResource(resID,data);
	}

	void ResMgr::removeResource(QString resID)
	{
		this->resWorker->removeResource(resID);
	}

}