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

void CharacterBehaviour::navigateDoor()
{
	int directionX[] = { -1, 1,  0, 0 }; // Left, Right
	int directionY[] = { 0, 0, -1, 1 }; // Up, Down

	for (int i = 0; i < 4; i++) {
		int newX = arrayPosition.x + directionX[i];
		int newY = arrayPosition.y + directionY[i];

		if (level.rooms[newY][newX] == targetRoom)
		{
			if (targetRoom != currentRoom)
			{
				roomTargetPosition = Vector2D(newX, newY);
				cout << "\nFound the target room!\n";
			}
		}
	}

	cout << "roomTP then arrayP \n" << roomTargetPosition << "  " << arrayPosition << endl;

	currentTarget = roomTargetPosition;

	//printf("\nDOOR_RIGHT_NOW\n");
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
	if (arrayPosition.x == targetFinalPosition.x && arrayPosition.y == targetFinalPosition.y)
	{
		targetFinalPosition = Vector2D(-1, -1);
		pathSet = false;
		nav.pathList.clear();
		return true;
	}
	else
	{
		return false;
	}
}

void CharacterBehaviour::getRoomTarget()
{
	// get the graph path,by checking with the graph knowledge ? 
	// This sets the roomPathList
	getGraphPath();

	// if the roomstep is not null, proceed
	if (roomStep != -1)
	{
		// the room target position is the next step in the path? 
		roomTargetPosition = roomPathList[roomStep];
	}
	if (arrayPosition.x == roomPathList[roomStep].x && arrayPosition.y == roomPathList[roomStep].y)
	{
		roomStep -= 1;
	}
}

void CharacterBehaviour::update()
{
	// SET THE CURRENT ROOMS AND TARGET ROOM
	// set the current room
	int xA = arrayPosition.x;
	int yA = arrayPosition.y;
	currentRoom = level.rooms[yA][xA];
	int xB = targetFinalPosition.x;
	int yB = targetFinalPosition.y;
	targetRoom = level.rooms[yB][xB];

	// SET THE POSITION STEP TO -1 IF THE CURRENT POSITION IS THE TARGET --  MEANS THAT THE VECTOR ERROR WONT ARISE RANDOMLY!
	if (currentPosition == currentTarget)
	{
		nextStep = -1;
	}
	// SAME THING FOR THE ROOM STEP, SO THE NEXT ROOM ISNT BEING LOOKED FOR WHEN THERE IS NOT ONE
	if (currentRoom == targetRoom)
	{
		roomStep = -1;
	}

	/*cout << "\nList of Known Rooms and Doors: ";
	for (int i = 0; i < levelKnowledge.roomsNDoorsList.size(); i++)
	{
		cout << "\nRoom ID: " << levelKnowledge.roomsNDoorsList[i].iD << "\nPosition: " << levelKnowledge.roomsNDoorsList[i].position;
	}
	cout << "\nEnd of List\n\n\n\n";*/

	//levelKnowledge.printGraph();
	//cout << "\n\n\n";

	//cout << "\n" << targetRoom << " " << currentRoom << endl;
	
	// if array position is the target position, reset all the values that could lead to irregular data next time around. 
	if (arrayPosition.x == targetFinalPosition.x && arrayPosition.y == targetFinalPosition.y)
	{
		//reset the lists and the values!

		// clear the Astar pathlist 
		nav.pathList.clear();

		// clear the room pathlist
		roomPathList.clear();

		//reset the room target position
		roomTargetPosition = Vector2D(-1, -1);

		//reset the final target position (where it was clicked)
		targetFinalPosition = Vector2D(-1, -1);

		// also set the current target to the targetfinal position ?
		currentTarget = Vector2D(-1, -1);

		//reset the nextstep and the roomstep to -1 -1 so it cannot be used in a list and if it does it will bring  up and error.
		nextStep = -1;
		roomStep = -1;


		// reset pathset to false, because there is no path to be followed.
		pathSet = false;
		return;
	}

	//set current target to the target final position
	currentTarget = targetFinalPosition;



	// if the target room is a door ? 
	if (targetRoom != currentRoom && targetRoom >= 100)
	{
		//cout << "Trying to go" << endl;
		getRoomTarget();
		if (!roomPathList.empty())
		{
			currentTarget = roomTargetPosition;
		}
	}

	if (currentRoom < 199 && targetRoom != 0)
	{
		navigateDoor();
	}

	if (arrayPosition.x == currentTarget.x && arrayPosition.y == currentTarget.y)
	{
		// this is not supposed to happen
		return;
	}
	

	if (!pathSet && currentTarget.x != -1 && currentTarget.y != -1 && arrayPosition.x != targetFinalPosition.x && arrayPosition.y != targetFinalPosition.y)
	{
		
		cout << "\nSetting Up the Path\n";
			setUpPath();	
	}

	//cout << "\n Current Target: " << currentTarget << " Final target Position: " << targetFinalPosition << " Current Position: " << arrayPosition << endl;

	if (!nav.pathList.empty())
	{
		checkNextPosition();
		moveToTarget();
	}

	currentPosition.x = (arrayPosition.x * 10) + offsetX;
	currentPosition.y = (arrayPosition.y * 10) + offsetY;

	player.x = currentPosition.x;
	player.y = currentPosition.y;


}

void CharacterBehaviour::setUpPath()
{
	nav.search(arrayPosition.x, arrayPosition.y, currentTarget.x, currentTarget.y);

	nextStep = nav.pathList.size() -1;

	pathSet = true;
}

vector<Vector2D> CharacterBehaviour::getGraphPath()
{
	//room path list clear
	roomPathList.clear();

	//get the path from the levelknowledge.return path which looks for the path between the two rooms.
	vector<int> numberedPath = levelKnowledge.returnPath(currentRoom, targetRoom);

	// for each room in the numberedPath(the path from roomA to B)
	for (int o : numberedPath)
	{
		// find the poisiton of the rooms/ doors 
		for (int i = 0; i < levelKnowledge.roomsNDoorsList.size(); i++)
		{
			// the positions are stored in the rooms n doors list with an id ... ?
			if (levelKnowledge.roomsNDoorsList[i].iD == o)
			{
				roomPathList.push_back(levelKnowledge.roomsNDoorsList[i].position);
			}
		}
	}
	roomStep = roomPathList.size() - 1;

	return roomPathList;
}

