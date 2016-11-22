#include "myFileSystem.h"

MyFileSystem::MyFileSystem(QWidget *parent)
	: QMainWindow(parent)
{
	this->resize(QSize(800, 650));
	this->setMinimumSize(QSize(800, 650));
	this->setMaximumSize(QSize(800, 650));

	QFont font("Arial", 12);

	QLabel *l1 = new QLabel(this);
	l1->move(100, 540);
	l1->setText("Name:");

	l1 = new QLabel(this);
	l1->move(200, 540);
	l1->setText("Type:");

	l1 = new QLabel(this);
	l1->move(300, 540);
	l1->setText("Length:");

	l1 = new QLabel(this);
	l1->move(100, 450);
	l1->setText("Direction:");
	l1->setFont(font);

	openButton = new QPushButton(this);
	openButton->move(100, 500);
	openButton->setText("Open");

	textEdit = new QTextEdit(this);
	textEdit->move(410, 0);
	textEdit->resize(300, 300);
	textEdit->setFont(font);

	textName = new QTextEdit(this);
	textName->move(100, 570);
	textName->resize(90, 30);
	textName->setFont(font);

	comboBox = new QComboBox(this);
	comboBox->move(200, 570);
	comboBox->resize(90, 30);
	comboBox->addItem("File");
	comboBox->addItem("Folder");

	dic = new QLabel(this);
	dic->move(180, 457);
	dic->resize(100, 30);
	dic->setFont(font);

	textLength = new QTextEdit(this);
	textLength->move(300, 570);
	textLength->resize(90, 30);
	textLength->setFont(font);

	backButton = new QPushButton(this);
	backButton->move(200, 500);
	backButton->setText("Back");

	deleteButton = new QPushButton(this);
	deleteButton->move(300, 500);
	deleteButton->setText("Delete");

	createButton = new QPushButton(this);
	createButton->move(400, 500);
	createButton->setText("Create");

	writeButton = new QPushButton(this);
	writeButton->move(500, 500);
	writeButton->setText("Write");

	table = new QTableWidget(1, 2, this);
	table->resize(400, 400);

	table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	table->horizontalHeader()->setStretchLastSection(true);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//Chu Shi Hua
	FileManager::getInstance();
	FileFactory::getInstance();

	connect(openButton, SIGNAL(clicked()), this, SLOT(onOpenClick()));
	connect(backButton, SIGNAL(clicked()), this, SLOT(onBackClick()));
	connect(writeButton, SIGNAL(clicked()), this, SLOT(onWriteClick()));
	connect(createButton, SIGNAL(clicked()), this, SLOT(onCreateClick()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(onDeleteClick()));

	setTable();


	//table->currentRow();
}

MyFileSystem::~MyFileSystem()
{
	delete FileFactory::getInstance();
	delete FileManager::getInstance();
}

void MyFileSystem::showContent()
{
	textEdit->setText(content);
}

void MyFileSystem::setTable()
{
	//tableNum = 0;
	myNode = FileManager::getInstance()->getCurNode();
	tableNum = myNode->size();
	QString str = "";
	QVector<QString*>* mPath = FileManager::getInstance()->getCurPath();
	int length = mPath->length();
	for (int i = 0; i < length; i++)
	{
		str.append('/' + mPath->at(i));
	}
	dic->setText(str);
	dic->adjustSize();

	table->clear();
	QStringList headerLabels;
	headerLabels << "Name" << "Type";
	table->setHorizontalHeaderLabels(headerLabels);
	table->setRowCount(tableNum);
	for (int i = 0; i < table->rowCount(); i++)
	{
		table->setRowHeight(i, 22);
		table->setItem(i, 0, new QTableWidgetItem(*(myNode->at(i)->getName())));
		if (myNode->at(i)->getType())
		{
			table->setItem(i, 1, new QTableWidgetItem("Folder"));
		}
		else
		{
			table->setItem(i, 1, new QTableWidgetItem("File"));
		}
	}
}

void MyFileSystem::onOpenClick()
{
	usingFile = NULL;
	textEdit->clear();
	int a = table->currentRow();
	if (a >= 0 && a < tableNum)
	{
		if (myNode->at(a)->getType())
		{
			FileManager::getInstance()->openFile(myNode->at(a));
			setTable();
		}
		else
		{
			usingFile = myNode->at(a);
			content = *(FileManager::getInstance()->openFile(myNode->at(a)));
			showContent();
		}
	}
}

void MyFileSystem::onBackClick()
{
	usingFile = nullptr;
	textEdit->clear();
	bool result = FileManager::getInstance()->goBack();
	if (result)
		setTable();
}

void MyFileSystem::onWriteClick()
{
	if (!usingFile)
		return;
	if (textEdit->toPlainText().isEmpty())
	{
		QString str = "";
		usingFile->setContent(&str);
		QMessageBox::information(NULL, "Error", "Write Success", 0x00000000L);
		setTable();
		return;
	}
	else if (FileManager::getInstance()->writeFile(&(textEdit->toPlainText()),usingFile))
	{
		QMessageBox::information(NULL, "Error", "Write Success", 0x00000000L);
		setTable();
		return;
	}
	else
	{
		QMessageBox::information(NULL, "Error", "Write Fail", 0x00000000L);
	}
}

void MyFileSystem::onCreateClick()
{
	usingFile = NULL;
	if (textName->toPlainText().isEmpty())
	{
		QMessageBox::information(NULL, "Error", "Create Fail", 0x00000000L);
		return;
	}
	if (textLength->toPlainText().isEmpty())
	{
		if (FileManager::getInstance()->createFile(comboBox->currentIndex(), textName->toPlainText()))
		{
			QMessageBox::information(NULL, "Error", "Create Success", 0x00000000L);
			setTable();
			return;
		}
		else
		{
			QMessageBox::information(NULL, "Error", "Create Fail", 0x00000000L);
			return;
		}
	}
	if (FileManager::getInstance()->createFile(comboBox->currentIndex(), textName->toPlainText(),textLength->toPlainText().toInt()))
	{
		QMessageBox::information(NULL, "Error", "Create Success", 0x00000000L);
		setTable();
		return;
	}
	QMessageBox::information(NULL, "Error", "Create Fail", 0x00000000L);
	return;
}

void MyFileSystem::onDeleteClick()
{
	usingFile = NULL;
	textEdit->clear();
	int a = table->currentRow();
	if (a < tableNum&&a >= 0)
	{
		if (FileManager::getInstance()->deleteFile(myNode->at(a)->getName()))
		{
			QMessageBox::information(NULL, "Error", "Delete Success", 0x00000000L);
			setTable();
			return;
		}
	}
	QMessageBox::information(NULL, "Error", "Delete Fail", 0x00000000L);
	return;
}

