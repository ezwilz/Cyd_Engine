#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <list>

#include "Vector2D.h"
#include "LevelMap.h"
#include "SDL.h"


using namespace std;

class Astar
{
private:
	bool searching = false;
	struct Node {
		Vector2D position;
		Vector2D parent = Vector2D(-1,-1); 
		double gCost, hCost, fCost;

		Node(Vector2D pos, Vector2D parentPos, double g = 0, double h = 0)
			: position(pos), parent(parentPos), gCost(g), hCost(h), fCost(g + h) {
		}

		// Comparison operator for sorting (lowest fCost is best)
		bool operator<(const Node& other) const {
			return fCost < other.fCost;
		}

		bool operator==(const Node& other) const {
			return position.x == other.position.x && position.y == other.position.y;
		}

	};

	Node targetPosition = Node(Vector2D(-1, -1), Vector2D(-1, -1), 0, 0);
	Node currentPosition = Node(Vector2D(-1, -1), Vector2D(-1, -1), 0, 0);

	Node finalNode = Node(Vector2D(-1,-1), Vector2D(-1, -1),0,0);
	Node currentNode = Node(Vector2D(-1, -1), Vector2D(-1, -1), 0, 0);
	Node startNode = Node(Vector2D(-1, -1), Vector2D(-1, -1), 0, 0);
	


	LevelMap level;
public:
	double smallestCost = 1000000000000;

	vector<Node*> openList, closedList;
	vector<Node*> pathList;
	void setTargetPosition(int x, int y);
	void getAllNeighbours( int rows, int cols);
	void checkOpenList();
	int getIndex(const std::vector<Node*>& list, const Vector2D target);

	void search(int currX, int currY, int tarX, int tarY);
	void buildPath();

	double diagonalDistance(Vector2D a, Vector2D b);

	vector<Node> getPath();
	bool CheckForItemInList(vector<Node*> nodeList , Vector2D node);
	bool CheckForTargetInClosed();
	double getDistanceAtoB(Node a, Node b);

};

