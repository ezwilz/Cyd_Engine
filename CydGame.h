#pragma once
#include <string>
#include <list>
#include <SDL.h>
#include <iostream> 
#include <vector>

#include "GameObject.h"
#include "LevelMap.h"
#include "InputHandler.h"
#include "Graphs.h"
#include "UI.h"
#include "Astar.h"
#include "CharacterBehaviour.h"
#include "Room.h"

using namespace std;
class CydGame
{
private:
	bool isPaused = false;
	bool isRunning;

	list<SDL_Rect> levelRects;
	LevelMap level;
	UI uiManager;

	struct Door {
		int id = -1;
		Vector2D location = Vector2D(-1, -1);
	};
public:

	AabbCollision collisionChecker;
	InputHandler inputHandler;
	int appWidth = 800;
	int appHeight = 600;
	SDL_Rect currentTask = { appWidth - 60, appHeight - 60, 50,50 };

	CharacterBehaviour cyd;
	CharacterBehaviour murphy;

	int idTemplate = 500;
	vector<Room> rooms;
	vector<GameObject> objects;

	Graphs thisGraph;
	vector<Door> doors;

	SDL_Event eventSDL;

	int offsetX = 0;
	int offsetY = 0;

	Vector2D lastClickedLocation;
	int lClickArrayPosX = -10;
	int lClickArrayPosY = -10;
	
	int menuUIx = 0;
	int menuUIy = 0;
	//===
	void setPause(bool o) { isPaused = o; };
	bool getPause() { return isPaused; };

	int mouseX, mouseY;

	void setRunning(bool t) { isRunning = t; }
	bool getRunning() { return isRunning; }

	void start();
	void update();
	void render(SDL_Renderer* renderer);

	void createNewGameObject(string name, int x, int y, int w, int h);
	void updateActiveGameObjects();
	void loadLevel(int levelArray[60][60]);
	void moveMap(int x, int y, list<SDL_Rect>& rects, vector<GameObject>& obs);
	void scene1(SDL_Renderer* renderer);
	void pauseScreen(SDL_Renderer* renderer);
	void handleMapControl();
	void gameState();
	void leftClickAction();
	void button1Pressed();
	void moveTestDummy();
	Vector2D arrayToRenderPosition(int x, int y);
	Vector2D renderToArrayPosition(int x, int y);
	void createTheGraph();
	void locateAllDoors(int level[60][60]);


};