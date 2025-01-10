#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "utils.h"
#include <ctype.h>


int askForPlayers(int numPlayer) {
    char term;
    do {
        printf("Enter the number of players from 2 to 4: ");
        if (scanf("%d%c", &numPlayer, &term) != 2 || term != '\n') {
            printf("Enter the number of players from 2 to 4: ");
            while (getchar() != '\n'); // Clear invalid input
            numPlayer = 0; // Reset to ensure the loop continues
        }
    } while (numPlayer < 2 || numPlayer > 4);
    return numPlayer;
}

void AskForDimensions(Board* board) {
    char term;
    do {
        printf("\nHow many rows should the board have: ");
        if (scanf("%d%c", &(board->rows), &term) != 2 || term != '\n' || board->rows <= 0) {
            printf("\nHow many rows should the board have: ");
            while (getchar() != '\n'); // Clear invalid input
            board->rows = 0;
        }
    } while (board->rows <= 0);

    do {
        printf("How many columns should the board have: ");
        if (scanf("%d%c", &(board->columns), &term) != 2 || term != '\n' || board->columns <= 0) {
            printf("How many columns should the board have: ");
            while (getchar() != '\n'); // Clear invalid input
            board->columns = 0;
        }
    } while (board->columns <= 0);
}

void AskForPenguins(Board* board) {
    char term;
    do {
        printf("How many penguins each player should have: ");
        if (scanf("%d%c", &(board->penguins_per_player), &term) != 2 || term != '\n' || board->penguins_per_player <= 0) {
            //printf("How many penguins each player should have: ");
            while (getchar() != '\n'); // Clear invalid input
            board->penguins_per_player = 0;
        }
    } while (board->penguins_per_player <= 0);
}

void AskForCoordinates(int* x, int* y) {
    char term;
    do {
        printf("Enter where would you like to place your penguin (x y): ");
        if (scanf("%d %d%c", x, y, &term) != 3 || term != '\n') {
            //printf("Enter where would you like to place your penguin (x y): ");
            while (getchar() != '\n'); // Clear invalid input
            *x = *y = -1; // Reset values
        }
    } while (*x < 0 || *y < 0);
}

void AskForCoordinatesOfPenguin(int *x, int *y, int sign, Board* board) {
    int newX;
    int newY;
    if(board->penguins_per_player==1){
        for(int i = 0; i< board->rows; i++)
        {
            for(int j = 0; j<board->columns;j++)
            {
                if(board->array[i][j]==sign)
                {
                    *x= i;
                    *y= j;
                }
            }
        } 

    }
    else
    {
        char term;
        int valid = 0;
        do {
            printf("Where is the penguin you want to move? (x y): ");
            if (scanf("%d %d%c", x, y, &term) != 3 || term != '\n') {
                //printf("Where is the penguin you want to move? (x y):\n");
                while (getchar() != '\n'); // Clear invalid input
                continue;
            }
            if (board->array[*x][*y] == sign) {
                valid = 1;
            }else {
                char letter;
                if(sign==6){
                    letter='A';
                }else if(sign==7){
                    letter='B';
                }else if(sign==8){
                    letter='C';
                }else if(sign==9){
                    letter='D';
                }else{
                    printf("Internal program error");
                }
                printf("That is not your penguin, yours is denoted by: %c\n", letter);
            }
        } while (!valid);
    }
}

void AskForCoordinatesMovement(int *x, int *y, int *x1, int *y1, int sign, Board* board) {
    char term;
    int valid = 0;
    do {
        printf("Where do you want to move your penguin? (x y): ");
        if (scanf("%d %d%c", x1, y1, &term) != 3 || term != '\n') {
            //printf("Where do you want to move your penguin? (x y):");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }
        if ((*x1 == *x || *y1 == *y) && *x1 >= 0 && *x1 < board->rows && *y1 >= 0 && *y1 < board->columns) {
            valid = 1;
        } else {
            printf("You can only move either on the same row or column inside bounds");
        }
    } while (!valid);
}

void initializePlayers(int numPlayer, Player players[]) 
{                  
    for (int i = 0; i < numPlayer; i++) 
    {   
        players[i].score = 0;
    }
}

int ValidateDimensionsAndPenguins(Board* board, int numPlayer) {
    if (board->rows > 0 && board->columns > 0 && board->penguins_per_player * numPlayer > board->rows*board->columns) {
        printf("Invalid parameters\n");
        return 0;
    }
    return 1;
}

void printScores(Player players[], int numPlayer) 
{
    printf("\nScores:\n");
    for (int i = 0; i < numPlayer; i++) 
    {
        printf("Player %d score: %d\n", i+1, players[i].score);
    }
}

void summerization(Player players[], int numPlayer)
{
    int highest = 0;
    int player = 0;
    int occurance = 0;
    for(int i=0;i<numPlayer;i++)
    {
        if(players[i].score>highest)
        {
            occurance=0;
            highest=players[i].score;
            player=i+1;
            
        }
        else if(players[i].score==highest)
        {
            occurance++;
        }
    }

    if (occurance==0)
    {
        printf("Player %d wins with %d points!\n", player, highest);
    }
    else
    {
        printf("It's a tie!\n");
    }
}

void ShowBoard(Board* board)
{
    printf("\n   ");
    for (int j = 0; j < board->columns; j++) 
    {
        if(j==0){
            printf(" ");
        }
        printf("%4d", j);  // Print column headers
    }
    printf("\n   ");
    for (int j = 0; j < board->columns+1; j++) 
    {
        printf("----"); // Separator line below headers
    }
    printf("\n");
    for (int i = 0; i < board->rows; i++) 
    {
        printf("%2d |", i); // Print row headers
        for (int j = 0; j < board->columns; j++) {
            if (board->array[i][j] == 6) {
                printf("\033[1;31m%4c\033[0m", 'A'); // Red 'A'
            } else if (board->array[i][j] == 7) {
                printf("\033[1;34m%4c\033[0m", 'B'); // Blue 'B'
            } else if (board->array[i][j] == 8) {
                printf("\033[1;33m%4c\033[0m", 'C'); // Yellow 'C'
            } else if (board->array[i][j] == 9) {
                printf("\033[1;32m%4c\033[0m", 'D'); // Green 'D'
            } else {
                printf("%4d", board->array[i][j]); // Default case for other numbers
            }

        }
        printf("\n");
    }
}

void FreeBoard(Board *board) {
    for (int i = 0; i < board->rows; i++) {
        free(board->array[i]); // Free each row
    }
    free(board->array); // Free the array of row pointers
    board->array=NULL;
    board->rows=0;
    board->columns=0;
    board->penguins_per_player=0;
}

int ValidateCoordinates(Board* board, int x, int y) {
    if (x < board->rows && x >= 0 && y < board->columns && y >= 0) {
        if (board->array[x][y] == 1) {
            return 0;
        } else {
            printf("Invalid tile selected\n");
            return 1;
        }
    }
    printf("Selected tile is out of bounds\n");
    return 1;
}


