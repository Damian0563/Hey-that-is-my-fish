/**
 * @file placement.c
 * @author Team D
 * @brief This file contains the implementation of functions for placing penguins on the game board.
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "placement.h"
#include "utils.h"
#include "structs.h"
#include <string.h>

/**
 * @brief This function generates the game board and initializes it based on user input.
 * 
 * @param board pointer to the Board structure to initialize.
 * @param numPlayer the number of players participating in the game.
 */
void generateBoard(Board *board, int numPlayer)
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
            askForDimensions(board);
            askForPenguins(board);
        } while (validateDimensionsAndPenguins(board, numPlayer) == 0);
    }
    else
    {
        //+1 needed for logic, +3 needed for clarity, readable board, it is a board at least 3x3
        do
        {
            board->rows = (rand() % 10) + 3;
            board->columns = (rand() % 10) + 3;
            askForPenguins(board);
        } while (validateDimensionsAndPenguins(board, numPlayer) == 0);
    }
}

/**
 * @brief This function checks if the board has enough space for the penguins.
 * 
 * @param board pointer to the Board structure representing the game board.
 * @param numPlayer the number of players participating in the game.
 */
void fillBoard(Board *board, int numPlayer)
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
            board->array[i][j] = generateTile();
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

/**
 * @brief This function generates a random tile value in the range [0, 3] inclusive.
 * 
 * @return An integer representing the generated tile value.
 */
int generateTile()
{
    return rand() % 4;
}

/**
 * @brief This function places a penguin on the selected tile of the board.
 * 
 * @param board Pointer to the Board structure representing the game board.
 * @param x The x-coordinate of the tile on the board.
 * @param y The y-coordinate of the tile on the board.
 * @param sign An integer symbol denoting the player's penguin (e.g., 8 or 9).
 */
void placePenguin(Board *board, int x, int y, int sign)
{
    board->array[x][y] = sign;
}

/**
 * @brief This function places a penguin autonomously on the board using logic.
 * 
 * @param board Pointer to the Board structure representing the game board.
 * @param my_id Integer value representing the id of the program.
 * @param num_players Integer value representing the number of players in the game.
 */
void placeAutonomously(AutonomousPlayer players[],Board *board,int my_id,int num_players)
{
    int best_i=-1,best_j=0; //searching for tiles with high potential(not on the borders of the board)
    int best_score=0;
    for(int i=0;i<board->rows;i++)
    {
        for(int j=0;j<board->columns;j++)
        {   
            if(board->array[i][j] == 1)
            {
                int score=1;
                if(i+1<board->rows && board->array[i+1][j]>0) score*=board->array[i+1][j];
                if(i-1>=0 && board->array[i-1][j]>0) score*=board->array[i-1][j];
                if(j+1<board->columns && board->array[i][j+1]) score*=board->array[i][j+1];
                if(j-1>=0 && board->array[i][j-1]) score*=board->array[i][j-1];
                if(score>=best_score)
                {
                    best_score=score;
                    best_i=i;
                    best_j=j;
                }
            }
        }
    }
    if(best_i!=-1){
        incrementScore(players,num_players,my_id,board->array[best_i][best_j]);
        board->array[best_i][best_j]=(my_id*-1);
    }else{
        exit(2);
    }
}

/**
 * @brief This function checks whether the program can place a penguin, taking into account the upper limit of penguins.
 * 
 * @param board Pointer to the Board structure representing the game board.
 * @param PenguinsToPlace Integer value storing information about the number of penguins per player.
 * 
 * @return 0 if the player can place a penguin; 1 if all penguins are placed.
 */
int checkPenguinsToPlace(Board *board,int PenguinsToPlace,int my_id){
    int counter=0;
    for(int i=0;i<board->rows;i++)
    {
        for(int j=0;j<board->columns;j++)
        {
            if(board->array[i][j]==((-1)*my_id))
            {
                counter++;
            }
        }
    }
    if (counter==PenguinsToPlace) return 0;
    return 1;
}