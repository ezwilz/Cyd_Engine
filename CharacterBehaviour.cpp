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
	cout << "\n7\n";
	// use the right list step/item according to how the character is navigating.
	//Check if the next position in the array is 0, it could have changed whilst the unit is moving.
	cout << "NextStep: " << nextStep << " ListSize: " << nav.pathList.size() - 1;
		int x = nav.pathList[nextStep]->position.x;
		int y = nav.pathList[nextStep]->position.y;
		cout << "\n8\n";

		if (level.house[y][x] != 0)
		{
			cout << "\n8\n";

			return false;
		}
		else
			return true;
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

	if (targetRoom == currentRoom)
	{
		graphPathSet = false;
		cout << "\nTargetRoom reached, path reset\n";
		
	}
	//cout << "\nTesting it gets this far! 1\n";
	if (targetPosition.x == -1)
	{
		targetRoom = -1;
	}
	//cout << "\nTesting it gets this far! 2\n";
	// if array position is the target position, reset all the values that could lead to irregular data next time around. 
	if (arrayPosition.x == targetPosition.x && arrayPosition.y == targetPosition.y)
	{
		//reset the lists and the values!
		targetRoom = -1;
		//doorTargetPosition = Vector2D(-1, -1);
		// clear the Astar pathlist 
		nav.pathList.clear();

		//reset the final target position (where it was clicked)
		targetPosition = Vector2D(-1, -1);

		// also set the current target to the targetfinal position ?
		currentTarget = Vector2D(-1, -1);

		//reset the nextstep and the roomstep to -1 -1 so it cannot be used in a list and if it does it will bring  up and error.
		nextStep = -1;


		cout << "\nDestination Met\n";
		//roomTargetFromDoor = Vector2D(-1, -1);

		// reset pathset to false, because there is no path to be followed.
		pathSet = false;
		return;
	}

	//cout << "\nTesting it gets this far! 3\n";

	//if the target is in the same room follow one process or else do the graph process !
	if (targetRoom == currentRoom)
	{
		cout << "\nTesting it gets this far! 4.1\n";
		sameRoomProcess();
	}
	else if (targetRoom != -1 && targetRoom != currentRoom)
	{
		//cout << "\nTesting it gets this far! 4.2\n";
		differentRoomProcess(graphOG);
	}

	//cout << "\nRoomPathReset: " << graphPathSet << " TargetRoom: " << targetRoom << " CurrentRoom: " << currentRoom << endl;
	
	//cout << "\nTesting it gets this far! 5\n";
	currentPosition.x = (arrayPosition.x * 10) + offsetX;
	currentPosition.y = (arrayPosition.y * 10) + offsetY;

	player.x = currentPosition.x;
	player.y = currentPosition.y;

	 for(int i = 0; i < roomPathList.size(); i ++)
		{
			cout << "Index: " << i << " - " << roomPathList[i] << " / ";
		}
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
		subTarget = Vector2D(-1, -1);
		graphPathSet = false;
		pathSet = false;
		targetRoom = -1;
		cout << "\n2\n";
		roomPathList.clear();
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
			//graphPathSet = false;
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
		///=====================================================
		cout << "\nA\n";

		cout << "\nRoom path is not empty\n"; 
		cout << "\Sub Tar Pos: " << subTarget << " Current Pos: " << arrayPosition  << " Target Pos: " << targetPosition << endl;


		for (int i = roomPathList.size() -1; i > -1; i--)
		{
			cout << i << " : " << roomPathList[i] << " Target Room: " << targetRoom << endl;;
		}
		cout << roomPathList.size();

		if (roomPathList[roomPathStep] < 199 && subTarget.x == -1)
		{
			cout << "\nB\n";
			cout << "\nRoom Target is a Door\n";
			for (const auto& e : doors)
			{
				cout << "\nC + " << targetRoom << " + " << roomPathList[roomPathStep] << "\n";
				
				if (e.id == roomPathList[roomPathStep])
				{
					cout << "\nD\n";
					cout << "\nSet the target position\n";
					subTarget = e.location;
					break;
				}
			}

			cout << "\nE\n";

			if (!pathSet && subTarget.x != -1 && subTarget.y != -1 && arrayPosition.x != subTarget.x && arrayPosition.y != subTarget.y)
			{
				cout << "\nF\n";
				cout << "\nSetting Up the ASTAR Path to a DOOR\n";
				setUpPath(subTarget);
			}
			cout << "\nG\n";
		} // check if character is in a door and if the target room is not a door!
		else if (currentRoom < 199 && roomPathList[roomPathStep] > 199)
		{
			//===========================================================
			cout << "\nH\n";
			cout << "\nRoom Target is a ROOM\n";
			if (!roomFound)
			{
				cout << "\nI\n";
				//IF AT A DOOR, CYCLE THROUGH ALL DIRECTIONS UNTIL THE TARGET ROOM IS FOUND! 
				int directionX[] = { -1, 1,  0, 0, -1, -1,  1,  1 };
				int directionY[] = { 0, 0, -1, 1, -1,  1, -1,  1 };

				for (int i = 0; i < 8; i++) {
					cout << "\nJ\n";
					cout << "\nSearching for the right ROOM\n";
					int newX = arrayPosition.x + directionX[i];
					int newY = arrayPosition.y + directionY[i];

					if (level.rooms[newY][newX] == roomPathList[roomPathStep])
					{
						cout << "\nK\n";
						subTarget = Vector2D(newX, newY);
						cout << "\nROOM FOUND\n";
						roomFound = true;
						break;
					}

				}

			}
			cout << "\nL\n";
			cout << pathSet;
			if (!pathSet && subTarget.x != -1 && 
				subTarget.y != -1 )
			{
				cout << "\nM\n";
				cout << "\nSetting Up the ASTAR Path to a ROOM\n";
				setUpPath(subTarget);
			}
		}
	}
	//cout << "\nN\n";
	if (!nav.pathList.empty())
	{
		
		if (roomPathStep == -1)
		{
			roomPathList.clear();
			//graphPathSet = false;
		}
		if (currentRoom == roomPathList[roomPathStep])
		{
			roomPathStep -= 1;
		}
		cout << "\nO\n";
		checkNextPosition();
		moveToTarget();
		if (arrayPosition == subTarget)
		{
			cout << "\nP\n";
			cout << "\nDestination Met\n";

			//Copy the vertex of the rooom or door the character just moved to
			int x = arrayPosition.x;
			int y = arrayPosition.y;
			levelKnowledge.CopyVertices(level.rooms[y][x], graphOG);
			//Reset the subTarget as we have reached it...
			subTarget = Vector2D(-1, -1);

			// Reset the graph path set to false so a new path can be rewritten
			graphPathSet = false;
			pathSet = false;
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