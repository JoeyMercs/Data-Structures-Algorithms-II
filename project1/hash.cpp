// Joseph Mercedes
// Data Structures and Algorithms II
// Program Assignment #1
// hash.cpp

#include <iostream>
#include "hash.h"

using namespace std;

hashTable::hashTable(int size){

	capacity = getPrime(size);
	data.resize(capacity);

	filled = 0;

	for (int i=0; i<data.size(); i++)
		data[i].isOccupied = false;
}

//Insert Function
int hashTable::insert(const std::string &key, void *pv){
	 
	bool success;

	if (contains(key))
		return 1;

	if (filled >= capacity/2){
		success = rehash();
		if(!success)
			return 2;	
	}

	int hashLocation = hash(key);

	while (data[hashLocation].isOccupied){
		hashLocation++;
		hashLocation %= capacity;
	}

	if (!data[hashLocation].isOccupied){
		data[hashLocation].key = key;
		data[hashLocation].isOccupied = true;
		data[hashLocation].isDeleted = false;
		data[hashLocation].pv = pv;
		filled++;
		return 0;
	}

	return -1;
}

//Contains Function
bool hashTable::contains(const std::string &key){

	int position = findPos(key);

	if (position == -1)
		return false;
	else
		return true;
}

// Hash Function
int hashTable::hash(const std::string &key){

	int hashVal = 0;

	for(int i=0; i<key.length(); i++)
		hashVal = 41*hashVal+key[i];

	hashVal %= capacity;
	if (hashVal<0)
		hashVal += capacity;

	return hashVal;
}

// Find Position Function
int hashTable::findPos(const std::string &key){

	int hashVal = hash(key);
	if(!data[hashVal].isOccupied)
		return -1;

	while (data[hashVal].isOccupied) {
        if (data[hashVal].key == key && !data[hashVal].isDeleted)
            return hashVal;
		
		hashVal++;
		hashVal %= capacity;		
	}

	return -1;
}

// Rehash Function
bool hashTable::rehash(){

	vector<hashItem> oldHash = data;

	filled = 0;

	int nextHashSize = getPrime(capacity);
	data.clear();
	data.resize(nextHashSize);
	capacity = nextHashSize;

	for (int i=0; i<capacity; i++){
		data[i].isOccupied = false;
	}

	for (int i=0; i<oldHash.size(); i++){
		if (oldHash[i].isOccupied){
			insert(oldHash[i].key);
		}
	}

	oldHash.clear();

	return true;
}

// Get Prime Function
unsigned int hashTable::getPrime(int size){

	// Using a seperate program to compute prime numbers:
	vector<int> primes;
	primes.push_back(100069);
    primes.push_back(250091);
    primes.push_back(500083);
    primes.push_back(750097);
    primes.push_back(999983);
    primes.push_back(1000099);
	primes.push_back(3000077);

	for (int i=0; i<primes.size(); i++){
		if(primes[i]>size)
			return primes[i];
	}
	return 0;
}

// Get Pointer Function
void* hashTable::getPointer(const std::string &key, bool *b){

	int pos = findPos(key);

	if (pos == -1 || data[pos].isDeleted){
		*b = false;
		return NULL;
	}
	else{
		*b = true;
		return data[pos].pv;
	}
}

// Set Pointer Function
int hashTable::setPointer(const std::string &key, void *pv){

	int pos = findPos(key);

	if (pos == -1)
		return 1;
	else{
		data[pos].pv = pv;
		return 0;
	}
}

// Remove Function
bool hashTable::remove(const std::string &key){

	int pos = findPos(key);

	if (pos == -1)
		return false;
	else{
		data[pos].isDeleted = true;
		return true;
	}
}