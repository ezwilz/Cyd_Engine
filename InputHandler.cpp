#include "InputHandler.h"

using namespace std;


float InputHandler :: getMouseX()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	return mouseX;
}

float InputHandler::getMouseY()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	return mouseY;
}

Vector2D InputHandler::getMousePosition()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	Vector2D pos;
	pos.x = mouseX;
	pos.y = mouseY;

	return pos;
}


SDL_Event InputHandler::GetInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		return event;
	}
	return event;
}

void InputHandler :: handleEvent(SDL_Event& event)
{
	leftMBDown = false;
	rightMBDown = false;
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			//cout << "\n\nLeft Clicked Through the Switch\n\nAt :" << getMousePosition().x  << " , " << getMousePosition().y;
			leftMBDown = true;
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
		{
			//cout << "\n\nRight Clicked Through the Switch\n\nAt :" << getMousePosition().x << " , " << getMousePosition().y;
			rightMBDown = true;
		}
		break;
	case SDL_QUIT:
		running = false;
		printf("Game Ended: Closing Window");
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			if (paused)
			{
				paused = false;
			}
			else
			{
				paused = true;
			}
		}
		if (event.key.keysym.sym == SDLK_d)
		{
			dPressed = true;
		}
		break;
	default:
		break;
	}
}