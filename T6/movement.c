/**
 * @file movement.c
 * @author Team D
 * @brief This file contains the implementation of functions for moving penguins on the game board.
 * @date 2025-01-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "movement.h"
#include "utils.h"

/**
 * @brief This function moves a penguin to a new tile on the board after performing validations.
 *
 * @param board Pointer to the Board structure representing the game board.
 * @param x Pointer to the x-coordinate of the penguin's current location.
 * @param y Pointer to the y-coordinate of the penguin's current location.
 * @param x1 Pointer to the x-coordinate of the penguin's new location.
 * @param y1 Pointer to the y-coordinate of the penguin's new location.
 * @param sign An integer symbol denoting the player's penguin.
 */
void movePenguin(Board *board, int *x, int *y, int *x1, int *y1, int sign)
{
    int newX = *x1;
    int newY = *y1;
    int oldX = *x;
    int oldY = *y;
    board->array[newX][newY] = sign;
    board->array[oldX][oldY] = 0;
}

/**
 * @brief This function validates the move and places the penguin at the specified new location.
 *
 * This function validates the move by checking if the path is blocked and if the penguin is moving in a straight line in 4 directions.
 *
 * @param board Pointer to the Board structure representing the game board.
 * @param x Pointer to the x-coordinate of the penguin's current location.
 * @param y Pointer to the y-coordinate of the penguin's current location.
 * @param x1 Pointer to the x-coordinate of the penguin's new location.
 * @param y1 Pointer to the y-coordinate of the penguin's new location.
 * @param sign An integer symbol denoting the player's penguin.
 * @return 1 if valid, 0 otherwise.
 */
int validateMove(Board *board, int x, int y, int x1, int y1)
{
    if (x == x1 && y == y1)
    {
        printf("Penguin unselected, choose another penguin");
        return 1;
    }

    if (x1 > x)
    {
        for (int i = x + 1; i <= x1; i++)
        {
            if (board->array[i][y1] == 0 || board->array[i][y1] == 6 || board->array[i][y1] == 7 || board->array[i][y1] == 8 || board->array[i][y1] == 9)
            {
                printf("Path is blocked, choose another coordinate to move to\n");
                return 1;
            }
        }
        return 0;
    }

    if (x1 < x)
    {
        for (int i = x - 1; i >= x1; i--)
        {
            if (board->array[i][y1] == 0 || board->array[i][y1] == 6 || board->array[i][y1] == 7 || board->array[i][y1] == 8 || board->array[i][y1] == 9)
            {
                printf("Path is blocked, choose another coordinate to move to\n");
                return 1;
            }
        }
        return 0;
    }

    if (y1 > y)
    {
        for (int i = y + 1; i <= y1; i++)
        {
            if (board->array[x1][i] == 0 || board->array[x1][i] == 6 || board->array[x1][i] == 7 || board->array[x1][i] == 8 || board->array[x1][i] == 9)
            {
                printf("Path is blocked, choose another coordinate to move to\n");
                return 1;
            }
        }
        return 0;
    }

    if (y1 < y)
    {
        for (int i = y - 1; i >= y1; i--)
        {
            if (board->array[x1][i] == 0 || board->array[x1][i] == 6 || board->array[x1][i] == 7 || board->array[x1][i] == 8 || board->array[x1][i] == 9)
            {
                printf("Path is blocked, choose another coordinate to move to\n");
                return 1;
            }
        }
        return 0;
    }
}

/**
 * @brief This function checks if a penguin can make a valid move from its current location.
 *
 * This function verifies the surrounding tiles of the penguin to determine if a move is possible.
 *
 * @param i The x-coordinate of the penguin's current location.
 * @param j The y-coordinate of the penguin's current location.
 * @param board Pointer to the Board structure representing the game board.
 * @return 0 if the penguin can move; 1 if it is stuck.
 */
int checkSurrounding(int i, int j, Board *board)
{
    // Check if the penguin can move to any of the four adjacent cells
    if (i + 1 < board->rows && (board->array[i + 1][j] == 1 || board->array[i + 1][j] == 2 || board->array[i + 1][j] == 3))
        return 0; // Down
    if (i - 1 >= 0 && (board->array[i - 1][j] == 1 || board->array[i - 1][j] == 2 || board->array[i - 1][j] == 3))
        return 0; // Up
    if (j + 1 < board->columns && (board->array[i][j + 1] == 1 || board->array[i][j + 1] == 2 || board->array[i][j + 1] == 3))
        return 0; // Right
    if (j - 1 >= 0 && (board->array[i][j - 1] == 1 || board->array[i][j - 1] == 2 || board->array[i][j - 1] == 3))
        return 0; // Left
    return 1;
}

/**
 * @brief This function checks if a player is completely stuck and unable to move any penguin for the autonomous mode.
 *
 * This function iterates through the player's penguins to determine if all are immobile.
 *
 * @param board Pointer to the Board structure representing the game board.
 * @param sign An integer symbol denoting the player's penguin.
 * @return 0 if the player can make a move; 1 if all penguins are stuck.
 */
