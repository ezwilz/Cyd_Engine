#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <array>
#include <list>
using namespace std;

class Graphs
{
private:
	map<int, vector<int>> m_graph;
	list<int> knownVertices;

public:

	Graphs() {}

	void addVertex(int vertex);
	void addEdge(int v1, int v2);
	void removeVertex(int vertex);
	vector<int> getVertices();
	vector<int>  getEgdes(int vertex);
	void printGraph();
	bool CheckConnection(int vertexA, int vertexB);
	bool CheckForNeighbour(int vertexA, int vertexB);
	bool CheckForConnection(int a, int b);
	vector<int> returnPath(int currentVertex, int targetVertex);
	bool CheckForVertexPresence(int x);
	map<int, vector<int>>  GetGraph();
	void CopyVertices(int vertex, map<int, vector<int>> graphOG);
	int MovingThroughDoor(int curr, int last, map<int, vector<int>>  graphOG);
};

