#ifndef MYFILESYSTEM_H
#define MYFILESYSTEM_H

#include <QtWidgets/QMainWindow>
#include "ui_myfile.h"
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <string>

#include "FileManager.h"
#include "FileFactory.h"
#include "MyNode.h"
#include "MyFile.h"
#include "MyFolder.h"

class MyFileSystem : public QMainWindow
{
	Q_OBJECT

public:
	MyFileSystem(QWidget *parent = 0);
	~MyFileSystem();
	void setTable();
	void showContent();
private:

	QVector<MyNode*>* myNode;
	MyFile* usingFile;

	Ui::MyFileClass ui;
	QTableWidget *table;
	QPushButton *backButton;
	QPushButton *openButton;
	QPushButton *createButton, *deleteButton, *writeButton;
	int tableNum;  // biao ge xiang shu liang
	QString content;
	QTextEdit *textEdit, *textName, *textLength;
	QComboBox *comboBox;
	QLabel *dic;
	public slots:
	void onOpenClick();
	void onBackClick();
	void onWriteClick();
	void onCreateClick();
	void onDeleteClick();
};

#endif // MYFILE_H
