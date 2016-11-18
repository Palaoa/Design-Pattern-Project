#include "MyFolder.h"

MyFolder::MyFolder()
{
	MyNode::MyNode();

}

MyFolder::MyFolder(const QString *mName)
{
	MyNode::MyNode(1, mName);
}