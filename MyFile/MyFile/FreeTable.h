#ifndef FREETABLE_H_
#define FREETABLE_H_

#include <QString>
#include <list>
#include <QLinkedList>
#include <QFile>
#include <QTextStream>

#define MaxSize 10000
#define MAXLEN 10000;

struct freeNode
{
	int base;
	int length;
};

class FreeTable
{
private:
	QLinkedList<freeNode> *freeTable;
	static FreeTable *instance;
	
public:
	static FreeTable *getInstance();
	FreeTable();
	~FreeTable();
	int createFile(int length);  // 返回基址 不成功返回-1
	bool deleteFile(int base, int length);

	// open 和 save 还没仔细改 最后再看!!

	void save();
	void open();
	int sum();
};


#endif