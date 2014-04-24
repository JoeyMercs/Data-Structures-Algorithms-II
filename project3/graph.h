// Joseph Mercedes
// Data Structures and Algorithms II
// Programming Project 3
// graph.h

#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"
#include "heap.h"

#include <iostream>
#include <string>
#include <list>
#include <climits>
#include <fstream>

class graph {

	public:
		
		// Creates the graph through a hashTable of verticies
		graph(int capacity = 100);

		// Inserts a vertex in the graph with string "id"
		// Returns true on success
		// Returns false if the vertex already exists
		bool insertVertex(std::string id);

		// Checks if a vertex wth string "id" already exists
		// Returns true on success
		// Returns false if the vertex exists already
		bool checkVertex(std::string id);

		// Inserts an edge with a start string, end string, and cost distance
		void insertEdge(std::string start,std::string end, int dist);

		// Runs Digkstra's Algorithm
		void dijkstraAlg(std::string sourceVertex);

		// Write to an output file of name "filename"
		void writeToFile(std::string filename);

	private:

		class edge;

		class vertex {
			public:
				std::string name;
				std::list<edge *> adjacent;
				vertex *prev;
				bool isKnown;
				int distance;
		};

		class edge {
			public:
				int cost;
				vertex *destination;
		};

		std::list<vertex *> vertices;
		hashTable *vertex_map;
};

#endif //_GRAPH_H