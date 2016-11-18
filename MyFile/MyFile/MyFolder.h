#ifndef MYFOLDER
#define MYFOLDER

#include <QString>

#include "MyNode.h"

class MyFolder : public MyNode
{
private:

public :
	MyFolder();
	MyFolder(const QString *mName);
	
};

#endif