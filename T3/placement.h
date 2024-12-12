#ifndef PLACEMENT_H
#define PLACEMENT_H

void GenerateBoard(int* m, int* n, int* penguins); //handles user input connected to getting board parameters
void FillBoard(int m,int n,int board[m][n],int penguins);// fills the board with pseudo-random values (0-3)
int GenerateTile();// generates a tile with pseudo random value, is used in the fill board function
void PlacePenguin(int m, int n,int board[m][n],int x, int y, int sign);//places a penguin on the board 

#endif