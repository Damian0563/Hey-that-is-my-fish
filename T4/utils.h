
#ifndef UTILS_H
#define UTILS_H

#include "structs.h"

void ClearConsole(); // Clears the console screen
void WaitForEnter(); // Waits for user to press Enter
void AskForDimensions(Board* board);/*
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    Function asks user for dimensions of the board 
*/
void AskForPenguins(Board* board);/*
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    Function asks user fo the amount of penguins each player should have
*/
int ValidateDimensionsAndPenguins(Board* board);/*
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    Function validates the dimensions and total amount of penguins on the board
    returns 1 if dimensions and amount of penguins are in order
    returns 0 otherwise
*/
void AskForCoordinates(int* x, int* y);/*
    int* x; pointer to coordinate x which is later used to place the penguin
    int* y; pointer to coordinate y which is later used to place the penguin
    Function asks user where to place a penguin
*/
int ValidateCoordinates(Board* board, int x, int y);/*
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    int x; Provided coordinate x where to place the penguin
    int y; Provided coordinate y  where to place the penguin
    Function checks whether entered coordinates are valid(return 0 and 1 otherwise)
*/
void AskForCoordinatesOfPenguin(int *x, int *y, int sign,Board* board);/*
    int *x; pointer to coordinate x of penguin to move 
    int *y; pointer to coordinate y of penguin to move 
    int sign; symbol denoting player's penguin(either 8 or 9)
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    Function asks which penguin player wants to move 
*/
void AskForCoordinatesMovement(int *x, int *y, int *x1,int *y1,int sign, Board* board);/*
    int *x; pointer to coordinate x of penguin to move
    int *y; pointer to coordinate y of penguin to move
    int *x1; pointer to new coordinate x of a penguin 
    int *y2; pointer to new coordinate y of a penguin
    int sign; symbol denoting player's penguin(either 8 or 9)
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    Function asks user where to move earlier specified penguin
*/
void ShowBoard(Board* board);/*
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    Function prints the board to the screen
*/

void FreeBoard(Board* board);/*
    Board* board; pointer to the structure board(containing rows,columns,pointer to 2D matrix, penguins_per_player)
    Function clears allocated memory for the dynamic 2D matrix(board)
*/
#endif
