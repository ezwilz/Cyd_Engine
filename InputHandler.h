#pragma once
#include <iostream>
#include "Vector2D.h"
#include<SDL.h>
class InputHandler
{
public:

	bool leftMBDown = false;
	bool rightMBDown = false;
	bool paused = false;
	bool running = true;

	bool dPressed = false;

	float  getMouseX();
	float getMouseY();
	Vector2D getMousePosition();
	SDL_Event GetInput();
	void handleEvent(SDL_Event& event);

	void pollEvent(SDL_Event* event);



};

