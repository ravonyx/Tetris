#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL.h>    
#include <stack>
#include <vector>
#include "CBlock.h"
#include "CSquare.h"

extern SDL_Surface* g_Bitmap;
extern SDL_Surface* g_Window;
extern SDL_Event g_Event;
extern int g_Timer;      

extern CBlock* g_FocusBlock;  // The block the player is controlling
extern CBlock* g_NextBlock;  // The next block to be the focus block

extern std::vector<CSquare*> g_OldSquares;         // The squares that no longer form the focus block
extern int g_Score;                       // Players current score
extern int g_Level;                       // Current level player is on
extern int g_FocusBlockSpeed; // Speed of the focus block

struct StateStruct
{
	void(*StatePointer)();
};

extern std::stack<StateStruct> g_StateStack;

#endif
