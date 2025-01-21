/**
 * @file utils.c
 * @author Team D
 * @brief This file contains utility functions for the game.
 * @date 2025-01-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "string.h"
#include "utils.h"
#include <ctype.h>

/**
 * @brief This function asks the user to enter the number of players.
 *
 * @param num_players the number of players participating in the game.
 *
 * @return int representing the number of players that were successfully assigned an ID.
 */
int askForPlayers(int num_players)
{
    char term;
    do
    {
        printf("Enter the number of players from 2 to 4: ");
        if (scanf("%d%c", &num_players, &term) != 2 || term != '\n')
        {
            while (getchar() != '\n')
                ;            // Clear invalid input
            num_players = 0; // Reset to ensure the loop continues
        }
    } while (num_players < 2 || num_players > 4);
    return num_players;
}

/**
 * @brief This function asks the user to enter the dimensions of the board.
 *
 * This function clears the console screen by printing a series of newline characters.
 *
 * @param board Pointer to the Board structure to initialize.
 */
void askForDimensions(Board *board)
{
    char term;
    do
    {
        printf("How many rows should the board have: ");
        if (scanf("%d%c", &(board->rows), &term) != 2 || term != '\n' || board->rows <= 0)
        {
            while (getchar() != '\n')
                ; // Clear invalid input
            board->rows = 0;
        }
    } while (board->rows <= 0);

    do
    {
        printf("How many columns should the board have: ");
        if (scanf("%d%c", &(board->columns), &term) != 2 || term != '\n' || board->columns <= 0)
        {
            while (getchar() != '\n')
                ; // Clear invalid input
            board->columns = 0;
        }
    } while (board->columns <= 0);
}

/**
 * @brief This function asks the user to enter the number of penguins each player should have.
 *
 * @param board Pointer to the Board structure to initialize.
 */
void askForPenguins(Board *board)
{
    char term;
    do
    {
        printf("How many penguins each player should have: ");
        if (scanf("%d%c", &(board->penguins_per_player), &term) != 2 || term != '\n' || board->penguins_per_player <= 0)
        {
            while (getchar() != '\n')
                ; // Clear invalid input
            board->penguins_per_player = 0;
        }
    } while (board->penguins_per_player <= 0);
}

/**
 * @brief This function asks the user to enter the coordinates to place their penguins in placement phase.
 *
 * @param x Pointer to the x-coordinate.
 * @param y Pointer to the y-coordinate.
 */
void askForCoordinates(int *x, int *y)
{
    char term;
    do
    {
        printf("Enter where would you like to place your penguin (x y): ");
        if (scanf("%d %d%c", x, y, &term) != 3 || term != '\n')
        {
            while (getchar() != '\n')
                ;         // Clear invalid input
            *x = *y = -1; // Reset values
        }
    } while (*x < 0 || *y < 0);
}

/**
 * @brief This function asks the user to enter the coordinates of their own penguin that they want to move
 *
 * @param board Pointer to the board structure.
 * @param x The x-coordinate to validate.
 * @param y The y-coordinate to validate.
 *
 * @return 1 if valid, 0 otherwise.
 */
void askForCoordinatesOfPenguin(int *x, int *y, int sign, Board *board)
{
    int newX;
    int newY;
    if (board->penguins_per_player == 1)
    {
        for (int i = 0; i < board->rows; i++)
        {
            for (int j = 0; j < board->columns; j++)
            {
                if (board->array[i][j] == sign)
                {
                    *x = i;
                    *y = j;
                }
            }
        }
    }
    else
    {
        char term;
        int valid = 0;
        do
        {
            printf("Where is the penguin you want to move? (x y): ");
            if (scanf("%d %d%c", x, y, &term) != 3 || term != '\n')
            {
                while (getchar() != '\n')
                    ; // Clear invalid input
                continue;
            }
            if (board->array[*x][*y] == sign)
            {
                valid = 1;
            }
            else
            {
                char letter;
                if (sign == 6)
                {
                    letter = 'A';
                }
                else if (sign == 7)
                {
                    letter = 'B';
                }
                else if (sign == 8)
                {
                    letter = 'C';
                }
                else if (sign == 9)
                {
                    letter = 'D';
                }
                else
                {
                    printf("Internal program error");
                }
                printf("That is not your penguin, yours is denoted by: %c\n", letter);
            }
        } while (!valid);
    }
}

/**
 * @brief This function asks the user to enter the coordinates of the penguin they want to move to and check if its vald.
 *
 * @param x Pointer to the x-coordinate of the penguin.
 * @param y Pointer to the y-coordinate of the penguin.
 * @param x1 Pointer to the new x-coordinate of the penguin.
 * @param y1 Pointer to the new y-coordinate of the penguin.
 * @param sign The player's penguin identifier.
 * @param board Pointer to the board structure.
 */
void askForCoordinatesMovement(int *x, int *y, int *x1, int *y1, int sign, Board *board)
{
    char term;
    int valid = 0;
    do
    {
        printf("Where do you want to move your penguin? (x y): ");
        if (scanf("%d %d%c", x1, y1, &term) != 3 || term != '\n')
        {
            // printf("Where do you want to move your penguin? (x y):");
            while (getchar() != '\n')
                ; // Clear invalid input
            continue;
        }
        if ((*x1 == *x || *y1 == *y) && *x1 >= 0 && *x1 < board->rows && *y1 >= 0 && *y1 < board->columns)
        {
            valid = 1;
        }
        else
        {
            printf("You can only move either on the same row or column inside bounds");
        }
    } while (!valid);
}

/**
 * @brief This function initializes the players' scores to 0 depending on the number of players.
 *
 * @param num_players The number of players participating in the game.
 * @param players An array of Player structures representing the players.
 */
