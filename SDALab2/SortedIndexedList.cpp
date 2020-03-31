#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	this->head = nullptr;
	this->r = r;
	this->size = 0;
}

int SortedIndexedList::size() const {
	//TODO - modify after add
	if (head == nullptr)
		return 0;
	else
		return this->size;
}

bool SortedIndexedList::isEmpty() const {
	if (head == nullptr)
		return true;
	return false;
}

TComp SortedIndexedList::getElement(int i) const{
	//TODO - Implementation
	return NULL_TCOMP;
}

TComp SortedIndexedList::remove(int i) {
	//TODO - Implementation
	return NULL_TCOMP;
}

int SortedIndexedList::search(TComp e) const {
	//TODO - Implementation
	return 0;
}

void SortedIndexedList::add(TComp e) {
	/*
	if list empty -> add first
	if list not empty -> iterate through list
		if we get to last element -> add last
		else -> add to position
	*/
	if (head == nullptr)//adding first node (empty list)
	{
		this->head->info = e;
		this->head->next = nullptr;
		this->size++;
	}
	else //list not empty
	{
		SLLNode* current;
		current->info = head->info;
		current->next = head->next;
		while (r(current->info, e) && current->next != nullptr)
		{
			current = current->next;
			/*current->info = current->next->info; //current.info ia valoarea din 'info' a urmatorului nod
			current->next = current->next->next; //current.next ia pointerul 'next' al urmatorului nod*/
		}
		if (current->next == nullptr) //we're at the last node (adding to last position)
		{
			SLLNode* node;
			node->info = e;
			node->next = nullptr;
			current->next = node;
			this->size++;
		}
		else
		{
			/*
			we reached a point where the relation stopped being true for the next element
			so we are going to add the new node in between two other nodes
			*/
			SLLNode* node;
			node->info = e;
			node->next = current->next;
			current->next = node;
			this->size++;
		}
	}
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
}
