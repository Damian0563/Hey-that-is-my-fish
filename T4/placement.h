#ifndef PLACEMENT_H
#define PLACEMENT_H

void GenerateBoard(int* m, int* n, int* penguins);/*
    int* m; pointer to amount of rows of the board(0 initially)
    int* n; pointer to amount of columns of the board(0 initially)
    int* penguins; pointer to the amount of penguins each player has(0 initially)
    Function generates the board, within itself it invokes some other functions, which ask user for input
    and validate it
*/
void FillBoard(int m,int n,int board[m][n],int penguins);/*
    int m; amount of rows 
    int n; number of columns
    int board[m][n]; generated board with current playing position
    int penguins; the amount of penguins each player has
    Function fills the board with pseudo random values, the function also handles an edge case
*/
int GenerateTile();/*
    Function generates a tile in range<0-3>
*/
void PlacePenguin(int m, int n,int board[m][n],int x, int y, int sign);/*
    int m; amount of rows 
    int n; number of columns
    int board[m][n]; generated board with current playing position
    int x; selected coordinate x on the board
    int y; selected coordinate y on the board
    int sign; symbol denoting player's penguin(either 8 or 9)
    Function places a penguin on selected tile on the board prior to neccessary validations
*/ 

#endif