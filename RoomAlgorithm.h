#pragma once
#include "Graphs.h"
#include "LevelMap.h"
#include "Vector2D.h"


class RoomAlgorithm
{
private:

	struct Door {
		int id = -1;
		Vector2D location = Vector2D(-1, -1);
	};

public: 
	// pointer to the characters level knowledge, this will be dynamic! 
	Graphs* levelKnowledge;
	LevelMap level;

	vector<int> roomPathList;
	bool pathSet = false;
	int nextStep = -1;

	int currentRoom, targetRoom, nextRoom;

	//keeps track of the doors and all their positions
	vector<Door> doors;
	//target and current position!
	Vector2D* currentPosition;
	Vector2D* targetPosition;

	Vector2D targetToSend = Vector2D(-1,-1);
	//Functions
	// Set up path when the target room is definitely in the known vertices.
	void setUpPath();
	// clear path only when the current position =  target OR final target room ?
	void clearPath();
	
	void setNextTarget();

	void createNewDoor(int iD, Vector2D loco);

	void convertTargetRoomToVector();



};

