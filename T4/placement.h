#ifndef PLACEMENT_H
#define PLACEMENT_H

#include "structs.h"

/**
 * @brief Generates the game board and initializes it based on user input.
 * 
 * This function invokes other functions to ask the user for input and validate it.
 * @param board Pointer to the Board structure to initialize.
 * @param numPlayer The number of players participating in the game.
 */
void GenerateBoard(Board* board, int numPlayer);
    
/**
 * @brief Fills the board with pseudo-random values.
 * 
 * This function handles edge cases to ensure proper board initialization.
 * @param board Pointer to the Board structure representing the game board.
 * @param numPlayer The number of players participating in the game.
 */
void FillBoard(Board* board, int numPlayer);

/**
 * @brief Generates a random tile value in the range [0, 3].
 * 
 * This function is used to populate the board with appropriate values.
 * @return An integer representing the generated tile value.
 */    
int GenerateTile();

/**
 * @brief Places a penguin on the selected tile of the board.
 * 
 * This function ensures necessary validations are performed before placing the penguin.
 * @param board Pointer to the Board structure representing the game board.
 * @param x The x-coordinate of the tile on the board.
 * @param y The y-coordinate of the tile on the board.
 * @param sign An integer symbol denoting the player's penguin (e.g., 8 or 9).
 */    
void PlacePenguin(Board* board,int x, int y, int sign);

#endif