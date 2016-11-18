#include "myfile.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyFileSystem w;
	w.show();
	return a.exec();
}
