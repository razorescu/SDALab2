#include <assert.h>

#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

bool relation1(TComp e1, TComp e2) {
	if (e1 >= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedIndexedList list = SortedIndexedList(relation1);
	assert(list.size() == 0);
	assert(list.isEmpty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.isEmpty());
    ListIterator iterator = list.iterator();
    assert(iterator.valid());
    iterator.first();
    assert(iterator.getCurrent() == 1);
    iterator.next();
    assert(!iterator.valid());
    iterator.first();
    assert(iterator.valid());
    assert(list.search(1) == 0);
    assert(list.remove(0) == 1);
    assert(list.size() == 0);
    assert(list.isEmpty());
}

void testReunion() {
    SortedIndexedList list1 = SortedIndexedList(relation1);
    SortedIndexedList list2 = SortedIndexedList(relation1);
    SortedIndexedList reunion = SortedIndexedList(relation1);

    for (int i = 0; i < 10; i++) {
        list1.add(i);
    }
    for (int i = 2; i < 15; i++) {
        list2.add(i);
    }
    reunion.reunion(list1,list2);

    ListIterator itReun = reunion.iterator();
    itReun.first();
    int i = 2;
    while (itReun.valid()) {
        assert(i == reunion.getElement(reunion.search(itReun.getCurrent())));
        itReun.next();
        i++;
    }
    cout << "Reunion test passed!";
}

