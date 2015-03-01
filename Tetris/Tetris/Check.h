#ifndef CHECK_H
#define CHECK_H

// Return amount of lines cleared or zero if no lines were cleared 
int CheckCompletedLines();
// Check to see if player has won. Handle winning condition if needed. 
void CheckWin();
void CheckLoss();
void ChangeFocusBlock();

#endif

