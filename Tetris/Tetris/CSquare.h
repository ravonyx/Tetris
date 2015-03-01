#ifndef CSQUARE_H
#define CSQUARE_H

#include "Enums.h"
#include "Defines.h"
#include "SDL.h"

class CSquare
{
	private:
		// Location of the center of the square 
		int m_CenterX;
		int m_CenterY;

		// Type of block. Needed to locate the correct square in our bitmap 
		BlockType m_BlockType;

		// A pointer to our bitmap surface from "Main.cpp" 
		SDL_Surface* m_Bitmap;
	public:


	// Default constructor, your compiler will probably require this 
	CSquare();
	// Main constructor takes location and type of block, and a pointer to our bitmap surface. 
	CSquare(int x, int y, SDL_Surface* bitmap, BlockType type);

	// Draw() takes a pointer to the surface to draw to (our window) 
	void Draw(SDL_Surface* window);
	void Move(Direction dir);
	

	// Accessors 
	int GetCenterX();
	int GetCenterY();

	// Mutators
	void SetCenterX(int x);
	void SetCenterY(int y);
};

#endif
