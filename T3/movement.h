#ifndef MOVEMENT_H
#define MOVEMENT_H

void MovePenguin(int m, int n,int board[m][n],int *x, int *y, int *x1, int *y1, int sign);
void AskForCoordinatesOfP(int *x, int *y,int m, int n,int sign, int board[m][n]);
void AskForCoordinatesMovement(int *x, int *y, int *x1,int *y1, int m, int n, int sign, int board[m][n]);
int ValidateMove(int m, int n, int board[m][n],int x, int y,int x1,int y1);
void CollectPoints(int m,int n,int board[m][n],int *x1,int *y1, int points1, int points2,int cur_player);
//check the surrounding of the chosen index to see if it could move
int checkSurr(int i, int j, int m, int n, int board[m][n]);
//check if the index could move and output appropriate response
int CheckStuck(int m, int n,int board[m][n],int sign, int penguins);

#endif