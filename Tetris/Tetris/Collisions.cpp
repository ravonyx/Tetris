#include "Check.h"
#include "CSquare.h"
#include "CBlock.h"
#include "Global.h"

void HandleBottomCollision()
{ 
    ChangeFocusBlock();

    // Check for completed lines and store the number of lines completed 
    int num_lines = CheckCompletedLines();

    if ( num_lines > 0 )
    {
        // Increase player's score according to number of lines completed 
        g_Score += POINTS_PER_LINE * num_lines;

        // Check to see if it's time for a new level 
        if (g_Score >= g_Level * POINTS_PER_LEVEL)
        {
            g_Level++;
            CheckWin(); // check for a win after increasing the level 
            g_FocusBlockSpeed -= SPEED_CHANGE; // shorten the focus blocks movement interval
        }
    }

    // Now would be a good time to check to see if the player has lost 
    CheckLoss();
}

bool CheckEntityCollisions(CSquare* square, Direction dir) 
{ 
	// Width/height of a square. Also the distance 
	// between two squares if they've collided. 
	int distance = SQUARE_MEDIAN * 2;

	// Center of the given square 
	int centerX = square->GetCenterX(); 
	int centerY = square->GetCenterY();

	// Determine the location of the square after moving
	switch (dir)
	{
		case DOWN:
		{ 
			centerY += distance;
		} break;

		case LEFT:
		{
			centerX -= distance;
		} break;

		case RIGHT:
		{
			centerX += distance;
		} break;
	}

	// Iterate through the old squares vector, checking for collisions
	for (int i=0; i<g_OldSquares.size(); i++)
	{
		if ( ( abs(centerX - g_OldSquares[i]->GetCenterX() ) < distance ) &&( abs(centerY - g_OldSquares[i]->GetCenterY() ) < distance ) )
		{
			return true;
		}
	}

	return false;
}

bool CheckEntityCollisions(CBlock* block, Direction dir) 
{ 
	// Get an array of the squares that make up the given block 
	CSquare** temp_array = block->GetSquares();

	// Now just call the other CheckEntityCollisions() on each square 
	for (int i=0; i<4; i++)
	{
		if ( CheckEntityCollisions(temp_array[i], dir) )
	    		return true;
	}

	return false;
}

bool CheckWallCollisions(CSquare* square, Direction dir) 
{
	// Get the center of the square
	int x = square->GetCenterX();
	int y = square->GetCenterY();

	// Get the location of the square after moving and see if its out of bounds 
	switch (dir)
	{
		case DOWN:
		{
		    if ( (y + (SQUARE_MEDIAN*2)) > GAME_AREA_BOTTOM )
		    {
			return true;
		    }
		    else
		    {
			return false;
		    }
		} break;

		case LEFT:
		{
		    if ( (x - (SQUARE_MEDIAN*2)) < GAME_AREA_LEFT )
		    {
			return true;
		    }
		    else
		    {
			return false;
		    }
		} break;

		case RIGHT:
		{
		    if ( (x + (SQUARE_MEDIAN*2)) > GAME_AREA_RIGHT )
		    {
			return true;
		    }
		    else
		    {
			return false;
		    }
		} break;
	}

	return false;
}

bool CheckWallCollisions(CBlock* block, Direction dir) 
{
	// Get an array of squares that make up the given block
	CSquare** temp_array = block->GetSquares();

	// Call other CheckWallCollisions() on each square 
	for (int i=0; i<4; i++)
	{
		if ( CheckWallCollisions(temp_array[i], dir) )
			return true;
	}

	return false;
}

bool CheckRotationCollisions(CBlock* block) 
{
	// Get an array of values for the locations of the rotated block's squares
	int* temp_array = block->GetRotatedSquares();

	// Distance between two touching squares 
	int distance = SQUARE_MEDIAN * 2;

	for (int i=0; i<4; i++)
	{
	// Check to see if the block will go out of bounds 
		if ( (temp_array[i*2] < GAME_AREA_LEFT) ||
		     (temp_array[i*2] > GAME_AREA_RIGHT) )
		{
		    delete temp_array;
		    return true;
		}

		if ( temp_array[i*2+1] > GAME_AREA_BOTTOM )
		{
		    delete temp_array;
		    return true;
		}

		// Check to see if the block will collide with any squares 
		for (int index=0; index<g_OldSquares.size(); index++)
		{
		    if ( ( abs(temp_array[i*2] - g_OldSquares[index]->GetCenterX()) < distance ) && 
			( abs(temp_array[i*2+1] - g_OldSquares[index]->GetCenterY()) < distance ) )
		    {
			delete temp_array;
			return true;
		    }
		}
	}

	delete temp_array;
	return false;
}


