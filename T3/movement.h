#ifndef MOVEMENT_H
#define MOVEMENT_H

void MovePenguin(int m, int n,int board[m][n],int *x, int *y, int *x1, int *y1, int sign);//Moves the penguin to a specified
//tile after earlier validations
void AskForCoordinatesOfPenguin(int *x, int *y,int m, int n,int sign, int board[m][n]);//Asks user for the
//coordinates of a penguin to move
void AskForCoordinatesMovement(int *x, int *y, int *x1,int *y1, int m, int n, int sign, int board[m][n]);//Asks user where
//to move earlier specified penguin
int ValidateMove(int m, int n, int board[m][n],int x, int y,int x1,int y1);//Validates players move and 
//selected coordinates of a penguins to move
void CollectPoints(int m,int n,int board[m][n],int *x1,int *y1, int *point);//awards the points from a given tile to earlier
//specified player
int CheckSurrounding(int i, int j, int m, int n, int board[m][n]);//Check the surrounding of the chosen index 
//to see if it could move
int CheckStuck(int m, int n,int board[m][n],int sign, int penguins);//checks if the penguin could move from provided
//index could move and output appropriate response

#endif