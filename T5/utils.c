#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"
#include "structs.h"

void ClearConsole() {
    // Cross-platform console clearing
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void WaitForEnter() {
    printf("Press Enter to continue...");
    while (getchar() != '\n');
}

int askForPlayers(int numPlayer) 
{
    do
    {
        printf("Enter the number of players from 2 to 4: ");
        scanf("%d", &numPlayer);
    } while (numPlayer < 2 || numPlayer > 4);
    return numPlayer;
}

void initializePlayers(int numPlayer, Player players[]) 
{              
    
    for (int i = 0; i < numPlayer; i++) 
    {   
        players[i].score = 0;
    }
}

void AskForDimensions(Board* board) {
    printf("\nHow many rows should the board have: ");
    scanf("%d", &(board->rows));
    printf("How many columns should the board have: ");
    scanf("%d", &(board->columns));
}

void AskForPenguins(Board* board) {
    printf("How many penguins each player should have: ");
    scanf("%d", &(board->penguins_per_player));
}

int ValidateDimensionsAndPenguins(Board* board, int numPlayer) {
    if (board->rows > 0 && board->columns > 0 && board->penguins_per_player * numPlayer > board->rows*board->columns) {
        printf("Invalid parameters\n");
        return 0;
    }
    return 1;
}

void AskForCoordinates(int* x, int* y) {
    printf("Enter where would you like to place your penguin (x y): ");
    scanf("%d %d", x, y);
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

void AskForCoordinatesOfPenguin(int *x, int *y, int sign,Board* board)
{
    int newX;
    int newY;
    if(board->penguins_per_player==1)
    {
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
        do
        {
            printf("Where is the penguin you want to move? (x y):\n");
            scanf("%d %d",x,y);
            newX=*x;
            newY=*y;
            if(board->array[newX][newY] != sign)
            {
                printf("That is not your penguin, yours is denoted by: %d\n", sign);
            }
        } while (board->array[newX][newY] != sign);
    }
}

void AskForCoordinatesMovement(int *x, int *y, int *x1,int *y1, int sign,Board* board)
{
    int newX;
    int newY;
    int oldX=*x;
    int oldY=*y;
    do
    {
        printf("Where do you want to move your penguin? (x y):\n");
        scanf("%d %d",x1,y1);
        do
        {
            newX=*x1;
            newY=*y1;
            if(newX<0 || newX>=board->rows || newY<0 || newY>=board->columns)
            {
                printf("Your inputs are out of bounds\n");
                printf("Where do you want to move your penguin? (x y):\n");
                scanf("%d %d",x1,y1);
            }
        } while (newX<0 || newX>=board->rows || newY<0 || newY>=board->columns);
        
        if(newX!=oldX && newY!=oldY)
        {
            printf("You can only move either on the same row or column inside bounds\n");
        }
    } while (newX!=oldX && newY!=oldY);
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