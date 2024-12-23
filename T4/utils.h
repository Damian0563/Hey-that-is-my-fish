#ifndef UTILS_H
#define UTILS_H

void ClearConsole(); // Clears the console screen
void WaitForEnter(); // Waits for user to press Enter
void AskForDimensions(int* m, int* n);/*
    int* m; pointer to the amount of rows
    int* n; pointer to the amount of columns
    Function asks user for dimensions of the board 
*/
void AskForPenguins(int* penguins);/*
    int* penguins; pointer to the amount of penguins
    Function asks user fo the amount of penguins each player should have
*/
int ValidateDimensionsAndPenguins(int* m, int* n, int* penguins);/*
    int* m; pointer to the amount of rows
    int* n; pointer to the number of columns
    int* penguins; pointer to the amount of penguins
    Function validates the dimensions and total amount of penguins on the board
    returns 1 if dimensions and amount of penguins are in order
    returns 0 otherwise
*/
void AskForCoordinates(int* x, int* y);/*
    int* x; pointer to coordinate x which is later used to place the penguin
    int* y; pointer to coordinate y which is later used to place the penguin
    Function asks user where to place a penguin
*/
int ValidateCoordinates(int m, int n, int board[m][n], int x, int y);/*
    int m; amount of rows 
    int n; number of columns
    int board[m][n]; generated board with current playing position
    int x; Provided coordinate x where to place the penguin
    int y; Provided coordinate y  where to place the penguin
    Function checks whether entered coordinates are valid(return 0 and 1 otherwise)
*/
void AskForCoordinatesOfPenguin(int *x, int *y, int m, int n, int sign, int board[m][n], int penguins);/*
    int *x; pointer to coordinate x of penguin to move 
    int *y; pointer to coordinate y of penguin to move 
    int m; amount of rows 
    int n; number of columns
    int sign; symbol denoting player's penguin(either 8 or 9)
    int board[m][n]; generated board with current playing position
    int penguins; the amount of penguins each player has
    Function asks which penguin player wants to move 
*/
void AskForCoordinatesMovement(int *x, int *y, int *x1,int *y1, int m, int n, int sign, int board[m][n]);/*
    int *x; pointer to coordinate x of penguin to move
    int *y; pointer to coordinate y of penguin to move
    int *x1; pointer to new coordinate x of a penguin 
    int *y2; pointer to new coordinate y of a penguin
    int m; amount of rows 
    int n; number of columns
    int sign; symbol denoting player's penguin(either 8 or 9)
    int board[m][n]; generated board with current playing position
    Function asks user where to move earlier specified penguin
*/
void ShowBoard(int m,int n,int board[m][n]);/*
    int m; amount of rows 
    int n; number of columns
    int board[m][n]; generated board with current playing position
    Function prints the board to the screen
*/

#endif
