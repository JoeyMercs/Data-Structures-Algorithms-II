// Joseph Mercedes
// Data Structures and Algorithms II
// Programming Project 3
// graph.cpp

#include "graph.h"
using namespace std;

#define INFINITY INT_MAX

graph::graph(int capacity){

	this->vertex_map = new hashTable(capacity);
}

// Insert Vertex Function
bool graph::insertVertex(std::string id){

	if (this->checkVertex(id))
		return false;

	vertex *ver = new vertex();
	ver->name = id;

	this->vertex_map->insert(id, ver);
	this->vertices.push_back(ver);

	return true;
}

// Check Vertex Function
bool graph::checkVertex(std::string id){

	return this->vertex_map->contains(id);
}

// Insert Edge Function
void graph::insertEdge(std::string start, std::string end, int distance){

	this->insertVertex(start);
	this->insertVertex(end);

	bool exists = false;

	vertex *dest = static_cast<vertex *> (this->vertex_map->getPointer(end, &exists));

	edge *ed = new edge();
	ed->cost = distance;
	ed->destination = dest;

	vertex *source = static_cast<vertex *> (this->vertex_map->getPointer(start, &exists));

	source->adjacent.push_back(ed);

	return;
}

// Dijkstra Algorithm Function
void graph::dijkstraAlg(std::string sourceVertex){

	heap Healp(this->vertices.size()+1);

	list<vertex *>::iterator iter;

	for(iter=this->vertices.begin(); iter!=this->vertices.end(); iter++){
		if((*iter)->name == sourceVertex)
			(*iter)->distance = 0;
		else
			(*iter)->distance = INFINITY;
		(*iter)->isKnown = false;
		(*iter)->prev = NULL;
		Healp.insert((*iter)->name, (*iter)->distance, (*iter));
	}

	vertex *ver;

	while(Healp.deleteMin(NULL,NULL,&ver) != 1){
		
		ver->isKnown = true;
		list<edge *>::iterator iterr;

		if (ver->distance == INFINITY)
			continue;

		for(iterr=ver->adjacent.begin(); iterr!=ver->adjacent.end(); iterr++){

			int newCost = ver->distance + (*iterr)->cost;

			if(newCost < (*iterr)->destination->distance){
				(*iterr)->destination->distance = newCost;
				Healp.setKey((*iterr)->destination->name,newCost);
				(*iterr)->destination->prev = ver;
			}
		}
	}

	return;
}

// Write To File Function
void graph::writeToFile(std::string filename){

	ofstream out(filename.c_str());

	list<vertex *>::iterator iter;

	string path;

	for(iter=this->vertices.begin(); iter!=this->vertices.end(); iter++){

		out << (*iter)->name << ": ";
		vertex *ver = (*iter);

		if(ver->distance == INFINITY)
			out << "NO PATH" << endl;
		else if(ver->distance == 0)
			out << ver->distance << " [" << ver->name << "]" << endl;
		else{
			out << ver->distance << " [";
			path = ver->name;
			while(ver->prev != NULL){
				path = ver->prev->name + ", " + path;
				ver = ver->prev;
			}
			out << path << "]" << endl;
		}
	}

	return;
}