// Joseph Mercedes
// Data Structures and Algorithms II
// Programming Project 3
// dijkstra.cpp

#include "graph.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>

using namespace std;

// Loads the Graph
void loadGraph(graph &theGraph, ifstream &input) {

    string line, start, end;
    int cost;

    while(getline(input,line)){
        istringstream stream(line);
        stream >> start >> end >> cost;

        theGraph.insertEdge(start,end,cost);
    }
    return;

}

// Main Function that determines the starting vertex in Dijkstra's Algorithm and the format of the output file
int main() {

    string inputFile, outputFile;
    string vertexStart;
    bool inputGood = false;

    cout << "Enter name of graph file: ";
    cin >> inputFile;
    ifstream input(inputFile.c_str());
    if(!input.is_open()){
        cout << "Invalid Filename: " << inputFile << endl;
        exit(1);
    }

    graph theGraph(100);
    loadGraph(theGraph, input);

    while(!inputGood){
        cout << "Enter a valid vertex id for the starting vertex: ";
        cin >> vertexStart;

        if (theGraph.checkVertex(vertexStart))
            inputGood = true;
        else
            cout << "Invalid Vertex: " << vertexStart << endl;
    }

    clock_t t1 = clock();
    theGraph.dijkstraAlg(vertexStart);
    clock_t t2 = clock();

    double timeDijkstra = ((double) (t2-t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to apply Dijkstra's algorithm: ";
    cout << timeDijkstra << endl;

    cout << "Enter name of output file: ";
    cin >> outputFile;

    theGraph.writeToFile(outputFile);

    input.close();

    return 0;
}