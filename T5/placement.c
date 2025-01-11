#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "placement.h"
#include "utils.h"
#include "structs.h"
#include <string.h>




void GenerateBoard(Board *board, int numPlayer)
{
    int ans;
    char term;
    do {
        printf("Would you like to generate a board manually or artificially: 1[manually] or 2[artificially]: ");
        if (scanf("%d%c",&ans,&term) != 2 || term != '\n') {
            //printf("Enter where would you like to place your penguin (x y): ");
            while (getchar() != '\n'); // Clear invalid input
            ans=0; // Reset values
        }
    } while (ans != 1 && ans != 2);
    
    if (ans == 1)
    {
        do
        {
            AskForDimensions(board);
            AskForPenguins(board);
        } while (ValidateDimensionsAndPenguins(board, numPlayer) == 0);
    }
    else
    {
        //+1 needed for logic, +3 needed for clarity, readable board, it is a board at least 3x3
        do
        {
            board->rows = (rand() % 10) + 3;
            board->columns = (rand() % 10) + 3;
            AskForPenguins(board);
        } while (ValidateDimensionsAndPenguins(board, numPlayer) == 0);
    }
}

void FillBoard(Board *board, int numPlayer)
{
    int ones = 0;
    board->array = (int **)malloc(board->rows * sizeof(int *));
    if (board->array == NULL)
    {
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < board->rows; i++)
    {
        board->array[i] = (int *)malloc(board->columns * sizeof(int));
    }

    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->columns; j++)
        {
            board->array[i][j] = GenerateTile();
            if (board->array[i][j] == 1)
            {
                ones++;
            }
        }
    }
    while (ones < board->penguins_per_player * numPlayer)
    {
        int gen_i = rand() % board->rows;
        int gen_j = rand() % board->columns;
        if (board->array[gen_i][gen_j] != 1)
        {
            board->array[gen_i][gen_j] = 1;
            ones++;
        }
    }
}

int GenerateTile()
{
    return rand() % 4;
}

void PlacePenguin(Board *board, int x, int y, int sign)
{
    board->array[x][y] = sign;
}

void PlaceAutonomously(AutonomousPlayer players[],Board *board,int my_id,int num_players)
{
    int best_i,best_j; //searching for tiles with high potential(not on the borders of the board)
    int best_score=0;
    for(int i=0;i<board->rows;i++)
    {
        for(int j=0;j<board->columns;j++)
        {   
            if(board->array[i][j] == 1)
            {
                int score=-1;
                if(i+1<board->rows && board->array[i+1][j]>0) score*=board->array[i+1][j];
                if(i-1>=0 && board->array[i-1][j]>0) score*=board->array[i-1][j];
                if(j+1<board->columns && board->array[i][j+1]) score*=board->array[i][j+1];
                if(j-1>=0 && board->array[i][j-1]) score*=board->array[i][j-1];
                if(score>best_score)
                {
                    best_score=score;
                    best_i=i;
                    best_j=j;
                }
            }
        }
    }
    IncrementScore(players,num_players,my_id,board->array[best_i][best_j]);
    board->array[best_i][best_j]=(my_id*-1);
}


int CheckPenguinsToPlace(Board *board,int my_id,int PenguinsToPlace){
    my_id*=-1;
    int counter=0;
    for(int i=0;i<board->rows;i++)
    {
        for(int j=0;j<board->columns;j++)
        {
            if(board->array[i][j]==my_id) counter++;
        }
    }
    if (counter==PenguinsToPlace) return 0;
    return 1;
}