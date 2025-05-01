#include "CydGame.h"

void CydGame::update()
{	
	/*for (auto& e : rooms)
	{
		cout << endl << e.id << " Objects Contained: " << e.containedObjects.size();
	}*/
	//set the event -  only allows for one button to be pressed at a time ?? 
	
	/*eventSDL = inputHandler.GetInput();
	
	inputHandler.handleEvent(eventSDL);*/

	//inputHandler.pollEvent(&eventSDL);

	gameState();
	if (!isPaused)
	{
		handleMapControl();
		inputHandler.handleEvent(eventSDL);

		if (inputHandler.leftMBDown)
		{
			if (level.house[lClickArrayPosY][lClickArrayPosX] == 0)
			{
				if (lClickArrayPosX < 60 && lClickArrayPosX > 0 && lClickArrayPosY < 60 && lClickArrayPosY > 0)
				{
					murphy.targetPosition = Vector2D(lClickArrayPosX, lClickArrayPosY);
					murphy.pathSet = false;

					cout << "Setting murphys target\n";
				}
			}
		}
		if (uiManager.button1Clicked)
		{
			button1Pressed();
		}

		if (inputHandler.rightMBDown)
		{

			for (auto e : cyd.knownRooms)
			{
				cout << "\n" << e.id;
				for (auto e1 : e.containedObjects)
				{
					cout << " " << e1.getName();
				}
				cout << endl;
			}
			cout << cyd.currentRoom;

			lClickArrayPosX = (inputHandler.getMousePosition().x - offsetX) / 10;
			lClickArrayPosY = (inputHandler.getMousePosition().y - offsetY) / 10;

			if (level.house[lClickArrayPosY][lClickArrayPosX] == 0)
			{
				if (lClickArrayPosX < 60 && lClickArrayPosX > 0 && lClickArrayPosY < 60 && lClickArrayPosY > 0)
				{
					cyd.targetPosition = Vector2D(lClickArrayPosX, lClickArrayPosY);
					cyd.pathSet = false;
				}
			}
			else if (level.house[lClickArrayPosY][lClickArrayPosX] > 9 && level.house[lClickArrayPosY][lClickArrayPosX] < 61)
			{
				for (auto& e : cyd.knownRooms)
				{
					if (level.rooms[lClickArrayPosY][lClickArrayPosX] == e.id)
					{
						for (auto& o : e.containedObjects)
						{
							if (o.getLocation().x == lClickArrayPosX && o.getLocation().y == lClickArrayPosY)
							{
								cyd.queueTask(o);
							}
						}
					}
				}
			}

			cout << "Current: " << cyd.currentRoom << " Target: " << cyd.targetRoom << endl;
		}
		//===============================================================================
		cyd.offsetX = offsetX;
		cyd.offsetY = offsetY;

		murphy.offsetX = offsetX;
		murphy.offsetY = offsetY;

		cyd.update(thisGraph.GetGraph(),&rooms);
		murphy.update(thisGraph.GetGraph(),&rooms);
	}

	if (collisionChecker.checkAABBCollision(currentTask.x, currentTask.y, currentTask.w, currentTask.h, inputHandler.getMouseX(), inputHandler.getMouseY(), 5, 5))
	{
		if (!cyd.taskList.empty())
		{
			switch (cyd.taskList.front().targetObject.getType())
			{
			case 10:
				cyd.foodQueued = false;
				break;
			case 20:
				cyd.sleepQueued = false;
				break;
			case 30:
				cyd.hygieneQueued = false;
				break;
			case 40:
				cyd.bladderQueued = false;
				break;
			case 50:
				cyd.funQueued = false;
				break;
			case 60:
				cyd.funQueued = false;
				break;
			}

			cyd.foodMultiplier = 1.77;
			cyd.bladderMultiplier = 1.60;
			cyd.sleepMultiplier = 1;
			cyd.hygeineMultiplier = 1.10;
			cyd.funMultiplier = 1.90;
			
			cyd.taskList.pop();
		}
	}
	//update pause and running according to the input
	
	//===============================================================================
	//60 fps cap
	
	SDL_Delay(24);
}

void CydGame::button1Pressed()
{
	//cout << lClickArrayPosX << " , " << lClickArrayPosY << endl;
	if (level.house[lClickArrayPosY][lClickArrayPosX] == 0)
	{
		if (lClickArrayPosX < 60 && lClickArrayPosX > 0 && lClickArrayPosY < 60 && lClickArrayPosY > 0)
		{
			cyd.targetPosition = Vector2D(lClickArrayPosX, lClickArrayPosY);
			cyd.pathSet = false;
		}
	}
	cout << "\n\nButtonClicked\n\n";
	uiManager.button1Clicked = false;
	uiManager.isActive = false;

	//cout << " Test Dummy Location: " << testDummyArrayPosition << "\n" << "Left Click Position: (" << lClickArrayPosX << " , " << lClickArrayPosY << ")\n";
}

