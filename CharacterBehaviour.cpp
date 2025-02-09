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

		cout << "\nCurrent Room: " << currentRoom << " TargetRoom: " << targetRoom << endl;
		if (currentRoom != targetRoom)
			printf("\nNeed to refer to room graph to go there.\n");

		nextStep -= 1;
		lastTileMoved = SDL_GetTicks();
	}

	//Checks if we are at the target before moving anywwhere
	checkForTarget();
}

void CharacterBehaviour::moveToGraphTarget()
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

		cout << "\nCurrent Room: " << currentRoom << " TargetRoom: " << targetRoom << endl;
		if (currentRoom != targetRoom)
			printf("\nNeed to refer to room graph to go there.\n");

		nextStep -= 1;
		lastTileMoved = SDL_GetTicks();
	}

	//Checks if we are at the target before moving anywwhere
	checkForTarget();
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
		//graph movement

	}
	else
	{
		
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