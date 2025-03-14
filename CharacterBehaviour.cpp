#include "CharacterBehaviour.h"


void CharacterBehaviour::passive()
{
	food -= 0.5 * foodMultiplier;
	bladder -= 0.5 * bladderMultiplier;
	hygeine -= 0.5 * hygeineMultiplier;
	sleep -= 0.5 * sleepMultiplier;
} 

bool CharacterBehaviour::checkNextPosition()
{
	// use the right list step/item according to how the character is navigating.
	//Check if the next position in the array is 0, it could have changed whilst the unit is moving.

		int x = nav.pathList[nextStep]->position.x;
		int y = nav.pathList[nextStep]->position.y;

		if (level.house[y][x] != 0)
		{
			return false;
		}
		else
			return true;
}

void CharacterBehaviour::moveToTarget()
{
	if (SDL_GetTicks() > (tileSpeed + lastTileMoved))
	{
		// use the right list step/item according to how the character is navigating.
		

		int x = arrayPosition.x;
		int y = arrayPosition.y;

		int newX = nav.pathList[nextStep]->position.x;
		int newY = nav.pathList[nextStep]->position.y;

		//reset the old tile
		level.house[y][x] = 0;
		//set the new one
		level.house[newY][newX] = 4;

		arrayPosition = Vector2D(newX, newY);

		//cout << "\nTarget: " << targetFinalPosition << " Current: " << arrayPosition << " Target Room: " << targetRoom << " Current Room: " << currentRoom << endl;


		nextStep -= 1;
		lastTileMoved = SDL_GetTicks();


	}

	//Checks if we are at the target before moving anywwhere
	checkForTarget();
}


bool CharacterBehaviour::checkForTarget()
{
	if (arrayPosition.x == targetPosition.x && arrayPosition.y == targetPosition.y)
	{
		targetPosition = Vector2D(-1, -1);
		pathSet = false;
		nav.pathList.clear();
		return true;
	}
	else
	{
		return false;
	}
}

void CharacterBehaviour::update(map<int, vector<int>> graphOG)
{
	// SET THE CURRENT ROOMS AND TARGET ROOM
	// set the current room
	int xA = arrayPosition.x;
	int yA = arrayPosition.y;
	currentRoom = level.rooms[yA][xA];
	int xB = targetPosition.x;
	int yB = targetPosition.y;
	targetRoom = level.rooms[yB][xB];


	if (targetPosition.x == -1)
	{
		targetRoom = -1;
	}
	
	// if array position is the target position, reset all the values that could lead to irregular data next time around. 
	if (arrayPosition.x == targetPosition.x && arrayPosition.y == targetPosition.y)
	{
		//reset the lists and the values!
		targetRoom = -1;
		doorTargetPosition = Vector2D(-1, -1);
		// clear the Astar pathlist 
		nav.pathList.clear();

		//reset the final target position (where it was clicked)
		targetPosition = Vector2D(-1, -1);

		// also set the current target to the targetfinal position ?
		currentTarget = Vector2D(-1, -1);

		//reset the nextstep and the roomstep to -1 -1 so it cannot be used in a list and if it does it will bring  up and error.
		nextStep = -1;


		cout << "\nDestination Met\n";
		roomTargetFromDoor = Vector2D(-1, -1);
		graphPathSet = false;
		roomPathList.clear();

		// reset pathset to false, because there is no path to be followed.
		pathSet = false;
		return;
	}


	//if the target is in the same room follow one process or else do the graph process !
	if (targetRoom == currentRoom)
		sameRoomProcess();
	else if(targetRoom != -1)
		differentRoomProcess( graphOG);


	

	currentPosition.x = (arrayPosition.x * 10) + offsetX;
	currentPosition.y = (arrayPosition.y * 10) + offsetY;

	player.x = currentPosition.x;
	player.y = currentPosition.y;


}

void CharacterBehaviour::setUpPath(Vector2D tar)
{
	nav.search(arrayPosition.x, arrayPosition.y, tar.x, tar.y);

	nextStep = nav.pathList.size() -1;

	pathSet = true;
}

void CharacterBehaviour::sameRoomProcess() {
	//set current target to the target final position
	currentTarget = targetPosition;





	if (arrayPosition.x == currentTarget.x && arrayPosition.y == currentTarget.y)
	{
		cout << "\nDestination Met\n";
		doorTargetPosition = Vector2D(-1, -1);
		roomTargetFromDoor = Vector2D(-1, -1);
		graphPathSet = false;
		pathSet = false;
		targetRoom = -1;
		roomPathList.clear();
		// this is not supposed to happen
		return;
	}


	if (!pathSet && currentTarget.x != -1 && currentTarget.y != -1 && arrayPosition.x != targetPosition.x && arrayPosition.y != targetPosition.y)
	{

		cout << "\nSetting Up the Path\n";
		setUpPath(targetPosition);
	}

	//cout << "\n Current Target: " << currentTarget << " Final target Position: " << targetFinalPosition << " Current Position: " << arrayPosition << endl;

	if (!nav.pathList.empty())
	{
		checkNextPosition();
		moveToTarget();

	}
}

