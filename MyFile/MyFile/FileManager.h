#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include <QString>

#include "FreeTable.h"
#include "MyFile.h"
#include "MyFolder.h"
#include "MyNode.h"
#include "MyTree.h"

class FileManager
{
private:
	static FileManager* instance;

public:
	FileManager();
	~FileManager();
	FileManager* getInstance();

};

#endif