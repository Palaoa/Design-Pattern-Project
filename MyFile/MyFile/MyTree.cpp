#include "MyTree.h"

MyTree::MyTree()
{
	QString mName = "root";
	MyNode* mf = new MyNode(1, &mName);
	currentNode = rootNode = mf;
	currentPath = new QVector<QString>();
	currentPath->push_back("root");
	QDir qdir("root");
	open(rootNode, qdir);
}

MyTree::MyTree(MyNode *mRoot)
{
	currentNode = rootNode = mRoot;
	currentPath = new QVector<QString>();
	currentPath->push_back(*currentNode->getName());
	QDir qdir("root");
	open(rootNode, qdir);
}

MyTree::~MyTree()
{
	delete currentPath;
	QDir *temp = new QDir;
	bool ok = temp->mkdir("root");
	QDir qdir = "root";
	save(rootNode, qdir);
}

MyNode* MyTree::getCurNode()
{
	return currentNode;
}

QVector<MyNode*> *MyTree::getCurChild()
{
	MyNode *mNode = currentNode->getChild();
	QVector<MyNode*> *mVec = new QVector<MyNode*>();
	while (mNode)
	{
		mVec->push_back(mNode);
		mNode = mNode->getNext();
	}
	return mVec;
}

bool MyTree::goBack()
{
	MyNode *mNode = currentNode->getParent();
	if (mNode)
	{
		currentPath->pop_back();
		currentNode = mNode;
		return 1;
	}
	return 0;
}

QVector<QString>* MyTree::getCurPath() const
{
	return currentPath;
}

bool MyTree::enterCD(QVector<QString> *mPath)
{
	MyNode *mCurNode = rootNode;
	int mLen = mPath->length();
	// xian que ding neng tiao zhuan
	if (mLen < 1 || mPath->at(0) != "root")
	{
		return false;
	}
	for (int i = 1; i < mLen; i++)
	{
		mCurNode = mCurNode->checkChild(&mPath->at(i));
		if (mCurNode)
			continue;
		return false;
	}
	// zai tiao zhuan
	currentPath->clear();
	for (int i = 0; i < mLen; i++)
	{
		currentPath->push_back(mPath->at(i));
	}
	return 1;
}

bool MyTree::insertNode(MyNode *mNode)
{
	QString *mName = mNode->getName();
	// cun zai zhe ge ming zi
	if (currentNode->checkChild(mName))
	{
		return 0;
	}
	MyNode *p1 = currentNode->getChild();
	MyNode *p2 = p1->getNext();
	if (!currentNode->getChild())
	{
		p1->setChild(mNode);
		mNode->setParent(p1);
		mNode->setChild(NULL);
		mNode->setNext(NULL);
		return 1;
	}
	while (p2)
	{
		p1 = p2;
		p2 = p2->getNext();
	}
	p1->setNext(mNode);
	mNode->setParent(currentNode);
	mNode->setNext(NULL);
	mNode->setChild(NULL);
	return 1;
}

bool MyTree::deleteNode(QString* mName)
{
	MyNode *mNode = currentNode->checkChild(mName);
	if (!mNode)
	{
		return 0;
	}
	// chu li next liebiao
	MyNode *mNext = currentNode->getChild();
	if (mNext == mNode)
	{
		currentNode->setChild(mNode->getNext());
	}
	else
	{
		while (mNext->getNext() != mNode)
		{
			mNext = mNext->getNext();
		}
		mNext->setNext(mNode->getNext());
	}
	// di gui shan chu gai dian
	MyNode* mChild = mNode->getChild();
	while (mChild)
	{
		deleteNode(mChild->getName());
		mChild = mNode->getChild();
	}
	return FileFactory::getInstance()->deleteFile(mNode);
}

void MyTree::open(MyNode* mNode, QDir mDir)
{
	MyNode* head = mNode;
	QString str = mDir.path();

	foreach(QFileInfo mfi, mDir.entryInfoList())
	{
		if (mfi.isFile())
		{
			QString name = mfi.fileName();
			QFile file(mfi.absoluteFilePath());
			file.open(QIODevice::ReadOnly);
			QTextStream in(&file);
			int mBase, mLen;
			in >> mBase >> mLen;
			MyNode *mFile = new MyNode(0, &name);
			mFile->setBaseAddr(mBase);
			mFile->setLength(mLen);
			QString str = in.readLine();
			while (!str.isNull())
			{
				mFile->getContent()->append(str);
				str = in.readLine();
			}

			mFile->setNext(mNode->getChild());
			mNode->setChild(mFile);
			mFile->setParent(mNode);
			mFile->setChild(NULL);
			file.close();
		}
		else
		{
			if (mfi.fileName() == "." || mfi.fileName() == "..")
				continue;
			str = mfi.absoluteFilePath();
			QDir qd = mfi.absoluteFilePath();
			QString name = mfi.fileName();
			MyNode *mFolder = new MyNode(1, &name);
			mFolder->setNext(mNode->getChild());
			mNode->setChild(mFolder);
			mFolder->setParent(mNode);
			mFolder->setChild(NULL);
			open(mFolder, qd);
		}
	}
	return;
}

void MyTree::save(MyNode* mNode, QDir mDir)
{
	MyNode* p = mNode->getChild();
	QString path;
	while (p)
	{
		if (p->getType())
		{
			mDir.mkdir(*(p->getName()));
			save(p, QDir(mDir.path() + "/" + *(p->getName())));
		}
		else
		{
			path = mDir.path() + "/" + *(p->getName());
			QFile file(path);
			file.open(QIODevice::WriteOnly);
			file.close();
			file.open(QIODevice::WriteOnly);
			if (file.isOpen())
			{
				QTextStream out(&file);
				out << p->getBaseAddr() << " " << p->getLength() << endl;
				out.flush();
				out << *p->getContent();
				out.flush();
				file.close();
			}
		}
		p = p->getNext();
	}
	return;
}

bool MyTree::enterChild(MyNode* mNode)
{
	if (mNode->getParent() != currentNode)
		return 0;
	MyNode* child = currentNode->getChild();
	while (child)
	{
		if (child == mNode)
		{
			currentNode = mNode;
			currentPath->push_back(*mNode->getName());
			return 1;
		}
		child = child->getNext();
	}
	return 0;
}

void MyTree::setCurNode(MyNode* mNode)
{
	currentNode == mNode;
	MyNode* temp = mNode;
	currentPath->clear();
	while (*temp->getName() != "root")
	{
		currentPath->insert(0, *temp->getName());
	}
	currentPath->insert(0, "root");
}