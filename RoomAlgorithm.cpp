#include "RoomAlgorithm.h"


void RoomAlgorithm::setUpPath()
{
	int cx = currentPosition->x;
	int cy = currentPosition->y;
	int ty = targetPosition->y;
	int tx = targetPosition->x;
	currentRoom = level.rooms[cy][cx];
	targetRoom = level.rooms[ty][tx];

	roomPathList = levelKnowledge->returnPath(currentRoom,targetRoom);
	pathSet = true;
	nextStep = roomPathList.size() - 1;
	nextRoom = roomPathList[nextStep];
	cout << "\nMilestone: PathList has been assigned, PathSet is true, NextStep has been set to size -1, and nextRoom is set.\n";
	convertTargetRoomToVector();
}

void RoomAlgorithm::clearPath()
{
	roomPathList.clear();
	pathSet = false;
	nextStep = -1;
	nextRoom = -1;
	targetToSend = Vector2D(-1, -1);
	cout << "\nMilestone: Path has been cleared, pathSet is false, nextStep is -1\n";
}

void RoomAlgorithm ::createNewDoor(int iD, Vector2D loco)
{
	Door newDoor;
	newDoor.id = iD;
	newDoor.location = loco;
	doors.push_back(newDoor);
}

void RoomAlgorithm::setNextTarget()
{
	if (currentRoom == nextRoom)
	{
		nextStep -= 1;
		if (nextStep == -1)
		{
			// destination has been reached
			cout << "\nMilestone: Reached the End of the Pathlist, Target Room Should be Reached.\n";
			clearPath();
		}
	}
}

void RoomAlgorithm::convertTargetRoomToVector()
{
	if (nextRoom > 199)
	{
		// Target Room is a room
		//Cycle through all surrounding tiles to find the right room.

		//IF AT A DOOR, CYCLE THROUGH ALL DIRECTIONS UNTIL THE TARGET ROOM IS FOUND! 
		int directionX[] = { -1, 1,  0, 0, -1, -1,  1,  1 };
		int directionY[] = { 0, 0, -1, 1, -1,  1, -1,  1 };

		for (int i = 0; i < 8; i++) {

			int newX = currentPosition->x + directionX[i];
			int newY = currentPosition->y + directionY[i];

			if (level.rooms[newY][newX] == nextRoom)
			{
				targetToSend = Vector2D(newX, newY);
				cout << "\nMilestone:  Found the next Room from the current door\n";
				break;
			}
			else
			{
				cout << "\nNot the Room Intended...\n";
			}
		}
	}
	else if (nextRoom < 199 && nextRoom > 99)
	{
		// Target Room is  a door
		for (Door d : doors)
		{
			if (d.id == nextRoom)
			{
				targetToSend = d.location;
				cout << "\nMilstone: Found the next Door, target to send has been set\n";
				break;
			}
		}
	}
	else
	{
		targetToSend = Vector2D(-1, -1);
	}

	


}