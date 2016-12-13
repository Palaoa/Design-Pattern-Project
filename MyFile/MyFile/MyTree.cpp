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

MyNode* MyTree::findNode(QVector<QString> *mPath)
{
	MyNode *mCurNode = rootNode;
	int mLen = mPath->length();
	int start = 0;
	while (isBlock(mPath->at(start)))
		start++;
	// xian que ding neng tiao zhuan
	if (mLen < 1 || mPath->at(start) != "root")
	{
		return false;

	}
	for (int i = start + 1; i < mLen; i++)
	{
		mCurNode = mCurNode->checkChild(&mPath->at(i));
		if (mCurNode)
			continue;
		return 0;
	}
	return mCurNode;
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
	if (!currentNode->getChild())
	{
		currentNode->setChild(mNode);
		mNode->setParent(currentNode);
		mNode->setChild(NULL);
		mNode->setNext(NULL);
		return 1;
	}
	while (p1->getNext())
	{
		p1 = p1->getNext();
	}
	p1->setNext(mNode);
	mNode->setParent(currentNode);
	mNode->setNext(NULL);
	mNode->setChild(NULL);
	return 1;
}

bool MyTree::deleteNode(MyNode* mNode)
{
	//MyNode *mNode = currentNode->checkChild(mName);
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
		deleteNode(mChild);
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
			int type, mBase, mLen, vLen;
			in >> type;
			MyNode *mFile = new MyNode(0, &name);
			if (type == 1)
			{
				QString str = in.readLine();
				mFile->setRef(str);
				mFile->setBaseAddr(0);
				mFile->setLength(0);
			}
			else
			{
				in >> mBase >> mLen;
				mFile->setBaseAddr(mBase);
				mFile->setLength(mLen);
				if (type)
				{
					in >> vLen;
					QString ref;
					while (vLen)
					{
						in >> ref;
						mFile->getRefVec()->push_back(ref);
						vLen--;
					}
				}
				QString str = in.readLine();
				while (!str.isNull())
				{
					mFile->getContent()->append(str);
					str = in.readLine();
				}
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
				if (p->getRef() != "")
				{
					out << "1 " << p->getRef();
					out.flush();
				}
				else
				{
					
					if (!p->getRefVec()->empty())
					{
						QVector<QString> *mVec = p->getRefVec();
						int len = mVec->length();
						out << "2 " << p->getBaseAddr() << " " << p->getLength() << " " << len << endl;
						out.flush();
						for (int i = 0; i < len; i++)
						{
							out << mVec->at(i) << endl;
						}
						out.flush();
					}
					else
					{
						out << "0 " << p->getBaseAddr() << " " << p->getLength() << endl;
						out.flush();
					}
					out << *p->getContent();
					out.flush();
				}
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
	currentNode = mNode;
	MyNode* temp = mNode;
	currentPath->clear();
	while (temp && *temp->getName() != "root")
	{
		currentPath->insert(0, *temp->getName());
		temp = temp->getParent();
	}
	currentPath->insert(0, "root");
}

bool MyTree::isBlock(const QString &mStr)
{
	for each (QChar var in mStr)
	{
		if (var != ' ')
			return 0;
	}
	return 1;
}