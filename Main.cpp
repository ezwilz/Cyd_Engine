#include <SDL.h>
#include <iostream>
#include "CydGame.h"



CydGame* game = new CydGame;

void gameLoop(SDL_Renderer* renderer)
{
    game->start();
    // Main event loop
    game->setRunning(true);
    SDL_Event event;
    while (game->getRunning()) {
        /*while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game->setRunning(false);
                printf("Game Ended: Closing Window");
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    if (game->getPause())
                    {
                        game->setPause(false);
                    }
                    else
                    {
                        game->setPause(true);
                    }
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                cout << "\n\nClicked Main \n\n";
            }
        }*/

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        game->update();

        game->render(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(17);
    }

}

int runGame()
{
    // Create an SDL window
    SDL_Window* gameWindow = SDL_CreateWindow("SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        game->appWidth, game->appHeight,            // Width and height
        SDL_WINDOW_SHOWN);   // Display window flag


    if (gameWindow == nullptr) {
        std::cerr << "Failure to Create window, SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);

    if (nullptr == renderer) {
        std::cout << "Failure to create renderer, SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    gameLoop(renderer);

    // Clean up and quit SDL
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();
}


int main(int argc, char* argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    runGame();
   
    delete game;

    // Shutdown SDL
    SDL_Quit();

	return 0;

}