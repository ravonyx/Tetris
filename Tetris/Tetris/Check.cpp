#include "Defines.h"
#include "Global.h"
#include "States.h"
#include "Enums.h"
#include "Collisions.h"

int CheckCompletedLines()
{
    // Store the amount of squares in each row in an array
    int squares_per_row[13];

    // The compiler will fill the array with junk values if we don't do this 
    for (int index=0; index<13; index++)
        squares_per_row[index] = 0;

    int row_size = SQUARE_MEDIAN * 2; // pixel size of one row
    int bottom = GAME_AREA_BOTTOM - SQUARE_MEDIAN; // center of bottom row
    int top = bottom - (12 * row_size); // center of top row

    int num_lines = 0; // number of lines cleared 
    int row; // multipurpose variable

    // Check for full lines 
    for (int i=0; i<g_OldSquares.size(); i++)
    {
        // Get the row the current square is in 
        row = (g_OldSquares[i]->GetCenterY() - top) / row_size;

        // Increment the appropriate row counter
        squares_per_row[row]++; 
    }

    // Erase any full lines
    for (int line=0; line<13; line++)
    {
        // Check for completed lines 
        if (squares_per_row[line] == SQUARES_PER_ROW)
        {
            // Keep track of how many lines have been completed 
            num_lines++;

            // Find any squares in current row and remove them 
            for (int index=0; index<g_OldSquares.size(); index++)
            {
                if ( ( (g_OldSquares[index]->GetCenterY() - top) / row_size ) == line )
                {
                    // delete the square
                    delete g_OldSquares[index]; 
                    // remove it from the vector
                    g_OldSquares.erase(g_OldSquares.begin() + index);

                    // When we delete a square, the next square in the vector takes 
                    // its place. We have to be sure to stay at the current index so 
                    // we don't skip any squares. For example, if we delete the first 
                    // square, the second square now becomes the first. We have to 
                    // stay at the current (first) index so we can check the second 
                    // square (now the first). 
                    index--; 
                }
            }
        }
    }

    // Move squares above cleared line down
    for (int index=0; index<g_OldSquares.size(); index++)
    {
        for (int line=0; line<13; line++)
        {
            // Determine if this row was filled 
            if (squares_per_row[line] == SQUARES_PER_ROW)
            {
                // If it was, get the location of it within the game area
                row = (g_OldSquares[index]->GetCenterY() - top) / row_size;

                // Now move any squares above that row down one 
                if ( row < line )
                {
                    g_OldSquares[index]->Move(DOWN);
                }
            }
        }
    }

    return num_lines;
}

void ChangeFocusBlock()
{
    // Get an array of pointers to the focus block squares
    CSquare** square_array = g_FocusBlock->GetSquares();

    // Add focus block squares to g_OldSquares 
    for (int i=0; i<4; i++)
    {
        g_OldSquares.push_back(square_array[i]);
    }

    delete g_FocusBlock; // delete the current focus block
    g_FocusBlock = g_NextBlock; // set the focus block to the next block
    g_FocusBlock->SetupSquares(BLOCK_START_X, BLOCK_START_Y, g_Bitmap);

    // Set the next block to a new block of random type 
    g_NextBlock = new CBlock(NEXT_BLOCK_CIRCLE_X, NEXT_BLOCK_CIRCLE_Y, 
                             g_Bitmap, (BlockType)(rand()%7));
}

void CheckWin() 
{
    // If current level is greater than number of levels, player has won 
    if (g_Level > NUM_LEVELS)
    {
        // Pop all states 
        while (!g_StateStack.empty())
        {
            g_StateStack.pop();
        }

        // Push the victory state onto the stack 
        StateStruct win;
        win.StatePointer = GameWon;

        g_StateStack.push(win);
    }
}

void CheckLoss() 
{
    // We call this function when the focus block is at the top of that 
    // game area. If the focus block is stuck now, the game is over. 
    if ( CheckEntityCollisions(g_FocusBlock, DOWN))
    {
        // Clear the old squares vector 
        for (int i=0; i<g_OldSquares.size(); i++)
        {
            delete g_OldSquares[i];
        }
        g_OldSquares.clear();

        // Pop all states 
        while (!g_StateStack.empty())
        {
            g_StateStack.pop();
        }

        // Push the losing state onto the stack 
        StateStruct lose;
        lose.StatePointer = GameLost;

        g_StateStack.push(lose);
    }
}
