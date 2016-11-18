#include "MyTree.h"

MyTree::MyTree()
{
	QString mName = "root";
	MyFolder* mf = new MyFolder(&mName);
	currentNode = rootNode = mf;
	currentPath->push_back(new QString("root"));
}

MyTree::MyTree(MyNode *mRoot)
{
	currentNode = rootNode = mRoot;
	currentPath = new QVector<QString*>();
	currentPath->push_back(new QString(*(currentNode->getName())));
}

MyTree::~MyTree()
{
	delete currentPath;
	// Yao Gai
	delete currentNode;
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

QVector<QString*>* MyTree::getCurPath() const
{
	return currentPath;
}

bool MyTree::enterCD(QVector<QString*> *mPath)
{
	MyNode *mCurNode = rootNode;
	int mLen = mPath->length();
	// xian que ding neng tiao zhuan
	if (mLen < 1 || *(mPath->at(0)) != "root")
	{
		return false;
	}
	for (int i = 1; i < mLen; i++)
	{
		mCurNode = mCurNode->checkChild(mPath->at(i));
		if (mCurNode)
			continue;
		return false;
	}
	// zai tiao zhuan
	currentPath->clear();
	for (int i = 0; i < mLen; i++)
	{
		currentPath->push_back(new QString(*(mPath->at(i))));
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
	MyNode *p1 = currentNode;
	MyNode *p2 = currentNode->getNext();
	while (p2)
	{
		p1 = p2;
		p2 = p2->getNext();
	}
	p1->setNext(mNode);
	mNode->setParent(currentNode);
	mNode->setNext(NULL);
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
	delete mNode;
	return 1;
}