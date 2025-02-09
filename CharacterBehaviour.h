#pragma once
#include <SDL.h>
#include "Astar.h"
#include <list>
#include "Vector2D.h"
#include "LevelMap.h"


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
	
	// Behaviour
	float foodMultiplier = 1;
	float bladderMultiplier = 1;
	float sleepMultiplier = 1;
	float hygeineMultiplier = 1;
	//timers
	int tileSpeed = 500; // 500 ms to move one tile
	int lastTileMoved = 0;

	void update();
	bool checkForTarget();
	void setUpPath();
	void passive();
	bool checkNextPosition();
	void moveToTarget();
	void setNextStep();
};