void CydGame::leftClickAction()
{
	if (uiManager.isActive)
		uiManager.isActive = false;
	else
		uiManager.isActive = true;

	menuUIx = inputHandler.getMousePosition().x;
	menuUIy = inputHandler.getMousePosition().y;

	lClickArrayPosX = (inputHandler.getMousePosition().x - offsetX) / 10;
	lClickArrayPosY = (inputHandler.getMousePosition().y - offsetY) / 10;

	//cout << "\Cyd Graph: ";
	//cyd.levelKnowledge.printGraph();
	//cout << "\nThis Graph: ";
	//thisGraph.printGraph();

	/*for (int i = 0; i < a_star.pathList.size(); i++)
	{
		cout << "Step " << i << ":" << a_star.pathList[i].position << "\n";
	}*/

	//cout << "\n\n" << lClickArrayPosX << " , " << lClickArrayPosY;

	//cout << "\n\Left Clicked Through the Switch\n\nAt :" << inputHandler.getMousePosition().x << " , " << inputHandler.getMousePosition().y;
	inputHandler.leftMBDown = false;
}

void CydGame::gameState()
{
	isPaused = inputHandler.paused;
	isRunning = inputHandler.running;
}

void CydGame::render(SDL_Renderer* renderer)
{
	if (!isPaused)
	{
		scene1(renderer);		
		/*if (!a_star.pathList.empty())
		{
			Vector2D x;

			for (const auto& node : a_star.pathList)
			{
				x = arrayToRenderPosition(node->position.x, node->position.y);
				SDL_Rect newRect = { x.x,x.y,10,10 };
				SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
				SDL_RenderFillRect(renderer, &newRect);
				SDL_RenderDrawRect(renderer, &newRect);

			}
		}*/

	}
	else
	{
		pauseScreen(renderer);
	}
	
}

void CydGame::scene1(SDL_Renderer* renderer)
{
	for (auto& element : levelRects)
	{
		SDL_SetRenderDrawColor(renderer, 124, 154, 255, 255);
		SDL_RenderFillRect(renderer, &element);
		SDL_RenderDrawRect(renderer, &element);

	}
	for (auto& element : objects)
	{
		if (element.getType() == 10)
		{
			// fridge colour
			SDL_SetRenderDrawColor(renderer, 207, 206, 203, 255);
		}
		if (element.getType() == 20)
		{
			//bed colour
			SDL_SetRenderDrawColor(renderer, 133, 29, 29, 255);
		}
		if (element.getType() == 30)
		{
			//shower colour
			SDL_SetRenderDrawColor(renderer, 62, 137, 224, 255);
		}
		if (element.getType() == 40)
		{
			//toilet colour
			SDL_SetRenderDrawColor(renderer, 143, 63, 24, 255);
		}
		if (element.getType() == 50)
		{
			//fun1 colour
			SDL_SetRenderDrawColor(renderer, 255, 153, 0, 255);
		}
		if (element.getType() == 60)
		{
			//fun2 colour
			SDL_SetRenderDrawColor(renderer, 255, 153, 0, 255);
		}
		SDL_RenderFillRect(renderer, &element.rect);
		SDL_RenderDrawRect(renderer, &element.rect);

	}
	if (uiManager.isActive)
	{
		uiManager.renderUI(renderer, menuUIx, menuUIy);
	}
	if (!cyd.taskList.empty())
	{
		switch (cyd.taskList.front().targetObject.getType())
		{
		case 10:
			// fridge colour
			SDL_SetRenderDrawColor(renderer, 207, 206, 203, 255);
			break;
		case 20:
			//bed colour
			SDL_SetRenderDrawColor(renderer, 133, 29, 29, 255);
			break;
		case 30:
			//shower colour
			SDL_SetRenderDrawColor(renderer, 62, 137, 224, 255);
			break;
		case 40:
			//toilet colour
			SDL_SetRenderDrawColor(renderer, 143, 63, 24, 255);
			break;
		case 50:
			//toilet colour
			SDL_SetRenderDrawColor(renderer, 255, 153, 0, 255);
			break;
		case 60:
			//toilet colour
			SDL_SetRenderDrawColor(renderer, 255, 153, 0, 255);
			break;
		default:
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			break;
		}
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	}
	SDL_RenderFillRect(renderer, &currentTask);
	SDL_RenderDrawRect(renderer, &currentTask);

	cyd.renderNeedBars(renderer);

	SDL_SetRenderDrawColor(renderer, 240, 38, 131, 255);
	SDL_RenderFillRect(renderer, &cyd.sprite);
	SDL_RenderDrawRect(renderer, &cyd.sprite);

	SDL_SetRenderDrawColor(renderer, 240, 38, 131, 255);
	SDL_RenderFillRect(renderer, &murphy.sprite);
	SDL_RenderDrawRect(renderer, &murphy.sprite);
}

