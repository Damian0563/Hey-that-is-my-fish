#ifndef MOVEMENT_H
#define MOVEMENT_H

void MovePenguin(int m, int n,int board[m][n],int *x, int *y, int *x1, int *y1, int sign);/*
    int m; amount of rows 
    int n; number of columns
    int board[m][n]; generated board with current playing position
    int *x; pointer to the x coordinate of current location of the penguin
    int *y; pointer to the y coordinate of current location of the penguin
    int *x1; pointer to the new x coordinate of the penguin
    int *y1; pointer t the new y coordinate of the penguin
    int sign; symbol denoting player's penguin(either 8 or 9)
    Function places the penguin on a given tile after appropriate validations
*/
int ValidateMove(int m, int n, int board[m][n],int x, int y,int x1,int y1);/*
    int m; amount of rows 
    int n; number of columns
    int board[m][n]; generated board with current playing position
    int x; the x coordinate of current location of selected penguin
    int y; the y coordinate of current location of selected penguin
    int x1; new(selected) coordinate x of the penguin
    int y1; new(selected) coodinate y of the penguin
    Function checks whether the move is possible or not-if it is the function returns 1 and 0 otherwise
*/
void CollectPoints(int m,int n,int board[m][n],int *x1,int *y1, int *point);/*
    int m; amount of rows 
    int n; number of columns
    int board[m][n]; generated board with current playing position
    int *x1; pointer to the x coordinate of the penguin after the move
    int *y1; pointer to the y coordinate of the penguin after the move
    int *point; pointer to the amount of points of a respective player
    Function awards point(s) to the player which just made a move
*/
int CheckSurrounding(int i, int j, int m, int n, int board[m][n]);/*
    int i; coordinate x, which is a coordinate of the penguin
    int j; coordinate y, which is a coordinate of the penguin
    int m; amount of rows 
    int n; number of columns
    int board[m][n]; generated board with current playing position
    Function checks whether a penguin of a player can move- if it can move the function returns 0 and 1 otherwise
*/
int CheckStuck(int m, int n,int board[m][n],int sign, int penguins);/*
    int m; amount of rows 
    int n; number of columns
    int board[m][n]; generated board with current playing position
    int sign; symbol denoting player's penguin(either 8 or 9)
    int penguins; amount of penguins EACH player has
    Function checks whether a given player can move, or not- if the player can move the functions 
    returns 0 and 1 otherwise
*/

#endif