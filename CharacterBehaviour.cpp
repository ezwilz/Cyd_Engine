#include "CharacterBehaviour.h"


void CharacterBehaviour::passive()
{
	food -= 0.5 * foodMultiplier;
	bladder -= 0.5 * bladderMultiplier;
	hygeine -= 0.5 * hygeineMultiplier;
	sleep -= 0.5 * sleepMultiplier;
	fun -= 0.5 * funMultiplier;
	fun1 -= 0.5 * funMultiplier;
	fun2 -= 0.5 * funMultiplier;

	if (food < 0)
		food = 0;
	else if (food > maxNeedBar)
		food = maxNeedBar;

	if (bladder < 0)
		bladder = 0;
	else if (bladder > maxNeedBar)
		bladder = maxNeedBar;

	if (hygeine < 0)
		hygeine = 0;
	else if (hygeine > maxNeedBar)
		hygeine = maxNeedBar;

	if (sleep < 0)
		sleep = 0;
	else if (sleep > maxNeedBar)
		sleep = maxNeedBar;

	if (fun < 0)
		fun = 0;
	else if (fun > maxNeedBar)
		fun = maxNeedBar;

	if (fun1 < 0)
		fun1 = 0;
	else if (fun1 > maxNeedBar)
		fun1 = maxNeedBar;

	if (fun2 < 0)
		fun2 = 0;
	else if (fun2 > maxNeedBar)
		fun2 = maxNeedBar;

	//cout << "Fun1 " << fun1 << " Fun2 " << fun2;
		 
}

