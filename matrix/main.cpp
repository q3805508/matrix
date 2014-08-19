#include "matrixeditor.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	matrixEditor w;
	w.show();
	return a.exec();
}
