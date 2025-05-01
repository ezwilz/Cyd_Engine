#pragma once
#include "GameObject.h"
#include <vector>
class Room
{
private:

public:
	Room(int i);
	int id;
	vector<GameObject> containedObjects;
};

