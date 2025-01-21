#ifndef PLACEMENT_H
#define PLACEMENT_H

#include "structs.h"

/**
 * @brief Generates the game board and initializes it based on user input.
 * 
 * This function invokes other functions to ask the user for input and validate it.
 * @param board Pointer to the Board structure to initialize.
 * @param num_player The number of players participating in the game.
 */
void generateBoard(Board* board, int num_player);
    
/**
 * @brief Fills the board with pseudo-random values.
 * 
 * This function handles edge cases to ensure proper board initialization.
 * @param board Pointer to the Board structure representing the game board.
 * @param num_player The number of players participating in the game.
 */
void fillBoard(Board* board, int num_player);

/**
 * @brief Generates a random tile value in the range [0, 3].
 * 
 * This function is used to populate the board with appropriate values.
 * @return An integer representing the generated tile value.
 */    
int generateTile();

/**
 * @brief Places a penguin on the selected tile of the board.
 * 
 * This function ensures necessary validations are performed before placing the penguin.
 * @param board Pointer to the Board structure representing the game board.
 * @param x The x-coordinate of the tile on the board.
 * @param y The y-coordinate of the tile on the board.
 * @param sign An integer symbol denoting the player's penguin (e.g., 8 or 9).
 */    
void placePenguin(Board* board,int x, int y, int sign);

/**
 * @brief Places a penguin autonomously on the board using logic.
 * 
 * This function places a penguin on the board autonomously.
 * @param board Pointer to the Board structure representing the game board.
 * @param my_id Integer value representing the id of the program.
 * @param num_players Integer value representing the number of players in the game.
 */ 
void placeAutonomously(AutonomousPlayer players[],Board* board,int my_id,int num_players);

/**
 * @brief Checks whether the program can place a penguin, taking into account the upper limit of penguin.
 * 
 * This function places a penguin on the board autonomously.
 * @param board Pointer to the Board structure representing the game board.
 * @param my_id Integer value representing the id of the program.
 * @param penguins_to_place Integer value storing information about number of penguins per player.
 */ 
int checkPenguinsToPlace(Board* board,int penguins_to_place,int my_id);

#endif