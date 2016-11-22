#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include <QString>

#include "FreeTable.h"
#include "FileFactory.h"
#include "MyFile.h"
#include "MyFolder.h"
#include "MyNode.h"
#include "MyTree.h"
#include <String>

class FileManager
{
private:
	static FileManager* instance;
	MyTree *myTree;
	QVector<MyNode*>* curNode;
	MyNode* copyNode;
public:
	FileManager();
	~FileManager();
	static FileManager* getInstance();

	// zai dang qian lu ding xia chuang jian xin de wen jian
	bool createFile(int flag, QString &name, int length = INITIAL_LENGTH);
	// delete file
	bool deleteFile(QString* mName);
	//da kai file / folder
	QString* openFile(MyNode* mNode);  
	bool goBack();
	bool writeFile(QString* mContent, MyNode *mNode);

	void closeFile(MyNode *mNode);
	QVector<MyNode*>* getCurNode();
	//Zhe Ge Zhi Shi she xiang
	bool copyFile();
	bool enterDir(QString* mDir);

	QVector<QString*>* getCurPath();
};

#endif