void CydGame::pauseScreen(SDL_Renderer* renderer)
{
	SDL_Rect pausedSqaure = { 0,0,50,50 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &pausedSqaure);
	SDL_RenderDrawRect(renderer, &pausedSqaure);
}

void CydGame::updateActiveGameObjects()
{
	
}

void CydGame::start()
{
	uiManager.inputHandler = &inputHandler;
	createTheGraph();
	loadLevel(level.house);
	cyd.offsetX = offsetX;
	cyd.offsetY = offsetY;
	murphy.offsetX = offsetX;
	murphy.offsetY = offsetY;
	locateAllDoors(level.rooms);
	cyd.roomAlg.levelKnowledge = &cyd.levelKnowledge;
	cyd.roomAlg.currentPosition = &cyd.arrayPosition;
	cyd.roomAlg.targetPosition = &cyd.targetPosition;

	murphy.roomAlg.levelKnowledge = &murphy.levelKnowledge;
	murphy.roomAlg.currentPosition = &murphy.arrayPosition;
	murphy.roomAlg.targetPosition = &murphy.targetPosition;


	for (auto e : rooms)
	{
		if (e.id == 201)
		{
			cyd.knownRooms.push_back(e);
		}
		/*if (e.id == 202)
		{
			murphy.knownRooms.push_back(e);
		}*/
		cout << "\n" << e.id;
		for (auto e1 : e.containedObjects)
		{
			cout << " " << e1.getName();
		}
		cout << endl;
	}
	

	//murphy.levelKnowledge.m_graph = thisGraph.m_graph;
	murphy.knownRooms = rooms;

	for (auto e : murphy.knownRooms)
	{
		cout << "\n Murphy's List: " << e.id;
		for (auto e1 : e.containedObjects)
		{
			cout << " " << e1.getName();
		}
		cout << endl;
	}
}

void CydGame::createNewGameObject(string name, int x, int y, int w, int h)
{
	
}

void CydGame::loadLevel(int levelArray[60][60])
{
	for (int i = 0; i < 60; ++i) {
		for (int j = 0; j < 60; ++j) {
			if (levelArray[i][j] == 1)
			{
				SDL_Rect newRect = { j * 10,i * 10, 10,10 };
				levelRects.push_back(newRect);
			}
			if (levelArray[i][j] == 4)
			{
				cyd.sprite = { j * 10,i * 10, 10,10 };
				cyd.arrayPosition.x = j;
				cyd.arrayPosition.y = i;
				cyd.currentPosition = Vector2D(j * 10, i * 10);
			}
			if(levelArray[i][j] == 7)
			{
				murphy.sprite = { j * 10,i * 10, 10,10 };
				murphy.arrayPosition.x = j;
				murphy.arrayPosition.y = i;
				murphy.currentPosition = Vector2D(j * 10, i * 10);
			}
			if (levelArray[i][j] > 9)
			{
				idTemplate += 1;
				GameObject obj = GameObject(idTemplate, levelArray[i][j], Vector2D(j, i));
				obj.rect.x = j * 10;
				obj.rect.y = i * 10;
				objects.push_back(obj);

				for (auto& element : rooms)
				{
					if (element.id == level.rooms[i][j])
					{
						element.containedObjects.push_back(obj);
						break;
					}
				}
			}
		}
	}
}

void CydGame::locateAllDoors(int level[60][60])
{
	for (int i = 0; i < 60; ++i) {
		for (int j = 0; j < 60; ++j) {
			if (level[i][j] > 100 && level[i][j] < 200)
			{
				cyd.roomAlg.createNewDoor(level[i][j], Vector2D(j, i));
				murphy.roomAlg.createNewDoor(level[i][j], Vector2D(j, i));
			}
		}
	}
}

void CydGame::moveMap(int x, int y, list<SDL_Rect>& rects, vector<GameObject>& obs)
{
	for (auto& element : rects)
	{
		element.x += x;
		element.y += y;
	}
	for (auto& element : obs)
	{
		element.rect.x += x;
		element.rect.y += y;
	}
	offsetX += x;
	offsetY += y;
	cyd.offsetX = offsetX;
	cyd.offsetY = offsetY;
	cyd.sprite.x += x;
	cyd.sprite.y += y;


	murphy.offsetX = offsetX;
	murphy.offsetY = offsetY;
	murphy.sprite.x += x;
	murphy.sprite.y += y;
}

