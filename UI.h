#pragma once
#pragma once
#include "Vector2D.h"
#include "InputHandler.h"
#include "AabbCollision.h"
#include <SDL.h>

using namespace std;
class UI
{
public:

	AabbCollision collision;
	InputHandler inputHandler;

	SDL_Rect window = {0,0,80,40};
	SDL_Rect button1 = { 0,0,70,30 };

	bool button1Clicked = false;
	bool isActive = false;

	bool mouseHoveringButton(SDL_Rect* button);
	void renderUI(SDL_Renderer *renderer, int x, int y);
	//void setDimensions();
};