void CharacterBehaviour::differentRoomProcess(map<int, vector<int>> graphOG) {


	// if the vertice is known to this character proceed, if not, return!
	if (!levelKnowledge.CheckForVertexPresence(targetRoom) && targetRoom > 99)
	{
		cout << "\nTarget Is Not Known to this character\n";
		return;
	}


	// runs only once, as the graph path is set, the variable is changed ! 
	if (!graphPathSet && targetRoom > 99)
	{
		cout << "\nPath is not set and targetroom is...\n"; 
		roomPathList = levelKnowledge.returnPath(currentRoom, targetRoom);
		if (roomPathList.empty())
		{
			printf("\nNo Path\n");
			graphPathSet = false;
			roomPathStep = -1;
			targetRoom = -1;
			//return;
		}
		else
		{
			graphPathSet = true;
			roomPathStep = roomPathList.size() - 1;
			cout << "\nPath has been created...\n"; 
		}
	}

	if (!roomPathList.empty())
	{
		cout << "\nRoom path is not empty\n"; 
		cout << "\nDoor Pos: " << doorTargetPosition << " Room Pos: " << roomTargetFromDoor << " Current Pos: " << arrayPosition << endl;
		if (roomPathList[roomPathStep] < 199 && doorTargetPosition.x == -1)
		{
			cout << "\nRoom Target is a Door\n";
			for (const auto& e : doors)
			{
				if (e.id == targetRoom)
				{
					cout << "\nSet the target position\n";
					doorTargetPosition = e.location;
				}
			}


			if (!pathSet && doorTargetPosition.x != -1 && doorTargetPosition.y != -1 && arrayPosition.x != doorTargetPosition.x && arrayPosition.y != doorTargetPosition.y)
			{

				cout << "\nSetting Up the ASTAR Path to a DOOR\n";
				setUpPath(doorTargetPosition);
			}

		} // check if character is in a door and if the target room is not a door!
		else if (currentRoom < 199 && roomPathList[roomPathStep] > 199)
		{
			cout << "\nRoom Target is a ROOM\n";
			if (!roomFound)
			{
				//IF AT A DOOR, CYCLE THROUGH ALL DIRECTIONS UNTIL THE TARGET ROOM IS FOUND! 
				int directionX[] = { -1, 1,  0, 0, -1, -1,  1,  1 };
				int directionY[] = { 0, 0, -1, 1, -1,  1, -1,  1 };

				for (int i = 0; i < 8; i++) {
					cout << "\nSearching for the right ROOM\n";
					int newX = arrayPosition.x + directionX[i];
					int newY = arrayPosition.y + directionY[i];

					if (level.rooms[newY][newX] == roomPathList[roomPathStep])
					{
						roomTargetFromDoor = Vector2D(newX, newY);
						cout << "\nROOM FOUND\n";
						roomFound = true;
						break;
					}

				}
			}
			

			if (!pathSet && roomTargetFromDoor.x != -1 && roomTargetFromDoor.y != -1 && arrayPosition.x != roomTargetFromDoor.x && arrayPosition.y != roomTargetFromDoor.y)
			{

				cout << "\nSetting Up the ASTAR Path to a ROOM\n";
				setUpPath(roomTargetFromDoor);
			}
		}
	}

	if (!nav.pathList.empty())
	{
		checkNextPosition();
		moveToTarget();
		if (arrayPosition == doorTargetPosition || arrayPosition == roomTargetFromDoor)
		{
			int x = arrayPosition.x;
			int y = arrayPosition.y;
			levelKnowledge.CopyVertices(level.rooms[y][x], graphOG);
			cout << "\nDestination Met\n";
			doorTargetPosition = Vector2D(-1, -1);
			roomTargetFromDoor = Vector2D(-1, -1);
			nav.pathList.clear();
			graphPathSet = false;
			pathSet = false;
			targetRoom = -1;
		}

	}
}

void CharacterBehaviour:: createNewDoor(int iD, Vector2D loco)
{
	Door newDoor;
	newDoor.id = iD;
	newDoor.location = loco;
	doors.push_back(newDoor);
}