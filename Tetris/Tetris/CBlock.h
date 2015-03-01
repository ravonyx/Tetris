#ifndef CBLOCK_H
#define CBLOCK_H

#include "CSquare.h"

class CBlock
{
	private:
	    // Location of the center of the block 
	    int m_CenterX;
	    int m_CenterY;

	    // Type of block 
	    BlockType m_Type;

	    // Array of pointers to the squares that make up the block
	    CSquare* m_Squares[4];


	public:
		// The constructor just sets the block location and calls SetupSquares 
		CBlock(int x, int y, SDL_Surface* bitmap, BlockType type);         

		// Setup our block according to its location and type. Note that the squares 
		// are defined according to their distance from the block's center. This 
		// function takes a surface that gets passed to cSquare's constructor. 
		void SetupSquares(int x, int y, SDL_Surface* bitmap);

		// Draw() simply iterates through the squares and calls their Draw() functions.
		void Draw(SDL_Surface* Window);
		// Move() simply changes the block's center and calls the squares' move functions.
		void Move(Direction dir);
		void Rotate();

		// This function gets the locations of the squares after
		// a rotation and returns an array of those values. 
		int* GetRotatedSquares();
		CSquare** GetSquares();
};

#endif