void initializePlayers(int num_players, Player players[])
{
    for (int i = 0; i < num_players; i++)
    {
        players[i].score = 0;
    }
}

/**
 * @brief This function validates the dimensions and total penguin count on the board to see that its possible to squeeze all penguins onto the board.
 *
 * @param board Pointer to the Board structure to be validated.
 * @param num_players The number of players.
 *
 * @return 1 if valid, 0 otherwise.
 */
int validateDimensionsAndPenguins(Board *board, int num_players)
{
    if (board->rows > 0 && board->columns > 0 && board->penguins_per_player * num_players > board->rows * board->columns)
    {
        printf("Invalid parameters\n");
        return 0;
    }
    return 1;
}

/**
 * @brief This function prints the scores of all players.
 *
 * @param players An array of Player structures representing the players.
 * @param num_players The number of players participating in the game.
 */
void printScores(Player players[], int num_players)
{
    printf("\nScores:\n");
    for (int i = 0; i < num_players; i++)
    {
        printf("Player %d score: %d\n", i + 1, players[i].score);
    }
}

/**
 * @brief This function prints the winner of the game.
 *
 * @param players An array of Player structures representing the players.
 * @param num_players The number of players participating in the game.
 */
void summerization(Player players[], int num_players)
{
    int highest = 0;
    int player = 0;
    int occurance = 0;
    for (int i = 0; i < num_players; i++)
    {
        if (players[i].score > highest)
        {
            occurance = 0;
            highest = players[i].score;
            player = i + 1;
        }
        else if (players[i].score == highest)
        {
            occurance++;
        }
    }

    if (occurance == 0)
    {
        printf("Player %d wins with %d points!\n", player, highest);
    }
    else
    {
        printf("It's a tie!\n");
    }
}

/**
 * @brief This function prints the board.
 *
 * @param board Pointer to the Board structure representing the game board.
 */
void showBoard(Board *board)
{
    printf("\n   ");
    for (int j = 0; j < board->columns; j++)
    {
        if (j == 0)
        {
            printf(" ");
        }
        printf("%4d", j); // Print column headers
    }
    printf("\n   ");
    for (int j = 0; j < board->columns + 1; j++)
    {
        printf("----"); // Separator line below headers
    }
    printf("\n");
    for (int i = 0; i < board->rows; i++)
    {
        printf("%2d |", i); // Print row headers
        for (int j = 0; j < board->columns; j++)
        {
            if (board->array[i][j] == 6)
            {
                printf("\033[1;31m%4c\033[0m", 'A'); // Red 'A'
            }
            else if (board->array[i][j] == 7)
            {
                printf("\033[1;34m%4c\033[0m", 'B'); // Blue 'B'
            }
            else if (board->array[i][j] == 8)
            {
                printf("\033[1;33m%4c\033[0m", 'C'); // Yellow 'C'
            }
            else if (board->array[i][j] == 9)
            {
                printf("\033[1;32m%4c\033[0m", 'D'); // Green 'D'
            }
            else
            {
                printf("%4d", board->array[i][j]); // Default case for other numbers
            }
        }
        printf("\n");
    }
}

/**
 * @brief This function frees the memory allocated for the board.
 *
 * @param board Pointer to the Board structure to be initialized.
 */
void freeBoard(Board *board)
{
    for (int i = 0; i < board->rows; i++)
    {
        free(board->array[i]); // Free each row
    }
    free(board->array); // Free the array of row pointers
    board->array = NULL;
    board->rows = 0;
    board->columns = 0;
    board->penguins_per_player = 0;
}

/**
 * @brief This function validates the new coordinates chosen by user.
 *
 * @param board Pointer to the Board structure representing the game board.
 * @param x The x-coordinate of the penguin.
 * @param y The y-coordinate of the penguin.
 *
 * @return 1 if valid, 0 otherwise.
 */
int validateCoordinates(Board *board, int x, int y)
{
    if (x < board->rows && x >= 0 && y < board->columns && y >= 0)
    {
        if (board->array[x][y] == 1)
        {
            return 0;
        }
        else
        {
            printf("Invalid tile selected\n");
            return 1;
        }
    }
    printf("Selected tile is out of bounds\n");
    return 1;
}

/**
 * @brief This function finds the ID of the player.
 *
 * @param board Pointer to the Board structure representing the game board.
 * @param sign An integer symbol denoting the player's penguin.
 *
 * @return 0 if the player can make a move; 1 if all penguins are stuck.
 */
int getMyId(AutonomousPlayer players[], char *name, int num_players)
{
    for (int i = 0; i < num_players; i++)
    {
        if (strcmp(players[i].name, name) == 0)
            return players[i].id;
    }
    return 0;
}

/**
 * @brief This function checks if the player exists or not on the board.
 *
 * @param board Pointer to the Board structure representing the game board.
 * @param sign An integer symbol denoting the player's penguin.
 *
 * @return 0 if the player can make a move; 1 if all penguins are stuck.
 */
int checkPresence(AutonomousPlayer players[], char *name, int num_players)
{

    for (int i = 0; i < num_players; i++)
    {
        if (strcmp(players[i].name, name) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief This function increments the score of the player.
 *
 * @param players An array of AutonomousPlayer objects.
 * @param num_players The number of players in the array.
 * @param id The ID of the player.
 * @param points The points to be added to the player's score.
 */
void incrementScore(AutonomousPlayer players[], int num_players, int id, int points)
{
    for (int i = 0; i < num_players; i++)
    {
        if (players[i].id == id)
        {
            players[i].points += points;
        }
    }
}
