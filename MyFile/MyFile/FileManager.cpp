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

//
bool FileManager::deleteFile(MyNode* mNode)
{
	QVector<QString> *mVec = mNode->getRefVec();
	if (!mVec->empty())
	{
		saveRef(mNode);
	}
	else if (mNode->getRef() != "")
	{
		MyNode *rNode = path2Node(mNode->getRef());
		QVector<QString>::Iterator it = rNode->getRefVec()->begin();
		QString str = mNode->getPath();
		while (it != rNode->getRefVec()->end())
		{
			if (it == str)
				break;
			it++;
		}
		rNode->getRefVec()->erase(it);
	}
	bool result = myTree->deleteNode(mNode);
	if (curNode)
		delete curNode;
	curNode = myTree->getCurChild();
	return result;
}

QString* FileManager::openFile(MyNode* mNode)
{
	if (!mNode->getType())
	{
		if (mNode->getRef() == "")
			return mNode->getContent();
		QVector<QString>* mVec = convertPath(mNode->getRef());
		MyNode *rNode = myTree->findNode(mVec);
		delete mVec;
		if (rNode)
			return rNode->getContent();
		return NULL;
	}
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

//
bool FileManager::writeFile(QString* mContent, MyNode *mNode)
{
	QVector<QString> *mVec = mNode->getRefVec();
	if (!mVec->empty())
	{
		saveRef(mNode);
	}
	else if (mNode->getRef() != "")
	{
		MyNode *rNode = path2Node(mNode->getRef());
		int base = FileFactory::getInstance()->getFreeTable()->createFile(rNode->getLength());
		mNode->setContent(mContent);
		mNode->setBaseAddr(base);
		mNode->setLength(rNode->getLength());
		mNode->setRef("");
		QVector<QString>::Iterator it = rNode->getRefVec()->begin();
		QString str = mNode->getPath();
		while (it != rNode->getRefVec()->end())
		{
			if (it == str)
				break;
			it++;
		}
		rNode->getRefVec()->erase(it);
	}
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

bool FileManager::pasteFile(MyNode *mNode)
{
	if (mNode->getType())
		return 0;
	QString mName = *mNode->getName();
	MyNode* curN = myTree->getCurNode();
	MyNode* rNode;
	if (curN->checkChild(&mName))
	{
		// '0' - 48
		int i = 1;
		mName = mName.append("(1)");
		int len = mName.length();
		while (curN->checkChild(&mName))
		{
			mName[len - 2] = 48 + i;
		}
	}
	bool type = mNode->getType();
	MyNode *newNode = new MyNode(mNode->getType(), &mName);
	newNode->setBaseAddr(0);
	newNode->setLength(0);
	// Mei Ref
	if (mNode->getRef() == "")
	{
		newNode->setRef(mNode->getPath());
		rNode = mNode;
		//mNode->RefCountAdd();
		//rNode = mNode;
	}
	else
	{
		newNode->setRef(mNode->getRef());
		QVector<QString> *mVector = convertPath(mNode->getRef());
		rNode = myTree->findNode(mVector);
		delete mVector;
		//rNode->RefCountAdd();
	}
	bool result = myTree->insertNode(newNode);
	if (!result)
	{
		delete newNode;
		return 0;
	}
	rNode->getRefVec()->push_back(newNode->getPath());
	if (curNode)
		delete curNode;
	curNode = myTree->getCurChild();
	return 1;
}

bool FileManager::saveRef(MyNode* mNode)
{
	QVector<QString> *mVec = mNode->getRefVec();
	MyNode* rNode;
	for (int i = 0, l = mVec->length(); i < l; i++)
	{
		QVector<QString> *mVector = convertPath(mVec->at(i));
		rNode = myTree->findNode(mVector);
		rNode->setContent(mNode->getContent());
		rNode->setLength(mNode->getLength());
		rNode->setBaseAddr(FileFactory::getInstance()->getFreeTable()->createFile(rNode->getLength()));
		rNode->setRef("");
		delete mVector;
	}
	mNode->getRefVec()->clear();
	return 1;
}

QVector<QString>* FileManager::convertPath(const QString& mPath)
{
	QVector<QString> *mVector = new QVector<QString>();
	std::string mStr = mPath.toStdString();
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
	return mVector;
}

MyNode* FileManager::path2Node(QString &ref)
{
	QVector<QString> *mVec = convertPath(ref);
	MyNode* result = myTree->findNode(mVec);
	delete mVec;
	return result;
}

int FileManager::sizeSum()
{
	return FileFactory::getInstance()->getFreeTable()->sum();
}