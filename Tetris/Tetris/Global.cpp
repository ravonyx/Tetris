#include "Global.h"

SDL_Surface* 	g_Bitmap = NULL;
SDL_Surface* 	g_Window = NULL;
SDL_Surface* 	texte = NULL;
SDL_Event 	g_Event;
int 		g_Timer;      

CBlock* 	g_FocusBlock = NULL;  
CBlock* 	g_NextBlock  = NULL; 

  
int 		g_Score = 0;                       
int 		g_Level = 1;                     
int 		g_FocusBlockSpeed = INITIAL_SPEED; 

std::vector<CSquare*> g_OldSquares;      
std::stack<StateStruct> g_StateStack;
