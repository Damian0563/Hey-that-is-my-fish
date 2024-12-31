#ifndef PLACEMENT_H
#define PLACEMENT_H

#include "structs.h"
void GenerateBoard(Board* board);/*
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    Function generates the board, within itself it invokes some other functions, which ask user for input
    and validate it
*/
void FillBoard(Board* board);/*
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    Function fills the board with pseudo random values, the function also handles an edge case
*/
int GenerateTile();/*
    Function generates a tile in range<0-3>
*/
void PlacePenguin(Board* board,int x, int y, int sign);/*
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    int x; selected coordinate x on the board
    int y; selected coordinate y on the board
    int sign; symbol denoting player's penguin(either 8 or 9)
    Function places a penguin on selected tile on the board prior to neccessary validations
*/ 

#endif