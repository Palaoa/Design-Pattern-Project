#ifndef MYNODE_H_
#define MYNODE_H_

#include <QString>
#include <QVector>
#include <QDir>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QIODevice>

#define INITIAL_LENGTH 200

class MyNode
{
protected:
	QString name;
	int protect;	// quan xian (Hai Mei Xiang Hao)  yue da yue hao
	MyNode *child, *next, *parent;
	int refCount = 0;  // zhi xiang gai jie dian de references
	QString ref;       // Gai Jie Dian Shi Ji Wei Zhi
	QVector<QString>* refVec;  // Zhi Xiang Gai Jie Dian De ref
	QString content;
	int baseAddr;
	int length;
protected:
	bool type;		// 0 - wenjian 1 - wenjianjia
	/*
	!!!!!
	GUAN YU REF DE DI FANG HAI YAO GAI!!!
	!!!!!
	*/
	


public:

	MyNode();
	MyNode::MyNode(bool type ,const QString* name);
	~MyNode(); 

	QString* getName()
	{
		return &name;
	}

	void setName(QString& mName)
	{
		name = mName;
	}

	bool getType()
	{
		return type;
	}

	void setType(bool mType)
	{
		type = mType;
	}

	MyNode* getParent()
	{
		return parent;
	}

	MyNode* getChild()
	{
		return child;
	}

	MyNode* getNext()
	{
		return next;
	}

	void setParent(MyNode *mParent)
	{
		parent = mParent;
	}

	void setChild(MyNode *mChild)
	{
		child = mChild;
	}

	void setNext(MyNode *mNext)
	{
		next = mNext;
	}

	int getProtect()
	{
		return protect;
	}

	void setProtect(int mProtect)
	{
		protect = mProtect;
	}

	MyNode* checkChild(const QString *mName);

	QString getRef()
	{
		return ref;
	}

	QString getPath()
	{
		QString mPath;
		MyNode *mNode = this;
		while (mNode)
		{
			mPath = "/" + mNode->name + mPath;
			mNode = mNode->parent;
		}
		return mPath;

	}
	void setRef(const QString & mDir)
	{
		ref = mDir;
	}

	QVector<QString>* getRefVec()
	{
		return refVec;
	}

	int getRefCount()
	{
		return refCount;
	}

	bool RefCountAdd()
	{
		if (refCount < 0)
			return false;
		refCount++;
		return 1;
	}

	bool RefCountSub()
	{
		if (refCount <= 0)
			return 0;
		refCount--;
		return 1;
	}

	virtual QString* getContent()
	{
		return &content;
	}
	virtual void setContent(QString* str)
	{
		if (content == NULL)
			content = *new QString();
		content = *str;
	}
	virtual int getBaseAddr()
	{
		return baseAddr;
	}
	virtual int getLength()
	{
		return length;
	}
	virtual void setBaseAddr(int i)
	{
		baseAddr = i;
	}
	virtual void setLength(int i)
	{
		length = i;
	}
private:

};


#endif
