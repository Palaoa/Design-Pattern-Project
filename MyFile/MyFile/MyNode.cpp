#include "MyNode.h"

MyNode::MyNode()
{
	name = *(new QString());
	type = 1;  // wen jian jia
	protect = 0;
	child = NULL;
	next = NULL;
	parent = NULL;
}

MyNode::MyNode(bool mType, const QString* mName)
{
	name = *(new QString(*mName));
	type = mType;  //
	protect = 0;
	child = NULL;
	next = NULL;
	parent = NULL;
}

MyNode::~MyNode()
{
	delete &name;
}

MyNode* MyNode::checkChild(const QString *mName)
{
	MyNode *mNode = child;
	if (!mNode)
	{
		return NULL;
	}
	while (mNode)
	{
		if (*(mNode->getName()) == *mName)
			return mNode;
		mNode = mNode->next;
	}
	return mNode;
}