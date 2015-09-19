#include "matrixeditor.h"
#include "..\resmgr\resmgr.h"
#include "..\renderer\renderer.h"
#include "..\renderer\rendermgr.h"

matrixEditor::matrixEditor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	this->init();

	//begin rendering
	this->frameTimer = this->startTimer(0);


	//this->testResMgr();
}

matrixEditor::~matrixEditor()
{
	this->release();
}

void matrixEditor::init()
{
	resmgr::initResMgr();
	renderer::initRenderer("rendererd3d9.dll");
	this->pRenderer = renderer::theRenderMgr->getRenderer();
	pRenderer->init(this->centralWidget(),800,600,true);
}

void matrixEditor::timerEvent(QTimerEvent * event)
{
	this->pRenderer->beginFrame();
	this->pRenderer->endFrame();
	this->pRenderer->present();
}

void matrixEditor::release()
{
	this->killTimer(this->frameTimer);
	resmgr::shutDownResMgr();
	renderer::shutdownRenderer();
}

//void matrixEditor::testResMgr()
//{
//	QSharedPointer<cn::Futrure<QByteArray>> future = 
//		resmgr::theResMgr->getResource("data/testRes.txt");
//	this->testFuture = future;
//	QObject::connect(future.data(),
//		SIGNAL(processFinished()),
//		SLOT(onResourceDone()));
//
//	QByteArray outData("fist write");
//	resmgr::theResMgr->updateResourceData("data/testRes.txt",outData);
//	future = 
//		resmgr::theResMgr->getResource("data/testRes.txt");
//
//	QSharedPointer<QByteArray> data  = future->getResult();
//
//	outData.append(" and the second one");
//	resmgr::theResMgr->updateResourceData("data/testRes.txt",outData);
//	future = 
//		resmgr::theResMgr->getResource("data/testRes.txt");
//
//	data  = future->getResult();
//
//
//}

//void matrixEditor::onResourceDone()
//{
//	cn::Futrure<QByteArray> *pFuture = (cn::Futrure<QByteArray>*) sender();
//	QSharedPointer<QByteArray> data = pFuture->queryResult();
//}