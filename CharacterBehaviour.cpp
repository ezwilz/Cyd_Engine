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
	//cout << "\n7\n";
	// use the right list step/item according to how the character is navigating.
	//Check if the next position in the array is 0, it could have changed whilst the unit is moving.
	//cout << "NextStep: " << nextStep << " ListSize: " << nav.pathList.size() - 1;
		checkForTarget();
		cout << "\nFart1 \n" << nextStep << nav.pathList.size();
		if (nextStep != -1)
		{
			int x = nav.pathList[nextStep]->position.x;
			int y = nav.pathList[nextStep]->position.y;
			//cout << "\n8\n";
			cout << "\nFart2\n";

			if (level.house[y][x] != 0)
			{
				//cout << "\n8\n";
				cout << "\nFart3\n";

				return false;
			}
			else
				cout << "\nFart4\n";

			return true;
		}
		
		return false;
}

void CharacterBehaviour::moveToTarget()
{
	if (nextStep > -1 || nextStep < nav.pathList.size() - 1)
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
}


bool CharacterBehaviour::checkForTarget()
{
	if (roomAlg.targetToSend.x != -1)
	{
		if (arrayPosition.x == roomAlg.targetToSend.x && arrayPosition.y == roomAlg.targetToSend.y)
		{
			roomAlg.clearPath();
			pathSet = false;
			nav.pathList.clear();
			return true;
		}
	}
	else
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

	
	if (levelKnowledge.m_graph[currentRoom].size() != graphOG[currentRoom].size())
	{
		levelKnowledge.CopyVertices(currentRoom, graphOG);
	}

	//cout << "\nTesting it gets this far! 1\n";
	if (targetPosition.x == -1)
	{

		targetRoom = -1;
	}

	//if the target is in the same room follow one process or else do the graph process !
	if (targetRoom == currentRoom)
	{
		sameRoomProcess();
	}
	else if (targetRoom != -1 && targetRoom != currentRoom)
	{
		if (levelKnowledge.CheckForVertexPresence(targetRoom))
			differentRoomProcess(graphOG);
	}
	else if (targetRoom == -1)
	{
		if (roomAlg.targetToSend.x != -1)
			roomAlg.clearPath();
	}
	//cout << "\nTesting it gets this far! 2\n";
	// if array position is the target position, reset all the values that could lead to irregular data next time around. 
	if (arrayPosition.x == targetPosition.x && arrayPosition.y == targetPosition.y)
	{
		//reset the lists and the values!
		targetRoom = -1;
		// clear the Astar pathlist 
		nav.pathList.clear();
		//reset the final target position (where it was clicked)
		targetPosition = Vector2D(-1, -1);
		// also set the current target to the targetfinal position ?
		currentTarget = Vector2D(-1, -1);
		//reset the nextstep and the roomstep to -1 -1 so it cannot be used in a list and if it does it will bring  up and error.
		nextStep = -1;

		//roomAlg.clearPath();
		cout << "\nDestination Met\n";

		// reset pathset to false, because there is no path to be followed.
		pathSet = false;
		return;
	}

	

	cout << "\nSendTo: " << roomAlg.targetToSend << " Actual: " << targetPosition << " TargetRoom: " << targetRoom << " CurrentRoom: " << currentRoom << endl;

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
	cout << "\n1\n";
	// if AT the target
	if (arrayPosition.x == currentTarget.x && arrayPosition.y == currentTarget.y)
	{
		cout << "\nDestination Met\n";
		//subTarget = Vector2D(-1, -1);
		//graphPathSet = false;
		pathSet = false;
		targetRoom = -1;
		cout << "\n2\n";
		//roomPathList.clear();
		// this is not supposed to happen
		return;
	}

	cout << "\n3\n";
	if (!pathSet && currentTarget.x != -1 && currentTarget.y != -1 && arrayPosition.x != targetPosition.x && arrayPosition.y != targetPosition.y)
	{
		cout << "\n4\n";
		cout << "\nSetting Up the Path\n";
		setUpPath(targetPosition);
	}
	cout << "\n5\n";

	//cout << "\n Current Target: " << currentTarget << " Final target Position: " << targetFinalPosition << " Current Position: " << arrayPosition << endl;

	if (!nav.pathList.empty())
	{
		cout << "\n6\n";
		checkNextPosition();
		cout << "\n7\n";
		moveToTarget();
		cout << "\n8\n";

	}
}

void CharacterBehaviour::differentRoomProcess(map<int, vector<int>> graphOG) 
{
	//set up the path if it has not been set already. 
	if (!roomAlg.pathSet)
	{
		roomAlg.setUpPath();
		if (roomAlg.targetToSend.x != -1)
			setUpPath(roomAlg.targetToSend);
	}

	if (!nav.pathList.empty())
	{
		cout << "\nMoving to Target\n";
		checkNextPosition();
		moveToTarget();
		roomAlg.setNextTarget();
	}


}

void CharacterBehaviour:: createNewDoor(int iD, Vector2D loco)
{
	Door newDoor;
	newDoor.id = iD;
	newDoor.location = loco;
	//doors.push_back(newDoor);
}