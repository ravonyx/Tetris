#include <stack>
#include "SDL.h"
#include "Defines.h"
#include "States.h"
#include "Global.h"
#include "Collisions.h"

void HandleMenuInput()
{
	if(SDL_PollEvent(&g_Event))
	{
		//handle user closing game
		if(g_Event.type == SDL_QUIT)
		{
			// if stack isnt empty
			while(!g_StateStack.empty())
			{
				g_StateStack.pop();
			}
			return;
		}
		// handle keyboard input
		if(g_Event.type == SDL_KEYDOWN)
		{
			if(g_Event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_StateStack.pop();
			}

			if(g_Event.key.keysym.sym == SDLK_q)
			{
				g_StateStack.pop();
			}

			if(g_Event.key.keysym.sym == SDLK_g)
			{
				StateStruct temp;
				temp.StatePointer = Game;
				g_StateStack.push(temp);
				return;
			}
		}
		
	}
}

void HandleGameInput()
{
	// These variables allow the user to hold the arrow keys down 
	static bool down_pressed = false;
	static bool left_pressed = false;
	static bool right_pressed = false;
	if(SDL_PollEvent(&g_Event))
	{
		//handle user closing game
		if(g_Event.type == SDL_QUIT)
		{
			// if stack isnt empty
			while(!g_StateStack.empty())
			{
				g_StateStack.pop();
			}
			return;
		}
		// handle keyboard input
		if(g_Event.type == SDL_KEYDOWN)
		{
			if(g_Event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_StateStack.pop();
			}
		}

		if (g_Event.key.keysym.sym == SDLK_UP)
		{
		// Check collisions before rotating 
			if (!CheckRotationCollisions(g_FocusBlock))
			{
			    g_FocusBlock->Rotate();
			}
		}

		// For the left, right, and down arrow keys, we just set a bool variable 
		if (g_Event.key.keysym.sym == SDLK_LEFT)
		{
			left_pressed = true;
		}

		if (g_Event.key.keysym.sym == SDLK_RIGHT)
		{
			right_pressed = true;
		}

		if (g_Event.key.keysym.sym == SDLK_DOWN)
		{
			down_pressed = true;
		}
		
	}
	// If player lifts key, set bool variable to false 
        if (g_Event.type == SDL_KEYUP)
        {
		if (g_Event.key.keysym.sym == SDLK_LEFT)
		{
			left_pressed = false;
		}
		if (g_Event.key.keysym.sym == SDLK_RIGHT)
		{
			right_pressed = false;
		}
		if (g_Event.key.keysym.sym == SDLK_DOWN)
		{
			down_pressed = false;
		}
        }

	if (down_pressed)
	{
		if ( !CheckWallCollisions(g_FocusBlock, DOWN) && !CheckEntityCollisions(g_FocusBlock, DOWN) )
		{
		   	 g_FocusBlock->Move(DOWN);
		}
	}
	if (left_pressed)
	{
		if ( !CheckWallCollisions(g_FocusBlock, LEFT) && !CheckEntityCollisions(g_FocusBlock, LEFT) )
		{
			g_FocusBlock->Move(LEFT);
		}
	}
	if (right_pressed)
	{
		if ( !CheckWallCollisions(g_FocusBlock, RIGHT) && !CheckEntityCollisions(g_FocusBlock, RIGHT) )
		{
			g_FocusBlock->Move(RIGHT);
		}
	}
}

void HandleExitInput()
{
	if(SDL_PollEvent(&g_Event))
	{
		//handle user closing game
		if(g_Event.type == SDL_QUIT)
		{
			// if stack isnt empty
			while(!g_StateStack.empty())
			{
				g_StateStack.pop();
			}
			return;
		}
		// handle keyboard input
		if(g_Event.type == SDL_KEYDOWN)
		{
			if(g_Event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_StateStack.pop();
			}
			
			if(g_Event.key.keysym.sym == SDLK_y)
			{
				g_StateStack.pop();
			}

			if(g_Event.key.keysym.sym == SDLK_n)
			{
				StateStruct temp;
				temp.StatePointer = Game;
				g_StateStack.push(temp);
				return;
			}
		}
		
	}
}

// Input handling for win/lose screens.
void HandleWinLoseInput()
{
    if ( SDL_PollEvent(&g_Event) )
    {
        // Handle user manually closing game window 
        if (g_Event.type == SDL_QUIT)
        { 
            // While state stack isn't empty, pop 
            while (!g_StateStack.empty())
            {
                g_StateStack.pop();
            }

            return; 
        }

        // Handle keyboard input here
        if (g_Event.type == SDL_KEYDOWN)
        {
            if (g_Event.key.keysym.sym == SDLK_ESCAPE)
            {
                g_StateStack.pop();

                return; 
            }
            if (g_Event.key.keysym.sym == SDLK_y)
            {
                g_StateStack.pop();
                return; 
            }
            // If player chooses to continue playing, we pop off 
            // current state and push exit and menu states back on. 
            if (g_Event.key.keysym.sym == SDLK_n)
            {
                g_StateStack.pop();

                StateStruct temp;
                temp.StatePointer = Exit;
                g_StateStack.push(temp);

                temp.StatePointer = Menu;
                g_StateStack.push(temp);
                return; 
            }
        }
    }
}
