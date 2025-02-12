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

using namespace std;
class CydGame
{
private:
	bool isPaused = false;
	bool isRunning;

	list<GameObject> activeObjects;
	list<SDL_Rect> levelRects;
	SDL_Rect rect1 = { 10,10,10,10 };
	LevelMap level;
	InputHandler inputHandler;
	UI uiManager;

	Astar a_star;

public:

	Graphs thisGraph;
	vector<Vector2D> vertexPositionsGod;

	int offsetX = 0;
	int offsetY = 0;

	Vector2D testDummyArrayPosition;

	CharacterBehaviour cyd;
	Vector2D lastClickedLocation;
	
	int menuUIx = 0;
	int menuUIy = 0;

	int lClickArrayPosX = -10;
	int lClickArrayPosY = -10;

	SDL_Event eventSDL;

	int appWidth = 800;
	int appHeight = 600;

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

	void loadLevel(int level[60][60]);
	void moveMap(int x, int y, list<SDL_Rect>& rects);
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

};