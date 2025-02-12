#pragma once
#include <SDL.h>
#include "Astar.h"
#include <list>
#include "Vector2D.h"
#include "LevelMap.h"
#include "Graphs.h"
#include <vector>

class CharacterBehaviour
{
	private:
	//Needs
	float food = 1000;
	float bladder = 1000;
	float sleep = 1000;
	float hygeine = 1000;
	// TODO: make a task list where the unit will work through the tasks and if its empty, they will become autonomous

public:
	//Level Memory
	Graphs levelKnowledge;
	vector<Vector2D> temporaryPathList;
	int tempStep = 0;
	Vector2D temporaryTargetPosition = Vector2D(-1, -1);
	vector<Vector2D> vertexPositions;
	bool graphPathSet = false;


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
	int tileSpeed = 250; // 500 ms to move one tile
	int lastTileMoved = 0;

	void update();
	bool checkForTarget();
	void setUpPath();
	void passive();
	bool checkNextPosition();
	bool checkNextPositionTempList();
	void moveToTarget();
	void moveToTempTarget();
	void moveToGraphTarget();
	void setNextStep();

	vector<Vector2D> getGraphPath();

};

