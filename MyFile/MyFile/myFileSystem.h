#ifndef MYFILESYSTEM_H
#define MYFILESYSTEM_H

#include <QtWidgets/QMainWindow>
#include "ui_myfile.h"

class MyFileSystem : public QMainWindow
{
	Q_OBJECT

public:
	MyFileSystem(QWidget *parent = 0);
	~MyFileSystem();

private:
	Ui::MyFileClass ui;
};

#endif // MYFILE_H
