#ifndef FILEITERATOR_H_
#define FILEITERATOR_H_

#include "MyNode.h"
#include "MyTree.h"
#include "MyFile.h"
#include "MyFolder.h"

//Xiang Jian:
//http://www.cplusplus.com/reference/iterator/iterator/

class FileIterator : public std::iterator < std::input_iterator_tag, int >
{
private:
	MyNode *rootNode, *curNode;
	QVector<MyNode*>* mVector;
public:
	FileIterator(MyNode*);
	MyNode* next();
	bool hasNext();
	bool remove();
	FileIterator& operator++();
	bool operator==(const FileIterator& rhs);
	bool operator!=(const FileIterator& rhs);
};
#endif