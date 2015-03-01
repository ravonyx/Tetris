#include <stack>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Defines.h"
#include <string>
#include "Global.h"

void DrawBackground() 
{
   	 SDL_Rect source;

    	// Set our source rectangle to the current level's background 
	switch (g_Level)
	{
		case 1:
		{
		    SDL_Rect temp = { LEVEL_ONE_X, LEVEL_ONE_Y, WINDOW_WIDTH, 
			WINDOW_HEIGHT };
		    source = temp;
		} break; 
		case 2:
		{
		    SDL_Rect temp = { LEVEL_TWO_X, LEVEL_TWO_Y, WINDOW_WIDTH, 
			WINDOW_HEIGHT };
		    source = temp;
		} break;
		case 3:
		{
		    SDL_Rect temp = { LEVEL_THREE_X, LEVEL_THREE_Y, WINDOW_WIDTH,
			WINDOW_HEIGHT };
		    source = temp;
		} break;
		case 4:
		{
		    SDL_Rect temp = { LEVEL_FOUR_X, LEVEL_FOUR_Y, WINDOW_WIDTH, 
			WINDOW_HEIGHT };
		    source = temp;
		} break;
		case 5:
		{
		    SDL_Rect temp = { LEVEL_FIVE_X, LEVEL_FIVE_Y, WINDOW_WIDTH, 
			WINDOW_HEIGHT };
		    source = temp;
		} break;
	}

	 SDL_Rect destination = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
   	 SDL_BlitSurface(g_Bitmap, &source, g_Window, &destination);
}

void ClearScreen()
{
	SDL_FillRect(g_Window, 0, 0);
}

void DisplayText(const std::string& text, unsigned char x, unsigned char y, unsigned char size, unsigned char fR, unsigned char fG, unsigned char fB, unsigned char bR, unsigned char bG, unsigned char bB)
{
	TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", size);
	
	SDL_Color foreground;
	foreground.r = fR;
	foreground.g = fG;
	foreground.b = fB;
	SDL_Color background;
	background.r = bR;
	background.g = bG;
	background.b = bB;
	
	SDL_Surface* temp = TTF_RenderText_Shaded(font, text.c_str(), foreground, background);
	SDL_Rect destination = {x, y, 0, 0};
	SDL_BlitSurface(temp, NULL, g_Window, &destination);

	SDL_FreeSurface(temp);
	TTF_CloseFont(font);
}
