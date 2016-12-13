#ifndef MYTREE_H_
#define MYTREE_H_

#include <QString>
#include <QVector>

#include "MyNode.h"
#include "MyFolder.h"
#include "MyFile.h"
#include "FileFactory.h"

struct MyPair
{
	int child;
	int next;
};

// type: none - 0, ref - 1, refVec - 2

class MyTree
{
private:
	MyNode* rootNode;  // Zhe Ke Shu de Gen Jie Dian
	MyNode* currentNode;
	QVector<QString>* currentPath;  // lu jing

public :
	MyTree();
	MyTree(MyNode *mRoot);
	~MyTree();
	MyNode *getCurNode();  //

	void setCurNode(MyNode* mNode);
	// ji de delete !!!!!
	// ji de delete  !!!
	//                !
	// 返回的vector要删除！！！
	QVector<MyNode*> *getCurChild();  // huo de dang qian lu jing xia zi jie dian 

	bool goBack();         // 返回上一级路径

	QVector<QString> *getCurPath()const;  // 返回当前路径

	bool enterCD(QVector<QString> *mPath);  //cd: root/...

	MyNode* findNode(QVector<QString> *mPath);

	bool enterChild(MyNode *node);  // jin ru xia yi ji lu jing

	bool insertNode(MyNode* node);  // zai dang qian lu jing xia zeng jia jie dian

	bool deleteNode(MyNode* mNode); // zai dang qian lu jing xia shan chu jie dian

	// Hai Wei Shi Xian !!!!!!!!!!!
	bool copyNode(MyNode* target, MyNode pasteFather);  // 将target复制到pasteFather路径下 还没写！！！

	void open(MyNode* mNode, QDir mDir);
	void save(MyNode* mNode, QDir mDir);

	bool isBlock(const QString &mStr);
};

#endif