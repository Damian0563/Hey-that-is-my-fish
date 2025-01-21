/**
 * @file file_handling.c
 * @author Team D
 * @brief This file contains the implementation of functions for accessing and editing input/output files
 * @date 2025-01-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_handling.h"
#include "movement.h"
#include "structs.h"
#include "utils.h"
#include "placement.h"

/**
 * @brief Reads the game board and player information from a file.
 *
 * This function reads the contents of the specified file and initializes the game board
 *
 * @param board a pointer to the Board structure that will be initialized with the file data.
 * @param file_name a string representing the name of the file to be read.
 * @param players a pointer to an array of AutonomousPlayer pointers that will be initialized with the player data.
 * @param num_players a pointer to an integer that will be set to the number of players read from the file.
 * @return void
 */
void readFile(Board *board, char *file_name, AutonomousPlayer **players, int *num_players)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(2); // Critical error: terminate program.
    }

    char buffer[1023];
    int row_index = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        buffer[strcspn(buffer, "\r\n")] = '\0'; // Strip newline characters.

        if (row_index == 0)
        {
            // Read and validate board dimensions.
            char *token = strtok(buffer, " ");
            if (token == NULL)
            {
                printf("Error: Missing board dimensions.\n");
                exit(2); // Critical error: terminate program.
            }
            board->rows = atoi(token);
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("Error: Missing board dimensions.\n");
                exit(2); // Critical error: terminate program.
            }
            board->columns = atoi(token);

            if (!validateBoardDimensions(board))
            {
                printf("Error: Invalid board dimensions.\n");
                exit(2); // Critical error: terminate program.
            }

            board->array = malloc(board->rows * sizeof(int *));
            for (int i = 0; i < board->rows; i++)
            {
                board->array[i] = malloc(board->columns * sizeof(int));
            }
        }
        else if (row_index <= board->rows)
        {
            // Read board contents.
            char *token = strtok(buffer, " ");
            for (int col_index = 0; col_index < board->columns; col_index++)
            {
                if (token == NULL)
                {
                    printf("Warning: Missing data in row %d.\n", row_index);
                    exit(2);
                }
                board->array[row_index - 1][col_index] = interpretValueRead(token);
                token = strtok(NULL, " ");
            }
        }
        else
        {
            // Read player data.
            AutonomousPlayer *temp = malloc((*num_players + 1) * sizeof(AutonomousPlayer));
            if (temp == NULL)
            {
                perror("Memory allocation failed for players");
                exit(2); // Critical error: terminate program.
            }
            memcpy(temp, *players, *num_players * sizeof(AutonomousPlayer));
            free(*players);
            *players = temp;

            char *token = strtok(buffer, " ");
            if (token == NULL)
            {
                printf("Warning: Missing player name.\n");
                exit(2); // Terminate due to critical error.
            }
            strncpy((*players)[*num_players].name, token, sizeof((*players)[*num_players].name) - 1);
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("Warning: Missing player ID.\n");
                exit(2); // Terminate due to critical error.
            }
            (*players)[*num_players].id = atoi(token);
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("Warning: Missing player points.\n");
                exit(2); // Terminate due to critical error.
            }
            (*players)[*num_players].points = atoi(token);
            (*num_players)++;
        }

        row_index++;
    }

    fclose(file);

    // Final validation.
    if (!validatePlayerData(*players, *num_players))
    {
        printf("Error: Invalid player data.\n");
        exit(2); // Critical error: terminate program.
    }
}

/**
 * @brief Validates the input data read from the file.
 *
 * This function validates the input data read from the file. It checks the board dimensions
 *
 * @param board A pointer to the Board structure to be validated.
 * @return int
 */
int checkInputValidity(Board *board)
{
    if (board == NULL || board->rows <= 0 || board->columns <= 0)
    {
        fprintf(stderr, "Error: Invalid board structure.\n");
        return 0; // Invalid input.
    }

    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->columns; j++)
        {
            if (board->array[i][j] > 3 || board->array[i][j] < -9)
            {
                printf("Error: Invalid value at row %d, column %d.\n", i, j);
                return 0; // Invalid value detected.
            }
        }
    }

    return 1; // Input is valid.
}

/**
 * @brief Validates the dimensions of the given board.
 *
 * @param board A pointer to the Board structure to be validated.
 * @return int Returns 0 if the dimensions are valid, otherwise returns an error code.
 */
int validateBoardDimensions(Board *board)
{
    return (board->rows > 0 && board->columns > 0 && board->rows <= 100 && board->columns <= 100);
}

