#pragma once
#include <SDL.h>
#include "Astar.h"
#include <list>
#include "Vector2D.h"
#include "LevelMap.h"
#include "Graphs.h"
#include <vector>
#include "RoomAlgorithm.h"
#include "Room.h"

#include <queue>
using namespace std;

class CharacterBehaviour
{
	private:
	//Needs
	float food = 1000;
	float bladder = 1000;
	float sleep = 1000;
	float hygeine = 1000;
	float fun = 1000;
	const float maxNeedBar = 1000;

	float fun1 = 786;
	float fun2 = 554;

	struct Task {
		
		GameObject targetObject;
		Vector2D usePoint;
		bool isCompleted = false;
		bool taskSet = false;
		float timeTaskStarted = 0;
		bool taskStarted = false;


		Task(GameObject obj) :
			targetObject(obj)
		{
			cout << "\nTask Queued with Object: " << obj.getName() << endl;
			usePoint = Vector2D(targetObject.getLocation().x, targetObject.getLocation().y + 1);
		}

		// once the task has been begun
		void setStartTime()
		{
			timeTaskStarted = SDL_GetTicks();
			taskStarted = true;
		}
		void resetStartTime()
		{
			taskStarted = false;
		}

		// once the duration of the task is up, tell us if its completed...
		bool checkIfComplete()
		{
			if (SDL_GetTicks() > (timeTaskStarted + targetObject.getDuration()))
			{
				isCompleted = true;
				cout << "\nTask is Complete\n";
			}
			else
			{
				isCompleted = false;
			}

			return isCompleted;
		}

		void cancelTask()
		{
			isCompleted = true;
		}

		bool isTaskSet()
		{
			return taskSet;
		}

		void setTaskSet(bool t)
		{
			taskSet = t;
		}

	};
public:
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
	//Tasks
	//tasklist will queue the tasks the character deem neccessary to complete
	queue<Task> taskList;
	//Objects
	//this version of the room list will already have the objects within, so there is no need to keep a seperate objects list (i think)
	vector<Room> knownRooms;
	//Needs
	float foodMultiplier = 1.77;
	float bladderMultiplier = 1.60;
	float sleepMultiplier = 1;
	float hygeineMultiplier = 1.10;
	float funMultiplier = 1.90;

	SDL_Rect foodBar = {650,40,10,10};
	SDL_Rect bladderBar = { 650,60,10,10 };
	SDL_Rect sleepBar = { 650,80,10,10 };
	SDL_Rect hygeineBar = { 650,100,10,10 };
	SDL_Rect funBar = { 650,120,10,10 };

	bool bladderQueued = false;
	bool foodQueued = false;
	bool hygieneQueued = false;
	bool sleepQueued = false;
	bool funQueued = false;
	
	//NAVIGATION
	// //A* Navigation
	Astar nav;
	// Room pathfinding
	RoomAlgorithm roomAlg;
	//Level Memory
	Graphs levelKnowledge;
	LevelMap level;
	
	//render
	SDL_Rect sprite;
	// VECTORS
	Vector2D currentPosition;
	Vector2D targetPosition = Vector2D(-1, -1);
	Vector2D arrayPosition;

	//Navigation variables
	bool pathSet = false;
	int nextStep = 0;
	bool targetReached = false;
	bool targetSet = false;
	// will be set with final target and the room target interchangably
	Vector2D currentTarget = Vector2D(-1, -1);
	//render offsets
	int offsetX;
	int offsetY;
	//Rooms
	int currentRoom;
	int targetRoom;
	//timers
	int tileSpeed = 100; // 500 ms to move one tile
	int lastTileMoved = 0;

	void update(map<int, vector<int>> graphOG, vector<Room>* rList);
	bool checkForTarget();
	void setUpPath(Vector2D tar);

	void passive();
	void handleNeedBars();
	void renderNeedBars(SDL_Renderer* renderer);
	void checkNeeds();
	void getFoodTask();
	void getBladderTask();
	void getHygieneTask();
	void getSleepTask();
	void getFunTask();
	void handleTasks();

	bool checkNextPosition();
	void moveToTarget();
	void sameRoomProcess();
	void differentRoomProcess(map<int, vector<int>> graphOG);
	void pathFinding(map<int, vector<int>> graphOG, vector<Room>* rList);
	void queueTask(GameObject object);



};