int checkStuckAutomatically(Board *board, int sign)
{
    int total_counter = 0;
    int penguins = 0;
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->columns; j++)
        {
            if (board->array[i][j] == sign)
            {
                penguins++;
                if (checkSurrounding(i, j, board) == 0)
                {
                    continue;
                }
                else
                {
                    total_counter++;
                }
            }
        }
    }
    if (total_counter == penguins)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief This function checks if a player is completely stuck and unable to move any penguin for the PvP mode.
 *
 * This function iterates through the player's penguins to determine if all are immobile.
 *
 * @param board Pointer to the Board structure representing the game board.
 * @param sign An integer symbol denoting the player's penguin.
 * @return 0 if the player can make a move; 1 if all penguins are stuck.
 */
int checkStuck(Board *board, int sign)
{
    int total_counter = 0;
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->columns; j++)
        {
            if (board->array[i][j] == sign)
            {
                if (checkSurrounding(i, j, board) == 0)
                {
                    continue;
                }
                else
                {
                    total_counter++;
                }
            }
        }
    }

    if (total_counter == board->penguins_per_player)
    {
        printf("\nPlayer %d can not move.\n", sign - 5);
        return 1;
    }
    else
    {
        printf("\nPlayer %d can move.\n", sign - 5);
        return 0;
    }
}

/**
 * @brief This function moves the penguin autonomously using logic.
 *
 * This function iterates through the 2D array to find the best move in the current game state. it Utilizes the checkStuckAutomatically function
 *
 * @param board Pointer to the Board structure representing the game board with interpreted values from input file.
 * @param players Pointer to the AutonomousPlayer structure representing the players in the game.
 * @param num_players The number of players in the game.
 * @param my_id The ID of the player running the program.
 */
int canMove(Board *board, AutonomousPlayer *players, int num_players, int my_id)
{
    for (int i = 0; i < num_players; i++)
    {
        if (players[i].id == (-1) * my_id && checkStuckAutomatically(board, (-1) * players[i].id) == 0)
        {
            return 1; // A player can move
        }
    }
    return 0; // players cannot move
}

/**
 * @brief This function moves the penguin autonomously using logic.
 *
 * This function iterates through the 2D array to find the best move in the current game state by checking the fish on and around the floes. It checks in 4 directions
 * for the best move, then checks again around that new best move location to find potentially more fish, if the total comes back as the best move, the penguin is moved.
 *
 * @param board Pointer to the Board structure representing the game board with interpreted values from input file.
 * @param players Pointer to the AutonomousPlayer structure representing the players in the game.
 * @param num_players The number of players in the game.
 * @param my_id The ID of the player running the program.
 */
void moveAutonomously(Board *board, AutonomousPlayer *players, int num_players, int my_id)
{
    int best_i = -1, best_j = -1, best_x = -1, best_y = -1;
    int max_fish = 0, max_surrounding_fish = 0; // the floes with the most fish on and around them
    // Iterate through the board to find the best move
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->columns; j++)
        {
            if (board->array[i][j] == my_id) // Check if the floe has our penguin
            {
                int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Down, Up, Right, Left respectively
                for (int d = 0; d < 4; d++)                                // Check all four directions
                {
                    int step = 1;
                    while (1)
                    {
                        int x = i + step * directions[d][0];                                                     // Checking the floe in the new coordinates
                        int y = j + step * directions[d][1];                                                     // Checking the floe in the new coordinates
                        if (x >= 0 && x < board->rows && y >= 0 && y < board->columns && board->array[x][y] > 0) // Validating the new coordinates are within the board and have fish
                        {
                            int fish = board->array[x][y];                                         // the number of fish on the floe
                            int surrounding_fish = 0;                                              // check the surrounding amount fish
                            int surrounding_directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Down, Up, Right, Left respectively
                            for (int sd = 0; sd < 4; sd++)
                            {
                                int sx = x + surrounding_directions[sd][0];                                                    // Checking the fish around the new coordinates
                                int sy = y + surrounding_directions[sd][1];                                                    // Checking the fish around the new coordinates
                                if (sx >= 0 && sx < board->rows && sy >= 0 && sy < board->columns && board->array[sx][sy] > 0) // Validating the surrounding fish are within the board
                                {
                                    surrounding_fish += board->array[sx][sy]; // totaling the surrounding fish
                                }
                            }
                            if (fish > max_fish || (fish == max_fish && surrounding_fish > max_surrounding_fish)) // Comparing to find the best move
                            {
                                // Update the best move
                                max_fish = fish;
                                max_surrounding_fish = surrounding_fish;
                                best_i = i;
                                best_j = j;
                                best_x = x;
                                best_y = y;
                            }
                        }
                        else
                        {
                            break; // Stop if the floe is out of bounds or has no fish
                        }
                        step++;
                    }
                }
            }
        }
    }

    if (best_i != -1 && best_j != -1 && best_x != -1 && best_y != -1)
    {
        // Move the penguin
        board->array[best_x][best_y] = my_id; // Moving the penguin to the new coordinates
        board->array[best_i][best_j] = 0;     // Removing the penguin from the old coordinates
        // Add the collected fish to the player's points
        for (int i = 0; i < num_players; i++)
        {
            if (players[i].id == (-1) * my_id)
            {
                players[i].points += max_fish;
                break;
            }
        }
        // debugging
        // printf("Player %d moved penguin from (%d, %d) to (%d, %d) and gained %d points.\n", my_id, best_i, best_j, best_x, best_y, max_fish);
    }
}