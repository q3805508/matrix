#ifndef MATRIXEDITOR_H
#define MATRIXEDITOR_H

#include <QtGui/QMainWindow>
#include "ui_matrixeditor.h"

#include "..\common\futrure.h"

namespace renderer {
	class IRenderer;
}

class matrixEditor : public QMainWindow
{
	Q_OBJECT

public:
	matrixEditor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~matrixEditor();

	void init();
	void release();

	//void testResMgr();

public slots:
	//void onResourceDone();

protected:
	virtual void timerEvent( QTimerEvent * event);

private:
	Ui::matrixEditorClass ui;

	renderer::IRenderer* pRenderer;
	int frameTimer;

	//for test purpose
	//QSharedPointer<cn::Futrure<QByteArray>> testFuture;
};

#endif // MATRIXEDITOR_H