void CharacterBehaviour::update(map<int, vector<int>> graphOG, vector<Room>* rList)
{
	//NEEDS
	passive();
	handleNeedBars();
	checkNeeds();
	pathFinding(graphOG, rList);
	handleTasks();

	currentPosition.x = (arrayPosition.x * 10) + offsetX;
	currentPosition.y = (arrayPosition.y * 10) + offsetY;

	sprite.x = currentPosition.x;
	sprite.y = currentPosition.y;
}
//PathFinding related functions
bool CharacterBehaviour::checkNextPosition()
{
	//cout << "\n7\n";
	// use the right list step/item according to how the character is navigating.
	//Check if the next position in the array is 0, it could have changed whilst the unit is moving.
	//cout << "NextStep: " << nextStep << " ListSize: " << nav.pathList.size() - 1;
		checkForTarget();
		//cout << "\nFart1 \n" << nextStep << nav.pathList.size();
		if (nextStep != -1)
		{
			int x = nav.pathList[nextStep]->position.x;
			int y = nav.pathList[nextStep]->position.y;
			//cout << "\n8\n";
			//cout << "\nFart2\n";

			if (level.house[y][x] != 0)
			{
				//cout << "\n8\n";
				//cout << "\nFart3\n";

				return false;
			}
			else
				//cout << "\nFart4\n";

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
void CharacterBehaviour::setUpPath(Vector2D tar)
{
	nav.search(arrayPosition.x, arrayPosition.y, tar.x, tar.y);

	nextStep = nav.pathList.size() -1;

	pathSet = true;
}
void CharacterBehaviour::sameRoomProcess() {
	//set current target to the target final position
	currentTarget = targetPosition;
	//cout << "\n1\n";
	// if AT the target
	if (arrayPosition.x == currentTarget.x && arrayPosition.y == currentTarget.y)
	{
		cout << "\nDestination Met\n";
		pathSet = false;
		targetRoom = -1;
		//subTarget = Vector2D(-1, -1);
		//graphPathSet = false;
		//cout << "\n2\n";
		//roomPathList.clear();
		// this is not supposed to happen
		return;
	}

	//cout << "\n3\n";
	if (!pathSet && currentTarget.x != -1 && currentTarget.y != -1 && arrayPosition.x != targetPosition.x && arrayPosition.y != targetPosition.y)
	{
		//cout << "\n4\n";
		cout << "\nSetting Up the Path\n";
		setUpPath(targetPosition);
	}
	//cout << "\n5\n";

	//cout << "\n Current Target: " << currentTarget << " Final target Position: " << targetFinalPosition << " Current Position: " << arrayPosition << endl;

	if (!nav.pathList.empty())
	{
		//cout << "\n6\n";
		checkNextPosition();
		//cout << "\n7\n";
		moveToTarget();
		//cout << "\n8\n";

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
void CharacterBehaviour::pathFinding(map<int, vector<int>> graphOG, vector<Room>* rList)
{
	// SET THE CURRENT ROOMS AND TARGET ROOM
	// set the current room
	int xA = arrayPosition.x;
	int yA = arrayPosition.y;
	currentRoom = level.rooms[yA][xA];
	int xB = targetPosition.x;
	int yB = targetPosition.y;
	targetRoom = level.rooms[yB][xB];


	if (knownRooms.size() != rList->size())
	{
		for (auto& e : *rList)
		{
			bool roomInList = false;
			//Look for the current Room
			if (e.id == currentRoom)
			{
				//look through the unit knownRooms
				for (auto e1 : knownRooms)
				{
					//If the id is also the currentRoom
					if (e1.id == currentRoom)
					{
						roomInList = true;
						break;
					}
				}
				if (!roomInList)
				{
					knownRooms.push_back(e);
					break;
				}
					
			}
		}
	}
	
	if (levelKnowledge.m_graph[currentRoom].size() != graphOG[currentRoom].size())
	{
		levelKnowledge.CopyVertices(currentRoom, graphOG);
		
	}
	

	//cout << "\nTesting it gets this far! 1\n";
	if (targetPosition.x == -1)
		targetRoom = -1;

	if (nav.pathFindingCancelled)
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
		roomAlg.clearPath();
		roomAlg.nextStep = -1;
		//roomAlg.clearPath();
		cout << "\nDestination Met\n";
		nav.pathFindingCancelled = false;
		cout << "\nPathFinding Cancelled - t to f ";
		// reset pathset to false, because there is no path to be followed.
		pathSet = false;
		int x = arrayPosition.x;
		int y = arrayPosition.y;

		level.house[y][x] = 0;
		arrayPosition.y -= 1;
		level.house[y -1][x] = 4;
		//targetPosition = taskList.front().usePoint;
		return;
	}

	//if the target is in the same room follow one process or else do the graph process !
	if (targetRoom == currentRoom)
		sameRoomProcess();
	else if (targetRoom != -1 && targetRoom != currentRoom)
	{
		if (levelKnowledge.CheckForVertexPresence(targetRoom))
			differentRoomProcess(graphOG);
		else
		{
			cout << "\nRoom Unknown\n";
			targetPosition = Vector2D(-1, -1);
		}
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
	/*if (nav.searchStuck)
	{
		targetPosition = arrayPosition;
		nav.searchStuck = false;
		nav.searchLoop = 0;
	}*/
	//cout << "\nSendTo: " << roomAlg.targetToSend << " Actual: " << targetPosition << " TargetRoom: " << targetRoom << " CurrentRoom: " << currentRoom << endl;
}
// Decision making related functions. 
void CharacterBehaviour::handleNeedBars()
{

	//set all the bars to the relative value of the need so its representative... if its too low, then just show as 5 !

	if (food < 10)
		foodBar.w = 5;
	else
		foodBar.w = food / 10;

	if (sleep < 10)
		sleepBar.w = 5;
	else
		sleepBar.w = sleep / 10;

	if (hygeine < 10)
		hygeineBar.w = 5;
	else
		hygeineBar.w = hygeine / 10;

	if (bladder < 10)
		bladderBar.w = 5;
	else
		bladderBar.w = bladder / 10;

	if (fun < 10)
		funBar.w = 5;
	else
		funBar.w = fun / 10;
}
void CharacterBehaviour::renderNeedBars(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 207, 206, 203, 255);
	SDL_RenderFillRect(renderer, &foodBar);
	SDL_RenderDrawRect(renderer, &foodBar);

	SDL_SetRenderDrawColor(renderer, 143, 63, 24, 255);
	SDL_RenderFillRect(renderer, &bladderBar);
	SDL_RenderDrawRect(renderer, &bladderBar);

	SDL_SetRenderDrawColor(renderer, 62, 137, 224, 255);
	SDL_RenderFillRect(renderer, &hygeineBar);
	SDL_RenderDrawRect(renderer, &hygeineBar);

	SDL_SetRenderDrawColor(renderer, 133, 29, 29, 255);
	SDL_RenderFillRect(renderer, &sleepBar);
	SDL_RenderDrawRect(renderer, &sleepBar);

	SDL_SetRenderDrawColor(renderer, 255, 153, 0, 255);
	SDL_RenderFillRect(renderer, &funBar);
	SDL_RenderDrawRect(renderer, &funBar);
}

void CharacterBehaviour::checkNeeds()
{
	if (food < (maxNeedBar * 0.25))
	{
		getFoodTask();
	}
	if (hygeine < (maxNeedBar * 0.25))
	{
		getHygieneTask();
	}
	if (bladder < (maxNeedBar * 0.25))
	{
		getBladderTask();
	}
	if (sleep < (maxNeedBar * 0.25))
	{
		getSleepTask();
	}
	if (fun < 750)
	{
		if (sleep > (maxNeedBar * 0.25) && bladder > (maxNeedBar * 0.25) && hygeine > (maxNeedBar * 0.25) && food > (maxNeedBar * 0.25))
		{
			getFunTask();
		}
	}
	
}
void CharacterBehaviour::getFoodTask()
{
	if (!foodQueued)
	{
		//cout << "\nLooking for a fridge\n";
		for (auto& i : knownRooms)
		{
			//cout << "A";
			for (auto& e : i.containedObjects)
			{
				//cout << "B";
				if (e.getType() == 10)
				{
					//cout << "C";
					Task t = Task(e);
					taskList.push(t);
					foodQueued = true;
					break;
				}
			}
		}
	}
}
void CharacterBehaviour::getBladderTask()
{
	if (!bladderQueued)
	{
		//cout << "\nLooking for a toilet\n";
		for (auto& i : knownRooms)
		{
			for (auto& e : i.containedObjects)
			{
				if (e.getType() == 40)
				{
					Task t = Task(e);
					taskList.push(t);
					bladderQueued = true;
					break;
				}
			}
		}
	}
	

}
void CharacterBehaviour::getHygieneTask()
{

	if (!hygieneQueued)
	{
		//cout << "\nLooking for a shower3\n";

		for (auto& i : knownRooms)
		{
			//cout << "\nLooking for a toilet4\n";

			for (auto& e : i.containedObjects)
			{
				//cout << "\nLooking for a toilet5\n";

				if (e.getType() == 30)
				{
					//cout << "\FOUND a toilet\n";

					Task t = Task(e);
					taskList.push(t);
					hygieneQueued = true;
					break;
				}
			}
		}
	}
}
void CharacterBehaviour::getSleepTask()
{
	if (!sleepQueued)
	{
		//cout << "\nLooking for a sleep\n";

		for (auto& i : knownRooms)
		{
			for (auto& e : i.containedObjects)
			{
				if (e.getType() == 20)
				{
					Task t = Task(e);
					taskList.push(t);
					sleepQueued = true;
					break;
				}
			}
		}
	}
}
void CharacterBehaviour::getFunTask()
{
	if (!funQueued)
	{
		//cout << "\nLooking for a sleep\n";
		if (fun1 > fun2)
		{
			for (auto& i : knownRooms)
			{
				for (auto& e : i.containedObjects)
				{
					if (e.getType() == 50)
					{
						Task t = Task(e);
						taskList.push(t);
						funQueued = true;
						fun1 += 173;
						break;
					}
				}
			}
		}
		else
		{
			for (auto& i : knownRooms)
			{
				for (auto& e : i.containedObjects)
				{
					if (e.getType() == 60)
					{
						Task t = Task(e);
						taskList.push(t);
						funQueued = true;
						fun2 += 179.2;
						break;
					}
				}
			}
		}
	}
}
void CharacterBehaviour::handleTasks()
{
	if (!taskList.empty())
	{
		//cout << "\nTaskList is not empty\n";
		// there are tasks available
		if (!taskList.front().isCompleted)
		{
			if(!taskList.front().isTaskSet())
			{
				targetPosition = taskList.front().usePoint;
				taskList.front().setTaskSet(true);
				cout << "\nSet Target Position and task set to true\n";
			}
			else
			{
				if (arrayPosition.x == taskList.front().usePoint.x && arrayPosition.y == taskList.front().usePoint.y)
				{
					if (!taskList.front().taskStarted)
					{
						taskList.front().setStartTime();
						cout << "\nStart time Set\n";
					}
					else
					{
						if (taskList.front().targetObject.affectsBladder)
							bladderMultiplier = taskList.front().targetObject.bladderModifier;
						if (taskList.front().targetObject.affectsHunger)
							foodMultiplier = taskList.front().targetObject.hungerModifier;
						if (taskList.front().targetObject.affectsHygiene)
							hygeineMultiplier = taskList.front().targetObject.hygieneModifer;
						if (taskList.front().targetObject.affectsSleep)
							sleepMultiplier = taskList.front().targetObject.sleepModifier;
						if (taskList.front().targetObject.affectsFun)
							funMultiplier = taskList.front().targetObject.funModifier;


						taskList.front().checkIfComplete();
					}
				}
				else
				{
					if (!(arrayPosition.x == taskList.front().usePoint.x && arrayPosition.y == taskList.front().usePoint.y) && targetPosition.x == -1)
					{
						foodMultiplier = 1.77;
						bladderMultiplier = 1.60;
						sleepMultiplier = 1;
						hygeineMultiplier = 1.10;
						funMultiplier = 1.90;

						taskList.front().resetStartTime();
						targetPosition = taskList.front().usePoint;
					}
				}
			}
		}
		else
		{
			cout << "\nTask Completed\n";
			foodMultiplier = 1.77;
			bladderMultiplier = 1.60;
			sleepMultiplier = 1;
			hygeineMultiplier = 1.10;
			funMultiplier = 1.90;

			switch (taskList.front().targetObject.getType())
			{
			case 10:
				foodQueued = false;
				break;
			case 20:
				sleepQueued = false;
				break;
			case 30:
				hygieneQueued = false;
				break;
			case 40:
				bladderQueued = false;
				break;
			case 50:
				funQueued = false;
				break;
			case 60:
				funQueued = false;
			}
			taskList.pop();
			
		}
		
	}
	else
	{

	}

	//cout << food << " - " << foodMultiplier << " - " << foodBar.w <<  endl;
}
void CharacterBehaviour::queueTask(GameObject object)
{
	//EMPTY THE QUEUE AND PRIORITISE THE TASK MANUALLY SET
	for (int i = 0; i < taskList.size(); i++)
	{
		if (!taskList.empty())
		{
			taskList.pop();
		}
	}
	hygieneQueued = false;
	sleepQueued = false;
	foodQueued = false;
	bladderQueued = false;
	funQueued = false;
	Task t = Task(object);
	switch (object.getType())
	{
		case 10: foodQueued = true; break;
		case 20: sleepQueued = true; break;
		case 30: hygieneQueued = true; break;
		case 40: bladderQueued = true; break;
		case 50: funQueued = true; break;
		case 60: funQueued = true; break;
	}
	taskList.push(t);
}
