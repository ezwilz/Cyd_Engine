#pragma once
class CharacterBehaviour
{
private:
	//Needs
	float food = 1000;
	float bladder = 1000;
	float sleep = 1000;
	float hygeine = 1000;

public:
	float foodMultiplier = 1;
	float bladderMultiplier = 1;
	float sleepMultiplier = 1;
	float hygeineMultiplier = 1;

	void passive();
};

