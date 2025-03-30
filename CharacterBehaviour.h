#pragma once
#include <SDL.h>
#include "Astar.h"
#include <list>
#include "Vector2D.h"
#include "LevelMap.h"
#include "Graphs.h"
#include <vector>
#include "RoomAlgorithm.h"

using namespace std;

class CharacterBehaviour
{
	private:

	//Needs
	float food = 1000;
	float bladder = 1000;
	float sleep = 1000;
	float hygeine = 1000;
	// TODO: make a task list where the unit will work through the tasks and if its empty, they will become autonomous

	struct Door {
		int id = -1;
		Vector2D location = Vector2D(-1, -1);
	};

public:
	RoomAlgorithm roomAlg;


	//Level Memory
	Graphs levelKnowledge;
	//vector<int> roomPathList;
	//int roomPathStep = -1;
	////Vector2D doorTargetPosition = Vector2D(-1, -1);
	////Vector2D roomTargetFromDoor = Vector2D(-1, -1);
	//Vector2D subTarget = Vector2D(-1, -1);

	//vector<Vector2D> vertexPositions;
	//bool graphPathSet = false;
	//bool roomFound = false;

	//DOORS STUFF
	//vector<Door> doors;
	//movement
	LevelMap level;
	Astar nav;

	SDL_Rect player;

	Vector2D currentPosition;
	Vector2D targetPosition = Vector2D(-1, -1);
	Vector2D arrayPosition;
	bool pathSet = false;
	int numberOfSteps;
	int nextStep = 0;
	bool targetReached = false;
	bool targetSet = false;

	// will be set with final target and the room target interchangably
	Vector2D currentTarget = Vector2D(-1, -1);


	//references
	int offsetX;
	int offsetY;

	int currentRoom;
	int targetRoom;
	
	// Behaviour
	float foodMultiplier = 1;
	float bladderMultiplier = 1;
	float sleepMultiplier = 1;
	float hygeineMultiplier = 1;
	//timers
	int tileSpeed = 100; // 500 ms to move one tile
	int lastTileMoved = 0;

	void update(map<int, vector<int>> graphOG);
	bool checkForTarget();
	void setUpPath(Vector2D tar);
	void passive();
	bool checkNextPosition();
	void moveToTarget();
	void getRoomTarget();
	void navigateDoor();

	void sameRoomProcess();
	void differentRoomProcess(map<int, vector<int>> graphOG);

	void createNewDoor(int iD, Vector2D loco);

};

