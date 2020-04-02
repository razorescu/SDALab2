#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	/*
	list constructor
	head - SLLNode -> points to a null node at init
	r - Relation -> establishes the relation the list will be sorted on
	length - unsigned int -> saves the size of the list, is initially 0
		length was only created in order to save time and not iterate through the list
		on every call to size()

	Complexity: O(1)
	*/
	this->head = nullptr;
	this->r = r;
	this->length = 0;
}

int SortedIndexedList::size() const {
	/*
	returns the number of nodes in the list (the size)

	Complexity: O(1)
	*/
	if (head == nullptr)
		return 0;
	else
		return this->length;
}

bool SortedIndexedList::isEmpty() const {
	/*
	if the head points to a null node -> list is empty
	otherwise, it is not

	Complexity: O(1)
	*/
	if (head == nullptr)
		return true;
	return false;
}

TComp SortedIndexedList::getElement(int i) const{
	/*
	if the list is empty or the index is invalid -> throws exception
	otherwise, returns the value inside the node at position i

	Complexity: O(n) (always i steps)
	*/
	if (head == nullptr || i < 0 || i >= this->length) { //list is empty/invalid index
		exception e;
		throw e;
	}
	unsigned int poz = 0;
	SLLNode* current;
	current = head;
	while (current->next != nullptr && poz <= i) { //iterating through the list until the last node
		if (poz == i) {
			return current->info; //if we're at the right position, returns the element in the node
		}
		poz++;
		current = current->next;
	}
	return current->info; //element is at last node
}

TComp SortedIndexedList::remove(int i) {
	/*
	if the list is empty or the index is invalid -> throws exception
	otherwise, removes a node from the list and returns its value

	Complexity: Best, average - O(n), Worst - O(n^2)
	In the worst case, we have to remove the last node, which means
	setting the node before it to point to null -> iterating again
	*/
	if (head == nullptr || i < 0 || i >= this->length) { //list is empty/invalid index
		exception e;
		throw e;
	}
	unsigned int poz = 1;
	SLLNode* current;
	current = head;
	TComp value;
	if (i == 0) { //first node is to be removed
		if (head->next != nullptr) { //more than 1 node in list
			value = head->info;
			head = head->next; //former head node gets removed
			this->length--;
			return value;
		}
		else { //only 1 node in list
			value = head->info;
			head = nullptr; //list becomes empty
			this->length--;
			return value;
		}
	}
	if (i == this->length - 1) { //last node is to be removed
		while (current->next != nullptr && poz <= i) { //we iterate to last node
			poz++;
			current = current->next;
		}
		value = current->info;
		current = nullptr; //last node is set to null
		poz = 1;
		current = head;
		while (current->next != nullptr && poz < i) { //setting the second before last's node "next" to point to null
			poz++;
			current = current->next;
		}
		current->next = nullptr;
		this->length--;
		return value;
	}
	SLLNode* future;
	future = current->next;
	while (future->next != nullptr && poz <= i) { //ordinary node in the list
		if (poz == i) {
			value = future->info;
			current->next = future->next; //node is removed from the list
			this->length--;
			return value;
		}
		poz++;
		current = current->next;
		future = current->next;
	}
	exception e;
	throw e;
}

int SortedIndexedList::search(TComp e) const {
	/*
	searches for an element in the list
	if the list is empty returns -1
	otherwise, iterates through the list until it finds
	the position the element is at and returns that position
	if the end of the list is reached, stops iterating and returns -1

	Complexity: 
	*/
	if (head == nullptr)
		return -1; //empty list
	SLLNode* current;
	current = head;
	unsigned int poz = 0; //position counter
	if (e == current->info) { //element is in first node
		return 0;
	}
	while (current->next != nullptr) { //iterating through the list until the last node is detected
		if (current->info == e)
			return poz; //if element is found, returns the position and exits
		poz++; 
		current = current->next; //if element is not found, continues iterating
	}
	if (e == current->info) { //element is in last node
		return poz;
	}
	return -1; //if we've reached the end of the list, returns -1
}

void SortedIndexedList::add(TComp e) {
	/*
	if list empty -> add first
	if list not empty -> iterate through list
		if we get to last element -> add last
		else -> add to position

	Complexity: Best case - O(1)
				Average case - O(n)
				Worst case - O(n^2)

	Mentiune: imi pare sincer rau pentru harababura pe care urmeaza sa o vedeti,
	initial gandisem si construisem functia intr-un mod in care in anumite cazuri
	esua monumental si mi-a fost mai simplu pe moment sa adaug failsafe-uri decat
	sa o regandesc de la cap la coada
	*/
	if (head == nullptr)//adding first node (empty list)
	{
		SLLNode* node = new SLLNode();
		node->info = e;
		node->next = nullptr;
		head = node;
		this->length++;
	}
	else //list not empty
	{
		SLLNode* current;
		current = head;
		while (r(current->info, e) == true && current->next != nullptr) { //finding the point the relation is false at
			current = current->next;
		}
		if (current->next == nullptr) //we're at the last node in the list
		{
			if (r(current->info,e)) { //relation is true between the current node and the element -> insert after
				SLLNode* node = new SLLNode();
				node->info = e;
				node->next = nullptr;
				current->next = node;
				this->length++;
			}
			else { //relation is false between the current node and the element -> insert before
				SLLNode* failsafe = new SLLNode();
				failsafe = head;
				if (failsafe->next != nullptr) { //making sure we have at least 2 elements
					while (failsafe->next->next != nullptr) {
						failsafe = failsafe->next;
					}
				}
				if (current == head) { //the head is the first and last node and we have to place the element before it
					SLLNode* node = new SLLNode();
					node->info = e;
					node->next = current;
					head = node;
					this->length++;
				}
				else { //placing the element before the last node and setting the node before it to point to it next
					SLLNode* node = new SLLNode();
					node->info = e;
					node->next = failsafe->next;
					failsafe->next = node;
					this->length++;
				}
			}

		}
		else {
			if (current == head) { //we're adding before the head of the list
				SLLNode* node = new SLLNode();
				node->info = e;
				node->next = current;
				head = node;
				this->length++;
			}
			else
			{
				if (r(current->info,e)) { //relation is true between the current node and the element -> insert after
					SLLNode* node = new SLLNode();
					node->info = e;
					node->next = current->next;
					current->next = node;
					this->length++;
				}
				else { //relation is false between the current node and the element -> insert before
					current = head;
					while (r(current->next->info, e) == true && current->next->next != nullptr) {
						current = current->next;
					}//setting the node before the added element to point to it next
					SLLNode* node = new SLLNode();
					node->info = e;
					node->next = current->next;
					current->next = node;
					this->length++;
				}
			}
		}
	}
}

ListIterator SortedIndexedList::iterator(){
	/*
	returns an iterator object for the list

	Complexity: O(1)
	*/
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() { 
}
