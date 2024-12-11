#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

void ClearConsole() {
    // Cross-platform console clearing
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void PrintMessage(const char* message) {
    printf("%s\n", message);
}

int GetValidatedInput(int min, int max) {
    int value;
    char buffer[100];
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &value) == 1 && value >= min && value <= max) {
                return value;
            }
        }
        printf("Invalid input. Please enter a number between %d and %d: ", min, max);
    }
}

void WaitForEnter() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

void AskForDimensions(int* m, int* n) {
    printf("\nHow many rows should the board have: ");
    scanf("%d", m);
    printf("How many columns should the board have: ");
    scanf("%d", n);
}

void AskForPenguins(int* penguins) {
    printf("How many penguins each player should have: ");
    scanf("%d", penguins);
}

int ValidateDimensionsAndPenguins(int* m, int* n, int* penguins) {
    if (*m > 0 && *n > 0 && *penguins * 2 > (*m) * (*n)) {
        printf("Invalid parameters\n");
        return 0;
    }
    return 1;
}

void AskForCoordinates(int* x, int* y) {
    printf("Enter where would you like to place your penguin (x y): ");
    scanf("%d %d", x, y);
}

int ValidateCoordinates(int m, int n, int board[m][n], int x, int y) {
    if (x < m && x >= 0 && y < n && y >= 0) {
        if (board[x][y] == 1) {
            return 0;
        } else {
            printf("Invalid tile selected\n");
            return 1;
        }
    }
    printf("Selected tile is out of bounds\n");
    return 1;
}

void AskForCoordinatesOfPenguin(int *x, int *y, int m, int n, int sign, int board[m][n])
{
    int newX;
    int newY;
    do
    {
        printf("Where is the penguin you want to move? (x y):\n");
        scanf("%d %d",x,y);
        newX=*x;
        newY=*y;
        if(board[newX][newY] != sign)
        {
            printf("That is not your penguin, yours is denoted by: %d\n", sign);
        }
    } while (board[newX][newY] != sign);
}

void AskForCoordinatesMovement(int *x, int *y, int *x1,int *y1, int m, int n, int sign, int board[m][n])
{
    int newX;
    int newY;
    int oldX=*x;
    int oldY=*y;
    do
    {
        printf("Where do you want to move your penguin? (x y):\n");
        scanf("%d %d",x1,y1);
        newX=*x1;
        newY=*y1;
        do
        {
            if(newX<0 || newX>=m || newY<0 || newY>n)
            {
                printf("Your inputs are out of bounds\n");
                printf("Where do you want to move your penguin? (x y):\n");
                scanf("%d %d",x1,y1);
            }
        } while (newX<0 || newX>=m || newY<0 || newY>n);
        
        if(newX!=oldX && newY!=oldY)
        {
            printf("You can only move either on the same row or column inside bounds\n");
        }
    } while (newX!=oldX && newY!=oldY);
}


void ShowBoard(int m,int n,int board[m][n])
{
    printf("\n   ");
    for (int j = 0; j < n; j++) 
    {
        if(j==0){
            printf(" ");
        }
        printf("%4d", j);  // Print column headers
    }
    printf("\n   ");
    for (int j = 0; j < n+1; j++) 
    {
        printf("----"); // Separator line below headers
    }
    printf("\n");
    for (int i = 0; i < m; i++) 
    {
        printf("%2d |", i); // Print row headers
        for (int j = 0; j < n; j++) {
            if (board[i][j]==8){
                printf("\033[1;31m%4d\033[0m", board[i][j]);
            }else if(board[i][j]==9){
                printf("\033[1;34m%4d\033[0m", board[i][j]);
            }else{
                printf("%4d",board[i][j]);
            }
        }
        printf("\n");
    }
}