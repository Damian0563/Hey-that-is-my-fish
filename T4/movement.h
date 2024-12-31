#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "structs.h"

void MovePenguin(Board* board,int *x, int *y, int *x1, int *y1, int sign);/*
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    int *x; pointer to the x coordinate of current location of the penguin
    int *y; pointer to the y coordinate of current location of the penguin
    int *x1; pointer to the new x coordinate of the penguin
    int *y1; pointer t the new y coordinate of the penguin
    int sign; symbol denoting player's penguin(either 8 or 9)
    Function places the penguin on a given tile after appropriate validations
*/
int ValidateMove(Board* board,int x, int y,int x1,int y1);/*
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    int x; the x coordinate of current location of selected penguin
    int y; the y coordinate of current location of selected penguin
    int x1; new(selected) coordinate x of the penguin
    int y1; new(selected) coodinate y of the penguin
    Function checks whether the move is possible or not-if it is the function returns 1 and 0 otherwise
*/
int CheckSurrounding(int i, int j, Board* board);/*
    int i; coordinate x, which is a coordinate of the penguin
    int j; coordinate y, which is a coordinate of the penguin
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    Function checks whether a penguin of a player can move- if it can move the function returns 0 and 1 otherwise
*/
int CheckStuck(Board* board,int sign);/*
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    int sign; symbol denoting player's penguin(either 8 or 9)
    int penguins; amount of penguins EACH player has
    Function checks whether a given player can move, or not- if the player can move the functions 
    returns 0 and 1 otherwise
*/

#endif