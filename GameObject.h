#pragma once
using namespace std;
#include "Vector2D.h"
#include <SDL.h>
#include "string.h"
class GameObject
{
private:

	//Uniquie ID for targeting this specific object
	int id = -1;
	// type refers to 1 = fridge 2 = bed etc. 
	int type = -1;
	// duration refers to the time it takes to complete this objects action in seconds
	int duration = -1;
	// for text renderings in game !
	string name = " ";
	Vector2D location = Vector2D(-1, -1);

public:

	GameObject(int i,int t,  Vector2D l);

	SDL_Rect rect = { 10,10,10,10 };

	bool affectsHunger, affectsBladder, affectsSleep, affectsHygiene = false;

	int hungerModifier, sleepModifier, bladderModifier, hygieneModifer = 0;

	void setType(int t);
	void setName(string n);
	void setLocation(Vector2D l);
	void setDuration(int d);
	void setId(int i);

	int getType();
	string getName();
	Vector2D getLocation();
	int getDuration();
	int getId();
};

