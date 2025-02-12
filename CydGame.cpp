#include "CydGame.h"

void CydGame::update()
{	
	//set the event -  only allows for one button to be pressed at a time ?? 
	eventSDL = inputHandler.GetInput();
	inputHandler.handleEvent(eventSDL);

	if (!isPaused)
	{
		handleMapControl();
		inputHandler.handleEvent(eventSDL);

		if (inputHandler.leftMBDown)
			leftClickAction();
		if (uiManager.button1Clicked)
		{
			button1Pressed();
		}
		//===============================================================================

		if (!cyd.levelKnowledge.CheckForVertexPresence(cyd.currentRoom))
		{
			cyd.levelKnowledge.CopyVertices(cyd.currentRoom, thisGraph.GetGraph());
			cout << "\nCopying the Vertice: " << cyd.currentRoom << endl;
		}

		cyd.offsetX = offsetX;
		cyd.offsetY = offsetY;
		cyd.update();


	}
	//update pause and running according to the input
	gameState();


	
	//cout << "\nTarget : " << cyd.targetPosition << " Current : " << cyd.arrayPosition << "\n";

	//===============================================================================
	//60 fps cap
	
	SDL_Delay(24);
}

void CydGame::button1Pressed()
{
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


	/*for (int i = 0; i < a_star.pathList.size(); i++)
	{
		cout << "Step " << i << ":" << a_star.pathList[i].position << "\n";
	}*/

	cout << "\n\n" << lClickArrayPosX << " , " << lClickArrayPosY;

	cout << "\n\Left Clicked Through the Switch\n\nAt :" << inputHandler.getMousePosition().x << " , " << inputHandler.getMousePosition().y;
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
	if (uiManager.isActive)
	{
		uiManager.renderUI(renderer, menuUIx, menuUIy);
	}
	
	SDL_SetRenderDrawColor(renderer, 240, 38, 131, 255);
	SDL_RenderFillRect(renderer, &cyd.player);
	SDL_RenderDrawRect(renderer, &cyd.player);
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
	loadLevel(level.house);
	cyd.offsetX = offsetX;
	cyd.offsetY = offsetY;
	createTheGraph();
}

void CydGame::createNewGameObject(string name, int x, int y, int w, int h)
{
	GameObject obj;
	obj.position.x = x;
	obj.position.y = y;
	obj.objectGraphic.w = w;
	obj.objectGraphic.h = h;
	activeObjects.push_back(obj);
}

void CydGame::loadLevel(int level[60][60])
{
	for (int i = 0; i < 60; ++i) {
		for (int j = 0; j < 60; ++j) {
			if (level[i][j] == 1)
			{
				SDL_Rect newRect = { j * 10,i * 10, 10,10 };
				levelRects.push_back(newRect);
			}
			if (level[i][j] == 4)
			{
				cyd.player = { j * 10,i * 10, 10,10 };
				cyd.arrayPosition.x = j;
				cyd.arrayPosition.y = i;
				cyd.currentPosition = Vector2D(j * 10, i * 10);
			}
		}
	}
}

void CydGame::moveMap(int x, int y, list<SDL_Rect>& rects)
{
	for (auto& element : rects)
	{
		element.x += x;
		element.y += y;
	}

	offsetX += x;
	offsetY += y;
	cyd.offsetX = offsetX;
	cyd.offsetY = offsetY;
	cyd.player.x += x;
	cyd.player.y += y;
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
			cyd.player = { tdX, tdY, 10,10 };

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
			moveMap(0, -10, levelRects);
		}

		// Move map down if mouse Y position is less than 40
		if (mouseY < 40) {
			moveMap(0, 10, levelRects);
		}

		// Move map left if mouse X position is less than 40
		if (mouseX < 40) {
			moveMap(10, 0, levelRects);
		}

		// Move map right if mouse X position is greater than 560
		if (mouseX > appWidth - 40) {
			moveMap(-10, 0, levelRects);
		}
	}
}

void CydGame::createTheGraph()
{
	//200's for rooms and 100's for doors
	thisGraph.addVertex(201);
	thisGraph.addVertex(202);
	thisGraph.addVertex(203);
	thisGraph.addVertex(204);
	thisGraph.addVertex(205);
	thisGraph.addVertex(206);
	thisGraph.addVertex(207);

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
	
}