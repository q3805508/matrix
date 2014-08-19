#ifndef MATRIXEDITOR_H
#define MATRIXEDITOR_H

#include <QtGui/QMainWindow>
#include "ui_matrixeditor.h"

#include "..\common\futrure.h"

class matrixEditor : public QMainWindow
{
	Q_OBJECT

public:
	matrixEditor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~matrixEditor();

	void init();
	void release();

	void testResMgr();

public slots:
	void onResourceDone();

private:
	Ui::matrixEditorClass ui;


	//for test purpose
	QSharedPointer<cn::Futrure<QByteArray>> testFuture;
};

#endif // MATRIXEDITOR_H
