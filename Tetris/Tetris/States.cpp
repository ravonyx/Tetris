#include <stack>
#include <string>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_ttf.h"

#include "States.h"
#include "Defines.h"
#include "Input.h"
#include "Render.h"
#include "Global.h"
#include "Collisions.h"
#include <iostream>

static int force_down_counter = 0;
static int slide_counter = SLIDE_TIME;

void Init()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		std::cerr << "SDL_Init() Failed: " << SDL_GetError() << std::endl;
		exit(1);
	}

	g_Window = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16, SDL_ANYFORMAT);
	if (g_Window == NULL)
	{
		std::cerr << "SDL_SetVideoMode() Failed: " << SDL_GetError() << std::endl;
		exit(1);
	}

	SDL_WM_SetCaption(WINDOW_CAPTION,0);
	g_Timer = SDL_GetTicks();
	g_Bitmap = SDL_LoadBMP("data/bg.jpg");

	// Initialize blocks and set them to their proper locations. 
	g_FocusBlock = new CBlock( BLOCK_START_X, BLOCK_START_Y, g_Bitmap,
	    (BlockType)(rand()%7) );
	g_NextBlock  = new CBlock( NEXT_BLOCK_CIRCLE_X, NEXT_BLOCK_CIRCLE_Y, 
	    g_Bitmap, (BlockType)(rand()%7) );

	StateStruct state;
	state.StatePointer = Exit;
	g_StateStack.push(state);

	state.StatePointer = Menu;
	g_StateStack.push(state);

	if (TTF_Init() != 0)
	{
		std::cerr << "TTF_Init() Failed: " << TTF_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	// Load a font
	TTF_Font *font;
	font = TTF_OpenFont("arial.ttf", 24);
	if (font == NULL)
	{
		std::cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << std::endl;
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}
}

void ShutDown()
{
	CSquare** temp_array_1 = g_FocusBlock->GetSquares();
	CSquare** temp_array_2 = g_NextBlock->GetSquares();

	// Delete our blocks 
	delete g_FocusBlock;
	delete g_NextBlock;

	// Delete the temporary arrays of squares 
	for (unsigned int i=0; i<4; i++)
	{
	    delete temp_array_1[i];
	    delete temp_array_2[i];
	}	
	
	for (unsigned int i=0; i<g_OldSquares.size(); i++)
	{
	    delete g_OldSquares[i];
	}

	TTF_Quit();

	SDL_FreeSurface(g_Bitmap);
	SDL_FreeSurface(g_Window);
	
	SDL_Quit();
}

void Menu()
{
	if((SDL_GetTicks() - g_Timer) >= FRAME_RATE)
	{
		HandleMenuInput();
		ClearScreen();
		/*DisplayText("Start (G)ame", 120, 120, 12, 255, 255, 255, 0, 0, 0);
		DisplayText("(Q)uit Game", 120, 150, 12, 255, 255, 255, 0, 0, 0);*/
		
		SDL_UpdateRect(g_Window, 0, 0, 0, 0);
		g_Timer = SDL_GetTicks();
	}
}

void Game()
{
	if((SDL_GetTicks() - g_Timer) >= FRAME_RATE)
	{
		printf("Game");
		HandleGameInput();
		force_down_counter++;

		/* (force_down_counter >= g_FocusBlockSpeed)
		{
		    // Always check for collisions before moving anything 
		    if ( !CheckWallCollisions(g_FocusBlock, DOWN) &&
			 !CheckEntityCollisions(g_FocusBlock, DOWN) )
		    {
			g_FocusBlock->Move(DOWN); // move the focus block
			force_down_counter = 0; // reset our counter
		    }
		}
		// Check to see if focus block's bottom has hit something.
		// If it has, we decrement our counter. 
		if ( CheckWallCollisions(g_FocusBlock, DOWN) ||
		     CheckEntityCollisions(g_FocusBlock, DOWN) )
		{
		    slide_counter--;
		}
		// If there isn't a collision, we reset our counter. 
		// This is in case the player moves out of a collision. 
		else 
		{
		    slide_counter = SLIDE_TIME;
		}
		// If the counter hits zero, we reset it and call our 
		// function that handles changing the focus block. 
		if (slide_counter == 0)
		{
		    slide_counter = SLIDE_TIME;
		    HandleBottomCollision();
		}*/
		ClearScreen();

		DrawBackground();
		// Draw the focus block and next block.
		g_FocusBlock->Draw(g_Window);
		g_NextBlock->Draw(g_Window);

		// Draw the old squares.
		for (unsigned int i=0; i < g_OldSquares.size(); i++)
		{
		    g_OldSquares[i]->Draw(g_Window);
		}

		// This will be passed to itoa() 
		char temp[256];

		std::string score = "Score: ";
		sprintf_s(temp,"%d",g_Score);
		//itoa(g_Score, temp, 10); // the 10 just tells itoa to use decimal notation
		score.append( temp );

		std::string nextscore = "Needed Score: ";
		sprintf_s(temp,"%d",g_Level*POINTS_PER_LEVEL);
		nextscore.append(temp);

		std::string level = "Level: ";
		sprintf_s(temp,"%d",g_Level);
		level.append(temp);
			
		
		
		DisplayText(score, SCORE_RECT_X, SCORE_RECT_Y, 8, 0, 0, 0, 255, 255, 255);
		DisplayText(nextscore, NEEDED_SCORE_RECT_X, NEEDED_SCORE_RECT_Y, 8, 0, 0, 0, 255, 255, 255);
		DisplayText(level, LEVEL_RECT_X, LEVEL_RECT_Y, 8, 0, 0, 0, 255, 255, 255);

		SDL_UpdateRect(g_Window, 0, 0, 0, 0);
		g_Timer = SDL_GetTicks();
	}
}

void GameWon()
{
	if ( (SDL_GetTicks() - g_Timer) >= FRAME_RATE )
	{
		HandleWinLoseInput();

		ClearScreen();

		DisplayText("You Win!!!", 100, 120, 12, 255, 255, 255, 0, 0, 0);
		DisplayText("Quit Game (Y or N)?", 100, 140, 12, 255, 255, 255, 0, 0, 0);

		SDL_UpdateRect(g_Window, 0, 0, 0, 0);

		g_Timer = SDL_GetTicks();
	} 
}

void GameLost()
{ 
	if ( (SDL_GetTicks() - g_Timer) >= FRAME_RATE )
	{
		HandleWinLoseInput();

		ClearScreen();

		DisplayText("You Lose.", 100, 120, 12, 255, 255, 255, 0, 0, 0);
		DisplayText("Quit Game (Y or N)?", 100, 140, 12, 255, 255, 255, 0, 0, 0);

		SDL_UpdateRect(g_Window, 0, 0, 0, 0);

		g_Timer = SDL_GetTicks();
	} 
}

void Exit()
{
	if((SDL_GetTicks() - g_Timer) >= FRAME_RATE)
	{
		HandleExitInput();
		ClearScreen();
		
		DisplayText("Quit Game (Y or N)?", 100, 150, 12, 255, 255, 255, 0, 0, 0);

		SDL_UpdateRect(g_Window, 0, 0, 0, 0);
		g_Timer = SDL_GetTicks();
	}
}