/**
 * @brief Validates the data of autonomous players.
 *
 * This function checks the validity of the data for a given array of
 * AutonomousPlayer structures. It ensures that the data meets the
 * required criteria and returns a status code indicating the result
 * of the validation.
 *
 * @param players Pointer to an array of AutonomousPlayer structures.
 * @param num_players The number of players in the array.
 * @return int Status code indicating the result of the validation:
 *         - 0: Validation successful.
 *         - 1: Validation failed due to invalid data.
 */
int validatePlayerData(const AutonomousPlayer *players, int num_players)
{
    for (int i = 0; i < num_players; i++)
    {
        if (players[i].id <= 0 || players[i].id > 9 || strlen(players[i].name) == 0 || players[i].points < 0)
        {
            printf("Error: Invalid data for player %d.\n", i);
            return 0; // Invalid player data.
        }
    }
    return 1; // All player data is valid.
}

/**
 * @brief Appends player information to the specified output file.
 *
 * This function takes the name of an output file, a player's name, and their ID,
 * and appends the player's information to the file.
 *
 * @param output_file_name The name of the file to which the player's information will be appended.
 * @param name The name of the player to be appended.
 * @param my_id The ID of the player to be appended.
 * @param num_players number of players.
 */
void appendMyPlayer(char *output_file_name, char *name, int my_id, int num_players)
{
    FILE *pf = fopen(output_file_name, "a");
    if (num_players != 0)
    {
        fprintf(pf, "\n");
    }
    fprintf(pf, "%s %d 1", name, my_id);
    fclose(pf);
}

/**
 * @brief Assigns unique IDs to an array of AutonomousPlayer objects.
 *
 * This function iterates through the provided array of AutonomousPlayer objects
 * and assigns a unique ID to each player. The IDs are assigned sequentially starting
 * from 1 up to the number of players.
 *
 * @param players An array of AutonomousPlayer objects to which IDs will be assigned.
 * @param num_players The number of players in the array.
 * @return The number of players that were successfully assigned an ID.
 */
int assignId(AutonomousPlayer players[], int num_players)
{
    for (int i = 1; i < 10; i++)
    {
        int flag = 1;
        for (int j = 0; j < num_players; j++)
        {
            if (players[j].id == i)
            {
                flag = 0;
            }
        }
        if (flag)
        {
            return i;
        }
    }
    return 10;
}

/**
 * @brief Interprets the given token and returns the corresponding integer value.
 *
 * This function takes a token as input, interprets it according to the
 * implementation, and returns the corresponding integer value.
 *
 * @param token The token to be interpreted.
 * @return An integer representing the interpreted value.
 */
int interpretValueRead(char *token)
{
    if (strcmp(token, "00") == 0)
    {
        return 0;
    }
    else if (strcmp(token, "10") == 0 || strcmp(token, "20") == 0 || strcmp(token, "30") == 0)
    {
        return atoi(token) / 10;
    }
    else if (strlen(token) <= 1)
    {
        printf("Invalid value detected on a tile, changing tile value to 0");
        return 0;
    }
    else if (atoi(token) >= 11 && atoi(token) <= 39)
    {
        if (atoi(token) >= 11 && atoi(token) < 20)
            return -(atoi(token) - 10);
        if (atoi(token) >= 21 && atoi(token) < 30)
            return -(atoi(token) - 20);
        else
            return -(atoi(token) - 30);
    }
    else
    {
        return -atoi(token);
    }
}

/**
 * @brief Interprets the given value and writes it to a specific destination.
 *
 * This function takes an integer value as input, processes it according to
 * the implementation, and writes the interpreted result to a predefined
 * destination (e.g., a file, a buffer, etc.).
 *
 * @param value The integer value to be interpreted and written.
 * @return An integer indicating the success or failure of the operation.
 *         Typically, a return value of 0 indicates success, while a non-zero
 *         value indicates an error.
 */
int interpretValueWrite(int value)
{
    if (value == 0)
    {
        return 0;
    }
    else if (value == 1 || value == 2 || value == 3)
    {
        value = value * 10;
        return value;
    }
    else
    {
        return abs(value);
    }
}

/**
 * @brief Writes the game board and player information to a file.
 *
 * @param board
 * @param file_name
 * @param players
 * @param num_players
 */
void writeFile(Board *board, char *file_name, AutonomousPlayer players[], int num_players)
{
    FILE *file = fopen(file_name, "w+");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%d %d\n", board->rows, board->columns);
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->columns; j++)
        {
            fprintf(file, "%02d ", interpretValueWrite(board->array[i][j]));
        }
        fprintf(file, "\n");
    }
    for (int i = 0; i < num_players; i++)
    {
        if (i == num_players - 1)
        {
            fprintf(file, "%s %d %d", players[i].name, players[i].id, players[i].points);
            break;
        }
        fprintf(file, "%s %d %d\n", players[i].name, players[i].id, players[i].points);
    }

    fclose(file);
}
