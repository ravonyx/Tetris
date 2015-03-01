#ifndef COLLISIONS_H
#define COLLISIONS_H

void HandleBottomCollision();
// Check collisions between a given square and the squares in g_OldSquares 
bool CheckEntityCollisions(CSquare* square, Direction dir); 
// Check collisions between a given block and the squares in g_OldSquares 
bool CheckEntityCollisions(CBlock* block, Direction dir);
// Check collisions between a given square and the sides of the game area 
bool CheckWallCollisions(CSquare* square, Direction dir); 
// Check for collisions between a given block a the sides of the game area 
bool CheckWallCollisions(CBlock* block, Direction dir); 
bool CheckRotationCollisions(CBlock* block);

#endif
