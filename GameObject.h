#pragma once
#include "Vector2D.h"
#include <SDL.h>
class GameObject
{
public:
	Vector2D position;
	SDL_Rect objectGraphic = { 10,10,10,10 };
	SDL_Texture* objectTexture;
	//string name;
	
	void update()
	{
		position.x++;
		objectGraphic.x = position.x;
		objectGraphic.y = position.y;

		
	}
	
};

