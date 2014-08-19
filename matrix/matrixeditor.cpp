#include "matrixeditor.h"
#include "..\resmgr\resmgr.h"

matrixEditor::matrixEditor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	this->init();




	this->testResMgr();
}

matrixEditor::~matrixEditor()
{

	this->release();
}

void matrixEditor::init()
{
	resmgr::initResMgr();
}

void matrixEditor::release()
{
	resmgr::shutDownResMgr();
}

void matrixEditor::testResMgr()
{
	QSharedPointer<cn::Futrure<QByteArray>> future = 
		resmgr::theResMgr->getResource("data/testRes.txt");
	this->testFuture = future;
	QObject::connect(future.data(),
		SIGNAL(processFinished()),
		SLOT(onResourceDone()));

	QByteArray outData("fist write");
	resmgr::theResMgr->updateResourceData("data/testRes.txt",outData);
	future = 
		resmgr::theResMgr->getResource("data/testRes.txt");

	QSharedPointer<QByteArray> data  = future->getResult();

	outData.append(" and the second one");
	resmgr::theResMgr->updateResourceData("data/testRes.txt",outData);
	future = 
		resmgr::theResMgr->getResource("data/testRes.txt");

	data  = future->getResult();


}

void matrixEditor::onResourceDone()
{
	cn::Futrure<QByteArray> *pFuture = (cn::Futrure<QByteArray>*) sender();
	QSharedPointer<QByteArray> data = pFuture->queryResult();
}