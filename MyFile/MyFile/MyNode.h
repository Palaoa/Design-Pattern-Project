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
private:
	QString name;
	bool type;		// 0 - wenjian 1 - wenjianjia
	int protect;	// quan xian (Hai Mei Xiang Hao)  yue da yue hao
	MyNode *child, *next, *parent;
	int refCount = 0;  // zhi xiang gai jie dian de references
	MyNode* ref;       
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

	MyNode* checkChild(QString *mName);
	virtual QString* getContent();
	virtual void setContent(QString*);
	virtual int getBaseAddr();
	virtual int getLength();
	virtual void setBaseAddr(int);
	virtual void setLength(int);
private:

};


#endif
