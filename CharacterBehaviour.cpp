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
bool CharacterBehaviour::checkNextPositionTempList()
{
	//Check if the next position in the array is 0, it could have changed whilst the unit is moving.
	int x = nav.pathList[tempStep]->position.x;
	int y = nav.pathList[tempStep]->position.y;
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
		int x = arrayPosition.x;
		int y = arrayPosition.y;

		int newX = nav.pathList[nextStep]->position.x;
		int newY = nav.pathList[nextStep]->position.y;

		//reset the old tile
		level.house[y][x] = 0;
		//set the new one
		level.house[newY][newX] = 4;

		arrayPosition = Vector2D(newX, newY);

		if (currentRoom != targetRoom)
			printf("\nNeed to refer to room graph to go there.\n");

		

		nextStep -= 1;
		lastTileMoved = SDL_GetTicks();
	}

	//Checks if we are at the target before moving anywwhere
	checkForTarget();
}

void CharacterBehaviour::moveToTempTarget()
{
	if (SDL_GetTicks() > (tileSpeed + lastTileMoved))
	{
		int x = arrayPosition.x;
		int y = arrayPosition.y;

		int newX = nav.pathList[tempStep]->position.x;
		int newY = nav.pathList[tempStep]->position.y;

		//reset the old tile
		level.house[y][x] = 0;
		//set the new one
		level.house[newY][newX] = 4;

		arrayPosition = Vector2D(newX, newY);




		tempStep -= 1;
		lastTileMoved = SDL_GetTicks();
	}

	//Checks if we are at the target before moving anywwhere
	//checkForTarget();
}

void CharacterBehaviour::moveToGraphTarget()
{
	
}

void CharacterBehaviour::setNextStep()
{

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

void CharacterBehaviour::update()
{
	// set the current room
	int xA = arrayPosition.x;
	int yA = arrayPosition.y;
	currentRoom = level.rooms[yA][xA];
	int xB = targetPosition.x;
	int yB = targetPosition.y;
	targetRoom = level.rooms[yB][xB];

	

	// if target POsition is -1,-1 just return!
	if (targetPosition.x == -1 && targetPosition.y == -1)
	{
		return;
	}

	if (targetRoom != currentRoom)
	{
		if (tempStep == -1)
		{
			// assume final position is met
			graphPathSet = false;
			temporaryTargetPosition = Vector2D(-1, -1);
			temporaryPathList.clear();
			tempStep = 0;
		}
		cout << "\nTarget Room is not Current Room\n";
		//graph movement
		if (!graphPathSet && temporaryTargetPosition.x == -1 && temporaryTargetPosition.y == -1)
		{
			if (targetPosition.x != -1 && targetPosition.y != -1)
			{
				cout << "\nGraph path is not set, and temporary position equals -1\n";
				cout << "\nSetting the path\n";
				temporaryPathList = getGraphPath();
				cout << "\nPath Set\n";
				cout << "\nChecking if temp path list is empty\n";
				if (!temporaryPathList.empty())
				{
					cout << "\nTemp List is not empty, setting the temporary target position to the step in the temporary path\n";
					temporaryTargetPosition = temporaryPathList[tempStep];
					cout << "\nTemp target position set\n";
				}
				else
					cout << "\nTemp List is empty\n";

				cout << "\nChecking if temp target position != -1, if it doesnt, then we are using Astar\n";
				if (temporaryTargetPosition.x != -1 && temporaryTargetPosition.y != -1)
				{
					cout << "\nTemp Target Position != -1\n";
					nav.search(arrayPosition.x, arrayPosition.y, temporaryTargetPosition.x, temporaryTargetPosition.y);
					cout << "\nTroom: " << targetRoom << "\nTarget Position: " << targetPosition << "\nTemp target position: " << temporaryTargetPosition << "\nCurrent position: " << arrayPosition << endl;
				}
				else
					cout << "\nTemp target postion == -1\n";

				graphPathSet = true;
			}
		}

		// Check that the next position is free
		cout << "\Checking if the path is set\n";
		if (graphPathSet) {
			cout << "\nPath is set\n";
			cout << "\nChecking availability of the next tile\n";
			checkNextPositionTempList();
			cout << "\nMoving to the next step in the Astar path finding\n";
			// move to the new position
			moveToTempTarget();
		}
		else
			cout << "\nPath is not set\n";

		
		
		//levelKnowledge.printGraph();
	}
	else
	{
		if (graphPathSet)
		{
			graphPathSet = false;
			temporaryTargetPosition = Vector2D(-1, -1);
			temporaryPathList.clear();
		}
		temporaryTargetPosition = Vector2D(-1, -1);
		
		if (targetPosition.x == arrayPosition.x && targetPosition.y == arrayPosition.y)
		{
			cout << "Target has been met.";
			targetPosition = Vector2D(-1, -1);
			return;
		}
		// if the path is not set and the target position is not -1,-1, search for the path
		if (!pathSet && targetPosition.x != -1 && targetPosition.y != -1)
		{
			setUpPath();
		}


	// Check that the next position is free
		checkNextPosition();

		// move to the new position
		moveToTarget();
	}
	

	currentPosition.x = (arrayPosition.x * 10) + offsetX;
	currentPosition.y = (arrayPosition.y * 10) + offsetY;

	player.x = currentPosition.x;
	player.y = currentPosition.y;
	//cout << "\n Current Position: " << currentPosition << " Array Position: " << arrayPosition << " TargetPosition: " << targetPosition << "\n";
}

void CharacterBehaviour::setUpPath()
{
	nav.search(arrayPosition.x, arrayPosition.y, targetPosition.x, targetPosition.y);

	nextStep = nav.pathList.size() - 1;

	pathSet = true;
}

vector<Vector2D> CharacterBehaviour::getGraphPath()
{
	temporaryPathList.clear();
	vector<int> numberedPath = levelKnowledge.returnPath(currentRoom, targetRoom);
	for (int o : numberedPath)
	{
		for (int i = 0; i < levelKnowledge.roomsNDoorsList.size(); i++)
		{
			if (levelKnowledge.roomsNDoorsList[i].iD == o)
			{
				temporaryPathList.push_back(levelKnowledge.roomsNDoorsList[i].position);
			}
		}
	}
	tempStep = temporaryPathList.size() - 1;

	return temporaryPathList;
}

