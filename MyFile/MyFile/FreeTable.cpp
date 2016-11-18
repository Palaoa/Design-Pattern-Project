#include "FreeTable.h"

FreeTable::FreeTable()
{
	freeTable = new QLinkedList<freeNode>();
}

FreeTable::~FreeTable()
{
	save();
}

FreeTable* FreeTable::getInstance()
{
	if (instance == NULL)
	{
		instance = new FreeTable();
		instance->open();
	}
	return instance;
}

bool FreeTable::deleteFile(int base, int length)
{
	QLinkedList<freeNode>::iterator itF = freeTable->begin();
	QLinkedList<freeNode>::iterator itTemp1;
	QLinkedList<freeNode>::iterator itTemp2;
	itTemp1 = itF;
	itTemp2 = ++itF;

	while (itF != freeTable->end())
	{

		//si zhong ke neng qing kuang
		if (base >= itTemp1->base + itTemp1->length&&base + length <= itTemp2->base)  //
		{
			if (base == itTemp1->base + itTemp1->length) //qian mian yi yang
			{
				if (base + length == itTemp2->base)  // qian hou dou yi yang
				{
					itTemp1->length += length + itTemp2->length;
					freeTable->erase(itTemp2);
					return 1;
				}
				else  // qian mian yi yang, hou mian bu yi yang
				{
					itTemp1->length += length;
					return 1;
				}
			}
			else if (base + length == itTemp2->base)  // qian mian bu yi yang, hou mian yi yang
			{
				itTemp2->base = base;
				itTemp2->length += length;
				return 1;
			}
			else  // qian hou dou bu yi yang
			{
				freeNode freeNode;
				freeNode.length = length;
				freeNode.base = base;
				freeTable->insert(itTemp2, freeNode);
				return 1;
			}
		}
		itTemp1 = itTemp2;
		itTemp2 = ++itF;

	}
	if (itTemp2 == freeTable->end())  // zai zui hou
	{
		if (freeTable->begin()->base >= base + length)  // zai kai tou 
		{
			if (freeTable->begin()->base == base + length)
			{
				freeTable->begin()->base = base;
				freeTable->begin()->length += length;
				return 1;
			}
			else
			{
				freeNode freeNode;
				freeNode.base = base;
				freeNode.length = length;
				freeTable->push_front(freeNode);
				return 1;
			}
		}
		else if (itTemp1->base + itTemp1->length < base)
		{
			freeNode freeNode;
			freeNode.base = base;
			freeNode.length = length;
			freeTable->push_back(freeNode);
			return 1;
		}
		else if (itTemp1->base + itTemp1->length == base)
		{
			itTemp1->length += length;
			return 1;
		}
	}

	return 0;

}

int FreeTable::createFile(int length)
{
	QLinkedList<freeNode>::iterator itF = freeTable->begin();
	int itbase;
	while (itF != freeTable->end())
	{
		if (itF->length >= length)
		{
			itbase = itF->base;
			if (itF->length == length)  // zheng hao yi yang da
			{
				freeTable->erase(itF);
			}
			else
			{
				itF->base += length;
				itF->length -= length;
			}
			return itbase;
		}
		itF++;

	}
	return -1;
	//wei zhao dao
}
/*
void FreeTable::open()
{
	QFile file("freetable.txt");
	file.open(QIODevice::ReadOnly);
	QTextStream in(&file);
	int i;
	in >> i;
	while (i)
	{
		freeNode node;
		in >> node.base >> node.length;
		freeTable->push_back(node);
		i--;
	}
	file.close();
}

void FreeTable::save()
{
	QFile file("freetable.txt");
	file.open(QIODevice::WriteOnly);
	QTextStream out(&file);
	QLinkedList<freeNode>::iterator it = freeTable->begin();
	out << freeTable->size() << " ";
	while (it != freeTable->end())
	{
		out << it->base << " " << it->length << " ";
		++it;
	}
	file.close();
}
*/