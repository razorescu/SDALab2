#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	/*
	iterator constructor
	index is set to -1 (invalid position) if the list is empty
	otherwise, it is set to 0 (starting position)

	Complexity: O(1)
	*/
	if (list.head == nullptr)
		index = -1;
	else
		index = 0;
}

void ListIterator::first(){
	/*
	sets the index to the first position - 0

	Complexity: O(1)
	*/
	index = 0;
}

void ListIterator::next(){
	/*
	if valid, sets the index to indicate the next element in the list
	otherwise, throws exception

	Complexity: O(1)
	*/
	if (valid())
		index++;
	else
	{
		exception e;
		throw e;
	}
}

bool ListIterator::valid() const{
	/*
	checks for the current index to be at a valid size

	Complexity: O(1)
	*/
	if (index < 0 || index >= list.size())
		return false;
	return true;
}

TComp ListIterator::getCurrent() const{
	/*
	returns the element located in the node the index is currently indicating

	Complexity: O(n) ('index' number of steps)
	*/
	SLLNode* current = new SLLNode();
	current = list.head;
	unsigned int poz = 0;
	while (current->next != nullptr && poz < index) {
		current = current->next;
		poz++;
	}
	return current->info;
}


