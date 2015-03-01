#include "CSquare.h"
#include "Color.h"

// Default constructor, your compiler will probably require this 
CSquare::CSquare(){}
// Main constructor takes location and type of block, and a pointer to our bitmap surface. 
CSquare::CSquare(int x, int y, SDL_Surface* bitmap, BlockType type) : m_CenterX(x), m_CenterY(y), m_Bitmap(bitmap), m_BlockType(type){}

void CSquare::Draw(SDL_Surface* window)
{
    SDL_Rect source;

    // switch statement to determine the location of the square within our bitmap
    switch (m_BlockType)
    {
	case SQUARE_BLOCK:
	{
	    SDL_Rect temp = { RED_SQUARE_X, RED_SQUARE_Y, SQUARE_MEDIAN * 2,
	        SQUARE_MEDIAN * 2 };
	    source = temp;
	} break;
	case T_BLOCK:
	{
	    SDL_Rect temp = { PURPLE_SQUARE_X, PURPLE_SQUARE_Y, SQUARE_MEDIAN * 2,
	        SQUARE_MEDIAN * 2 };
	    source = temp;
	} break;
	case L_BLOCK:
	{
	    SDL_Rect temp = { GREY_SQUARE_X, GREY_SQUARE_Y, SQUARE_MEDIAN * 2,
	        SQUARE_MEDIAN * 2 };
	    source = temp;
	} break;
	case BACKWARDS_L_BLOCK:
	{
	    SDL_Rect temp = { BLUE_SQUARE_X, BLUE_SQUARE_Y, SQUARE_MEDIAN * 2,
	        SQUARE_MEDIAN * 2 };
	    source = temp;
	} break;
	case STRAIGHT_BLOCK:
	{
	    SDL_Rect temp = { GREEN_SQUARE_X, GREEN_SQUARE_Y, SQUARE_MEDIAN * 2, 
	        SQUARE_MEDIAN * 2 };
	    source = temp;
	} break;
	case S_BLOCK:
	{
	    SDL_Rect temp = { BLACK_SQUARE_X, BLACK_SQUARE_Y, SQUARE_MEDIAN * 2, 
	        SQUARE_MEDIAN * 2 };
	    source = temp;
	} break;
	case BACKWARDS_S_BLOCK:
	{
	    SDL_Rect temp = { YELLOW_SQUARE_X, YELLOW_SQUARE_Y, SQUARE_MEDIAN * 2, 
	        SQUARE_MEDIAN * 2 };
	    source = temp;
	} break;
    }

     // Draw at square's current location. Remember that m_X and m_Y store the
     // center of the square. 
    SDL_Rect destination = { m_CenterX - SQUARE_MEDIAN, m_CenterY - SQUARE_MEDIAN, 
    SQUARE_MEDIAN * 2, SQUARE_MEDIAN * 2 };
    SDL_FillRect(m_Bitmap, NULL, SDL_MapRGB(window->format, 17, 206, 112));
    SDL_BlitSurface(m_Bitmap, &source, window, &destination);
}

void CSquare::Move(Direction dir)
{
    switch (dir)
    {
	case LEFT:
	{
	    m_CenterX -= SQUARE_MEDIAN * 2;
	} break;
	case RIGHT:
	{
	    m_CenterX += SQUARE_MEDIAN * 2;
	} break;
	case DOWN:
	{
	    m_CenterY += SQUARE_MEDIAN*2;
	} break;
   }
}  

// Accessors 
int CSquare::GetCenterX() { return m_CenterX; }
int CSquare::GetCenterY() { return m_CenterY; }

// Mutators
void CSquare::SetCenterX(int x) { m_CenterX = x; }
void CSquare::SetCenterY(int y) { m_CenterY = y; }