void CydGame::moveTestDummy()
{
	/*if (inputHandler.dPressed)
	{
		int oldy = testDummyArrayPosition.y;
		int oldx = testDummyArrayPosition.x;

		int newx = oldx + 1;
		int newy = oldy;
		if (level.house[newy][newx] == 0)
		{
			level.house[oldy][oldx] = 0;
			level.house[newy][newx] = 4;

			int tdX = (newx * 10) + offsetX;
			int tdY = (newy * 10) + offsetY;
			cyd.sprite = { tdX, tdY, 10,10 };

			testDummyArrayPosition.x = newx;
			testDummyArrayPosition.y = newy;
		}
	
		inputHandler.dPressed = false;

	}*/
}

Vector2D CydGame::arrayToRenderPosition(int x, int y)
{
	int newX = (x * 10) + offsetX;
	int newY = (y * 10) + offsetY;

	return Vector2D(newX,newY);
}

Vector2D CydGame::renderToArrayPosition(int x, int y)
{
	int newX = (x - offsetX) / 10;
	int newY = (y - offsetY) /10;

	return Vector2D(newX, newY);
}

void CydGame::handleMapControl()
{
	int mouseX = inputHandler.getMouseX();
	int mouseY = inputHandler.getMouseY();

	// Check if the mouse is within the bounds of the window
	if (mouseX > 0 && mouseX < appWidth && mouseY > 0 && mouseY < appHeight) {

		// Move map up if mouse Y position is greater than 360
		if (mouseY > appHeight - 40) {
			moveMap(0, -10, levelRects, objects);
		}

		// Move map down if mouse Y position is less than 40
		if (mouseY < 40) {
			moveMap(0, 10, levelRects, objects);
		}

		// Move map left if mouse X position is less than 40
		if (mouseX < 40) {
			moveMap(10, 0, levelRects, objects);
		}

		// Move map right if mouse X position is greater than 560
		if (mouseX > appWidth - 40) {
			moveMap(-10, 0, levelRects, objects);
		}
	}
}

void CydGame::createTheGraph()
{
	//200's for rooms and 100's for doors
	thisGraph.addVertex(201);
	Room r1 = Room(201);
	rooms.push_back(r1);

	thisGraph.addVertex(202);
	Room r2 = Room(202);
	rooms.push_back(r2);

	thisGraph.addVertex(203);
	Room r3 = Room(203);
	rooms.push_back(r3);

	thisGraph.addVertex(204);
	Room r4 = Room(204);
	rooms.push_back(r4);

	thisGraph.addVertex(205);
	Room r5 = Room(205);
	rooms.push_back(r5);

	thisGraph.addVertex(206);
	Room r6 = Room(206);
	rooms.push_back(r6);

	thisGraph.addVertex(207);
	Room r7 = Room(207);
	rooms.push_back(r7);

	//doors
	thisGraph.addVertex(101);
	thisGraph.addVertex(102);
	thisGraph.addVertex(103);
	thisGraph.addVertex(104);
	thisGraph.addVertex(105);
	thisGraph.addVertex(106);
	thisGraph.addVertex(107);
	thisGraph.addVertex(108);
	thisGraph.addVertex(109);

	thisGraph.addEdge(201, 101);
	thisGraph.addEdge(201, 102);
	thisGraph.addEdge(201, 104);
	thisGraph.addEdge(201, 105);
	thisGraph.addEdge(201, 106);
	thisGraph.addEdge(201, 107);

	thisGraph.addEdge(202, 105);

	thisGraph.addEdge(203, 102);
	thisGraph.addEdge(203, 103);

	thisGraph.addEdge(204, 101);
	thisGraph.addEdge(204, 109);

	thisGraph.addEdge(205, 109);

	thisGraph.addEdge(206, 104);
	thisGraph.addEdge(206, 108);

	thisGraph.addEdge(207, 107);
	thisGraph.addEdge(207, 108);


	cyd.levelKnowledge.addVertex(201);
	cyd.levelKnowledge.CopyVertices(201, thisGraph.GetGraph());
	cyd.levelKnowledge.createANewSpace(201, cyd.arrayPosition);

	murphy.levelKnowledge.addVertex(202);
	murphy.levelKnowledge.CopyVertices(202, thisGraph.GetGraph());
	murphy.levelKnowledge.createANewSpace(202, murphy.arrayPosition);

	murphy.levelKnowledge.CopyVertices(201, thisGraph.m_graph);
	murphy.levelKnowledge.CopyVertices(203, thisGraph.m_graph);
	murphy.levelKnowledge.CopyVertices(204, thisGraph.m_graph);
	murphy.levelKnowledge.CopyVertices(205, thisGraph.m_graph);
	murphy.levelKnowledge.CopyVertices(206, thisGraph.m_graph);
	murphy.levelKnowledge.CopyVertices(207, thisGraph.m_graph);

	

	
}