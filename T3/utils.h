#ifndef UTILS_H
#define UTILS_H

void ClearConsole(); // Clears the console screen
void PrintMessage(const char* message); // Prints a uniform message
int GetValidatedInput(int min, int max); // Validates and returns an integer input within range
void WaitForEnter(); // Waits for user to press Enter
void AskForDimensions(int* m, int* n); // Asks user for board dimensions
void AskForPenguins(int* penguins); // Asks user for the number of penguins per player
int ValidateDimensionsAndPenguins(int* m, int* n, int* penguins); // Validates board dimensions and penguins count
void AskForCoordinates(int* x, int* y); // Asks user for a coordinate
int ValidateCoordinates(int m, int n, int board[m][n], int x, int y); // Validates if a coordinate is valid
void AskForCoordinatesOfPenguin(int *x, int *y, int m, int n, int sign, int board[m][n], int penguins);// asks user which penguin to 
//move and performs neccessary validations
void AskForCoordinatesMovement(int *x, int *y, int *x1,int *y1, int m, int n, int sign, int board[m][n]);//Asks where to
//move earlier specified penguin and performs neccessary validations
void ShowBoard(int m,int n,int board[m][n]);//prints the board to the screen

#endif
