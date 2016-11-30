#include "FileManager.h"

FileManager* FileManager::instance;

FileManager::FileManager()
{
	myTree = new MyTree();
	curNode = myTree->getCurChild();
}

FileManager* FileManager::getInstance()
{
	if (!instance)
	{
		instance = new FileManager();
	}
	return instance;
}

QVector<MyNode*>* FileManager::getCurNode()
{
	return curNode;
}

FileManager::~FileManager()
{
	if (myTree)
		delete myTree;
	if (curNode)
		delete curNode;
}

bool FileManager::createFile(int flag, QString &name, int length)
{
	int s = curNode->size();
	for (int i = 0; i < s; i++)
	{
		if (curNode->at(i)->getName() == name)
			return 0;
	}
	MyNode* mNode;
	if (flag)
	{
		mNode = FileFactory::getInstance()->createFile(0, &name);
	}
	else
	{
		mNode = FileFactory::getInstance()->createFile(length, &name);
	}
	bool result = myTree->insertNode(mNode);
	if (!result)
	{
		delete mNode;
		return 0;
	}
	if (curNode)
		delete curNode;
	curNode = myTree->getCurChild();
	return result;
}

bool FileManager::deleteFile(QString* mName)
{
	bool result = myTree->deleteNode(mName);
	if (curNode)
		delete curNode;
	curNode = myTree->getCurChild();
	return result;
}

QString* FileManager::openFile(MyNode* mNode)
{
	if (!mNode->getType())
		return mNode->getContent();
	if (!myTree->enterChild(mNode))
		return 0;
	if (curNode)
		delete curNode;
	curNode = myTree->getCurChild();
	return NULL;
}

bool FileManager::goBack()
{
	if (!myTree->goBack())
		return 0;
	if (curNode)
		delete curNode;
	curNode = myTree->getCurChild();
	return 1;
}

bool FileManager::writeFile(QString* mContent, MyNode *mNode)
{
	if (mNode->getType())
		return 0;
	mNode->setContent(mContent);
	return 1;
}

void FileManager::closeFile(MyNode *mNode)
{

	return;
}

bool FileManager::enterDir(QString* mDir)
{
	// Xian Jie Xi
	QVector<QString> *mVector = new QVector<QString>();
	std::string mStr = mDir->toStdString();
	std::string temp;
	int index = mStr.find('/');
	while (index != -1)
	{
		if (!index)
		{
			mStr.erase(0, 1);
			index = mStr.find('/');
			continue;
		}
		temp = mStr.substr(0, index);
		mStr.erase(0, index + 1);
		mVector->push_back(temp.data());
		index = mStr.find('/');
	}
	mVector->push_back(mStr.data());
	if (!myTree->enterCD(mVector))
		return 0;
	if (curNode)
		delete curNode;
	curNode = myTree->getCurChild();
	return 1;
}

QVector<QString>* FileManager::getCurPath()
{
	return myTree->getCurPath();
}

MyNode* FileManager::searchFile(QString* mName)
{
	FileIterator *mIter = new FileIterator(myTree->getCurNode());
	MyNode* result;
	if (*mName == "root")
		return NULL;
	while (mIter->hasNext())
	{
		result = mIter->next();
		if (*(result->getName()) == *mName)// zhao dao
		{
			myTree->setCurNode(result->getParent());
			if (curNode)
				delete curNode;
			curNode = myTree->getCurChild();
			delete mIter;
			return result;
		}
	}
	delete mIter;
	return NULL;
}