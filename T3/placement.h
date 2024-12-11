#ifndef PLACEMENT_H
#define PLACEMENT_H

void GenerateBoard(int* m, int* n, int* penguins); //handles user input connected to getting board parameters
int ValidateDimensionsAndPenguins(int* m,int* n,int* penguins);//Validates the dimensions as well as the amount of 
//penguins for specified board size
void AskForPenguins(int *penguins);// asks user for the amount of penguins each player should have
void AskForDimensions(int* m, int* n);// asks user for the dimensions of the board
void FillBoard(int m,int n,int board[m][n],int penguins);// fills the board with pseudo-random values (0-3)
int GenerateTile();// generates a tile with pseudo random value, is used in the fill board function
void PlacePenguin(int m, int n,int board[m][n],int x, int y, int sign);//places a penguin on the board 
void AskForCoordinates(int *x, int *y);//asks user where to place a penguin on the board
int ValidateCoordinates(int m, int n,int board[m][n],int x, int y);// gauges whether user specified coordinates are correct





#endif