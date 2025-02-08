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
		if (inputHandler.dPressed)
			moveTestDummy();
	}
	/*if (inputHandler.rightMBDown)
		cout << "\n\nRight Clicked Through the Switch\n\nAt :" << inputHandler.getMousePosition().x << " , " << inputHandler.getMousePosition().y;*/
	if (inputHandler.leftMBDown)
		leftClickAction();
	//update pause and running according to the input
	gameState();
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


	if(level.house[lClickArrayPosY][lClickArrayPosX] == 0)
		if(lClickArrayPosX < 60 && lClickArrayPosX > 0 && lClickArrayPosY < 60 && lClickArrayPosY > 0)
			a_star.search(testDummyArrayPosition.x, testDummyArrayPosition.y, lClickArrayPosX, lClickArrayPosY);
	

	cout << " Test Dummy Location: " << testDummyArrayPosition << "\n" << "Left Click Position: (" << lClickArrayPosX << " , " << lClickArrayPosY << ")\n";

	/*for (int i = 0; i < a_star.pathList.size(); i++)
	{
		cout << "Step " << i << ":" << a_star.pathList[i].position << "\n";
	}*/

	cout << "\n\n" << lClickArrayPosX << " , " << lClickArrayPosY;

	cout << "\n\Left Clicked Through the Switch\n\nAt :" << inputHandler.getMousePosition().x << " , " << inputHandler.getMousePosition().y;
}

void CydGame::gameState()
{
	isPaused = inputHandler.paused;
	isRunning = inputHandler.running;
}

void CydGame::render(SDL_Renderer* renderer)
{
	/*SDL_Rect rect = character1.objectGraphic;
	SDL_SetRenderDrawColor(renderer, 124, 154, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawRect(renderer, &rect);*/
	if (!isPaused)
	{
		
		scene1(renderer);
		/*if (!a_star.closedList.empty())
		{
			Vector2D x;

			for (const auto& node : a_star.closedList)
			{
				x = arrayToRenderPosition(node.position.x, node.position.y);
				SDL_Rect newRect = { x.x,x.y,10,10 };
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderFillRect(renderer, &newRect);
				SDL_RenderDrawRect(renderer, &newRect);

			}
		}*/
		
		if (!a_star.pathList.empty())
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
		}


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
	SDL_RenderFillRect(renderer, &testDummy);
	SDL_RenderDrawRect(renderer, &testDummy);
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
	character1.update();
}

void CydGame::start()
{
	loadLevel(level.house);
	character1.objectGraphic.w = 60;
	character1.objectGraphic.h = 60;
	character1.position.y = 60;
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
				testDummy = { j * 10,i * 10, 10,10 };
				//levelRects.push_back(testDummy);
				testDummyArrayPosition.x = j;
				testDummyArrayPosition.y = i;
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

	testDummy.x += x;
	testDummy.y += y;
}

void CydGame::moveTestDummy()
{
	if (inputHandler.dPressed)
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
			testDummy = { tdX, tdY, 10,10 };

			testDummyArrayPosition.x = newx;
			testDummyArrayPosition.y = newy;
		}
	
		inputHandler.dPressed = false;

	}
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