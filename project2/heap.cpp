// Joseph Mercedes
// Data Structures and Algorithms II
// Programming Project 2

#include <iostream>
#include "heap.h"

using namespace std;

// Heap Constructor
heap::heap(int capacity){

	this->capacity = capacity;
	this->filled = 0;

	data.resize(capacity+1);
	mapping = new hashTable(capacity*2);
}

// Insert Function
int heap::insert(const std::string &id, int key, void *pv){
	
	if (capacity == filled)
		return 1;

	else if (mapping->contains(id) && filled < capacity)
		return 2;

	else{

		if(filled == capacity - 1)
			data.resize(capacity*2);

		filled++;

		data[filled].id = id;
		data[filled].key = key;
		data[filled].pData = pv;

		mapping->insert(id,&data[filled]);
		percolateUp(filled);

		return 0;
	}
}

// Set Key Function
int heap::setKey(const std::string &id, int key){

	bool exists = false;
	node *pn = static_cast<node *> (mapping->getPointer(id, &exists));

	if(!exists)
		return 1;

	int nodePos = getPos(pn);
	data[nodePos].key = key;

	bool percolDown = ((nodePos*2 <= filled) && (data[nodePos].key > data[nodePos*2].key)) || ((nodePos*2+1 <= filled) && (data[nodePos].key > data[nodePos*2+1].key)) || (nodePos == 1);

	// Increase Key
	if(percolDown)
		percolateDown(nodePos);

	// Decrease Key
	else if(data[nodePos].key < data[nodePos/2].key)
		percolateUp(nodePos);

	return 0;
}


// Delete Minimun Function
int heap::deleteMin(std::string *pId, int *pKey, void *ppData){

	if(filled == 0)
		return 1;

	// If pId, pKey, ppData Supplied:
	if(pId)
		*pId = data[1].id;
	if(pKey)
		*pKey = data[1].key;
	if(ppData)
		*(static_cast<void **> (ppData)) = data[1].pData;

	mapping->remove(data[1].id);
	data[1] = data[filled--];
	percolateDown(1);

	return 0;

}

// Remove Function
int heap::remove(const std::string &id, int *pKey, void *ppData){

	bool exist = false;
	node *pn = static_cast<node *> (mapping->getPointer(id, &exist));

	if(!exist)
		return 1;

	int nodePos = getPos(pn);

	// If pKey, ppData Supplied:
	if(pKey)
		*pKey = data[nodePos].key;
	if(ppData)
		ppData = data[nodePos].pData;

	data[nodePos] = data[filled--];
	mapping->setPointer(data[nodePos].id, &data[nodePos]);

	bool percolDown = ((nodePos*2 <= filled ) && (data[nodePos].key > data[nodePos*2].key)) || ((nodePos*2+1 <= filled) && (data[nodePos].key > data[nodePos*2+1].key)) || (nodePos == 1);

	// Increase Key
	if(percolDown)
		percolateDown(nodePos);

	// Decrease Key
	else if(data[nodePos].key < data[nodePos/2].key)
		percolateUp(nodePos);

	return 0;
}

// Percolate Up Function
void heap::percolateUp(int posCur){

	int hole = posCur;
	node temp = data[posCur];
	
	for( ; hole > 1 && temp.key < data[hole/2].key; hole /= 2){
		data[hole] = data[hole/2];
		mapping->setPointer(data[hole].id, &data[hole]);
	}

	data[hole] = temp;
	mapping->setPointer(data[hole].id, &data[hole]);
}

//Percolate Down Function
void heap::percolateDown(int posCur){

	int hole = posCur;
	int child;
	node temp = data[posCur];

	for( ; hole*2 <= filled; hole = child){

		child = hole*2;

		if(child != filled && data[child+1].key < data[child].key)
			child++;
		if(data[child].key < temp.key){
			data[hole] = data[child];
			mapping->setPointer(data[hole].id, &data[hole]);
		}
		else
			break;
	}

	data[hole] = temp;
	mapping->setPointer(data[hole].id, &data[hole]);
}

// Get Position Function
int heap::getPos(node *pn){

	int pos = pn - &data[0];
	return pos;
}