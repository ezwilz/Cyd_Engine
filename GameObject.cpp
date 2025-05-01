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

		affectsSleep = false;
		affectsHygiene = false;

		hungerModifier = -30;
		bladderModifier = 3;

		duration = 2500;

		break;
	case 20:
		cout << "\nBed Spawned\n";

		setName("Bed");

		affectsSleep = true;

		affectsHunger = false;
		affectsBladder = false;
		affectsHygiene = false;



		duration = 5000;
		
		sleepModifier = -20;
		break;
	case 30:
		cout << "\nShower Spawned\n";

		setName("Shower");

		affectsHygiene = true;

		affectsHunger = false;
		affectsBladder = false;
		affectsSleep = false;

		duration = 2000;

		hygieneModifer = -40;
		break;
	case 40:
		cout << "\nToilet Spawned\n";

		setName("Toilet");

		duration = 1000;

		affectsBladder = true;

		affectsHunger = false;
		affectsSleep = false;
		affectsHygiene = false;

		bladderModifier = -90;
		break;
	case 50: 
		cout << "\nFun Object Type 1 Spawned\n";

		setName("Fun Object Type 1");

		duration = 1000;

		funModifier = -90;
		affectsFun = true;

		affectsBladder = false;
		affectsHunger = false;
		affectsSleep = false;
		affectsHygiene = false;

		break;
	case 60:
		cout << "\nFun Object Type 2 Spawned\n";

		setName("Fun Object Type 2");

		duration = 1000;

		funModifier = -90;
		affectsFun = true;

		affectsBladder = false;
		affectsHunger = false;
		affectsSleep = false;
		affectsHygiene = false;

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

