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
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			leftMBDown = true;
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
		{
			rightMBDown = true;
		}
		break;

	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			leftMBDown = false;
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
		{
			rightMBDown = false;
		}
		break;

	case SDL_QUIT:
		running = false;
		printf("Game Ended: Closing Window\n");
		break;

	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			paused = !paused;
			std::cout << (paused ? "PAUSED\n" : "UnPAUSED\n");
		}
		if (event.key.keysym.sym == SDLK_d)
		{
			dPressed = true;
		}
		break;

	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_d)
		{
			dPressed = false;
		}
		break;

	default:
		break;
	}
}

void InputHandler::pollEvent(SDL_Event* event)
{
	while (SDL_PollEvent(event))
	{
		handleEvent(*event);
	}
}