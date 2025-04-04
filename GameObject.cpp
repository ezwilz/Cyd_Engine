#include "GameObject.h"



//Constructor
GameObject::GameObject(int i, int t, Vector2D l)
{
	id = i;
	type = t;
	location = l;

	switch (type)
	{
	case 10:
		cout << "\nFridge Spawned.\n";

		setName("Fridge");

		affectsHunger = true;
		affectsBladder = true;

		hungerModifier = -5;
		bladderModifier = 2;

		duration = 2500;

		break;
	case 20:
		cout << "\nBed Spawned\n";

		setName("Bed");

		affectsSleep = true;

		duration = 10000;
		
		sleepModifier = -5;
		break;
	case 30:
		cout << "\nShower Spawned\n";

		setName("Shower");

		affectsHygiene = true;

		duration = 5000;

		hygieneModifer = -5;
		break;
	case 40:
		cout << "\nToilet Spawned\n";

		setName("Toilet");

		duration = 2500;

		affectsBladder = true;

		bladderModifier = -5;
		break;
	default:
		break;
	}


}
//SETTERS
void GameObject:: setType(int t)
{
	type = t;
}
void GameObject::setStat(int s)
{
	stat = s;
}
void GameObject::setName(string n)
{
	name = n;
}
void GameObject::setLocation(Vector2D l)
{
	location = l;
}
void GameObject::setDuration(int d)
{
	duration = d;
}
void GameObject::setId(int i)
{
	id = i;
}
// GETTERS
int GameObject::getType()
{
	return type;
}
int GameObject::getStat()
{
	return stat;
}
string GameObject::getName()
{
	return name;
}
Vector2D GameObject::getLocation()
{
	return location;
}
int GameObject::getDuration()
{
	return duration;
}
int GameObject::getId()
{
	return id;
}

