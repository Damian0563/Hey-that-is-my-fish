#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "structs.h"

/**
 * @brief Moves a penguin to a new tile on the board after performing validations.
 * 
 * This function validates the move and places the penguin at the specified new location.
 * @param board Pointer to the Board structure representing the game board.
 * @param x Pointer to the x-coordinate of the penguin's current location.
 * @param y Pointer to the y-coordinate of the penguin's current location.
 * @param x1 Pointer to the x-coordinate of the penguin's new location.
 * @param y1 Pointer to the y-coordinate of the penguin's new location.
 * @param sign An integer symbol denoting the player's penguin (e.g., 8 or 9).
 */
void MovePenguin(Board* board,int *x, int *y, int *x1, int *y1, int sign);
    
/**
 * @brief Moves a penguin to a new tile on the board after performing validations.
 * 
 * This function validates the move and places the penguin at the specified new location.
 * @param board Pointer to the Board structure representing the game board.
 * @param x Pointer to the x-coordinate of the penguin's current location.
 * @param y Pointer to the y-coordinate of the penguin's current location.
 * @param x1 Pointer to the x-coordinate of the penguin's new location.
 * @param y1 Pointer to the y-coordinate of the penguin's new location.
 * @param sign An integer symbol denoting the player's penguin (e.g., 8 or 9).
 */
int ValidateMove(Board* board,int x, int y,int x1,int y1);

/**
 * @brief Checks if a penguin can make a valid move from its current location.
 * 
 * This function verifies the surrounding tiles of the penguin to determine if a move is possible.
 * @param i The x-coordinate of the penguin's current location.
 * @param j The y-coordinate of the penguin's current location.
 * @param board Pointer to the Board structure representing the game board.
 * @return 0 if the penguin can move; 1 if it is stuck.
 */
int CheckSurrounding(int i, int j, Board* board);

/**
 * @brief Checks if a player is completely stuck and unable to move any penguin.
 * 
 * This function iterates through the player's penguins to determine if all are immobile.
 * @param board Pointer to the Board structure representing the game board.
 * @param sign An integer symbol denoting the player's penguin (e.g., 8 or 9).
 * @return 0 if the player can make a move; 1 if all penguins are stuck.
 */
int CheckStuck(Board* board,int sign);

/**
 * @brief Moves the penguin autonomously using logic.
 * 
 * This function iterates through the 2D array to find the best move in the current game state.
 * @param board Pointer to the Board structure representing the game board with interpreted values from input file.
 * @param players Pointer to the AutonomousPlayer structure representing the players in the game.
 * @param num_players The number of players in the game.
 * @param my_id The ID of the player running the program.
 */
void MoveAutonomously(Board* board, AutonomousPlayer* players, int num_players, int my_id);

/**
 * @brief Checks if our program can make a move.
 * 
 * This function iterates through the Board structure to check whether penguins of our program are moveable.
 * @param board Pointer to the Board structure representing the game board with interpreted values from input file.
 * @param players Pointer to the AutonomousPlayer structure representing the players in the game.
 * @param num_players The number of players in the game.
 * @param my_id The ID of the player running the program.
 * @return 0 if can not make a move; 1 otherwise
 */
int CanMove(Board* board, AutonomousPlayer* players, int num_players, int my_id);


/**
 * @brief Checks if a player is stuck automatically.
 *
 * This function determines if a player, represented by the given sign, is stuck on the board.
 *
 * @param board Pointer to the Board object.
 * @param sign Integer representing the player's sign.
 * @return int Returns 1 if the player is stuck, 0 otherwise.
 */
int checkStuckAutomatically(Board *board, int sign);

#endif