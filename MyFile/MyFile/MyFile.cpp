#include "MyFile.h"

MyFile::MyFile()
{
	MyNode::MyNode();
	content = *(new QString());
	baseAddr = 0;
	length = INITIAL_LENGTH;
}

MyFile::MyFile(const QString* mName, int mBase, int mLen = INITIAL_LENGTH)
{
	MyNode::MyNode(0, mName);
	baseAddr = mBase;
	length = mLen;
}

MyFile::~MyFile()
{
	MyNode::~MyNode();
	delete &content;
}

int MyFile::getBaseAddr()
{
	return baseAddr;
}

void MyFile::setBaseAddr(int mBase)
{
	baseAddr = mBase;
}

int MyFile::getLength()
{
	return length;
}

void MyFile::setLength(int mLen)
{
	length = mLen;
}

QString* MyFile::getContent()
{
	return &content;
}

void MyFile::setContent(QString* mContent)
{
	content = *mContent;
}