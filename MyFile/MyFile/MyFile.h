#ifndef MYFILE_H_
#define MYFILE_H_

#include <QString>
#include "MyNode.h"

class MyFile :public MyNode
{
private:

public:
	MyFile();
	MyFile(const QString* mName, int mBase, int mLen = INITIAL_LENGTH);
	~MyFile();
	QString* getContent();
	void setContent(QString*);
	int getBaseAddr();
	int getLength();
	void setBaseAddr(int);
	void setLength(int);
};

#endif