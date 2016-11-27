#include "MyFolder.h"

MyFolder::MyFolder()
{
	MyNode::MyNode();
	type = 1;
}

MyFolder::MyFolder(const QString *mName)
{
	MyNode::MyNode(1, mName);
}