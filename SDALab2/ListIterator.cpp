#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	if (list.head == nullptr)
		index = -1;
	else
		index = 0;
}

void ListIterator::first(){
	index = 0;
}

void ListIterator::next(){
	if (valid())
		index++;
}

bool ListIterator::valid() const{
	if (index < 0 || index >= list.size)
		return false;
	return true;
}

TComp ListIterator::getCurrent() const{
	//TODO - Implementation
	return NULL_TCOMP;
}


