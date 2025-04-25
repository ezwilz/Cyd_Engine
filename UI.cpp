#include "UI.h"


bool UI::mouseHoveringButton(SDL_Rect* button)
{
	return collision.checkAABBCollision(inputHandler.getMouseX(), inputHandler.getMouseY(), 1, 1, button->x, button->y, button->w, button->h);
}

void UI::renderUI(SDL_Renderer* renderer, int x, int y)
{

	if (isActive)
	{
		// set the window and the button to the click x and y 
		window.x = x;
		window.y = y;

		button1.x = window.x + 5;
		button1.y = window.y + 5;

		SDL_SetRenderDrawColor(renderer, 95, 95, 95, 255);
		SDL_RenderFillRect(renderer, &window);
		SDL_RenderDrawRect(renderer, &window);
		if (mouseHoveringButton(&button1))
		{//red when hovering
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			if (inputHandler.GetInput().button.button == SDL_BUTTON_LEFT)
			{
				button1Clicked = true;
			}
			
		}
		else
		{//blue when not hovering 
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		}
		SDL_RenderFillRect(renderer, &button1);
		SDL_RenderDrawRect(renderer, &button1);
	}
}
