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
#include "FileIterator.h"

class FileManager
{
private:
	static FileManager* instance;
	MyTree *myTree;
	QVector<MyNode*>* curNode;
	MyNode* copyNode;
	FileManager();
public:
	
	~FileManager();
	static FileManager* getInstance();

	// zai dang qian lu ding xia chuang jian xin de wen jian
	bool createFile(int flag, QString &name, int length = INITIAL_LENGTH);
	// delete file
	bool deleteFile(MyNode* mNode);
	//da kai file / folder
	QString* openFile(MyNode* mNode);  
	bool goBack();
	bool writeFile(QString* mContent, MyNode *mNode);

	void closeFile(MyNode *mNode);
	QVector<MyNode*>* getCurNode();
	//
	bool copyFile();
	bool enterDir(QString* mDir);

	// Jiang node Fu Zhi Dao Dang Qian Lu Jing Xia, Ru Guo Ming Cheng Xiang Tong, Ze Gai Ming(1,2...)
	bool pasteFile(MyNode *mNode);
	bool saveRef(MyNode* mNode);
	MyNode* searchFile(QString* mName);
	QVector<QString>* getCurPath();
	QVector<QString>* convertPath(const QString& mPath);

	MyNode* path2Node(QString &ref);

	int sizeSum();
};

#endif