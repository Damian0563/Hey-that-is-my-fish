#ifndef UTILS_H
#define UTILS_H

#include "structs.h"

/**
 * @brief Prompts the user to enter the number of players.
 * @param numPlayer The initial number of players.
 * @return The validated number of players.
 */
int askForPlayers(int numPlayer);

/**
 * @brief Initializes players with their respective scores.
 * @param numPlayer The number of players.
 * @param players Array of players to be initialized.
 */
void initializePlayers(int numPlayer, Player players[]);

/**
 * @brief Prompts the user to specify the dimensions of the board.
 * @param board Pointer to the board structure.
 */
void askForDimensions(Board* board);

/**
 * @brief Prompts the user to specify the number of penguins per player.
 * @param board Pointer to the board structure.
 */
void askForPenguins(Board* board);

/**
 * @brief Validates the dimensions and total penguin count on the board.
 * @param board Pointer to the board structure.
 * @param numPlayer The number of players.
 * @return 1 if valid, 0 otherwise.
 */
int validateDimensionsAndPenguins(Board* board, int numPlayer);

/**
 * @brief Prompts the user to enter coordinates for placing a penguin.
 * @param x Pointer to the x-coordinate.
 * @param y Pointer to the y-coordinate.
 */
void askForCoordinates(int* x, int* y);

/**
 * @brief Validates the provided coordinates for placing a penguin.
 * @param board Pointer to the board structure.
 * @param x The x-coordinate to validate.
 * @param y The y-coordinate to validate.
 * @return 1 if valid, 0 otherwise.
 */
int validateCoordinates(Board* board, int x, int y);

/**
 * @brief Prompts the user to specify a penguin to move.
 * @param x Pointer to the x-coordinate of the penguin.
 * @param y Pointer to the y-coordinate of the penguin.
 * @param sign The player's penguin identifier.
 * @param board Pointer to the board structure.
 */
void askForCoordinatesOfPenguin(int *x, int *y, int sign, Board* board);

/**
 * @brief Prompts the user to specify movement coordinates for a penguin.
 * @param x Pointer to the x-coordinate of the penguin.
 * @param y Pointer to the y-coordinate of the penguin.
 * @param x1 Pointer to the new x-coordinate of the penguin.
 * @param y1 Pointer to the new y-coordinate of the penguin.
 * @param sign The player's penguin identifier.
 * @param board Pointer to the board structure.
 */
void askForCoordinatesMovement(int *x, int *y, int *x1, int *y1, int sign, Board* board);

/**
 * @brief Prints the scores of all players.
 * @param players Array of players containing their scores.
 * @param numPlayer The number of players.
 */
void printScores(Player players[], int numPlayer);

/**
 * @brief Displays the winner of the game or announces a tie.
 * @param players Array of players containing their scores.
 * @param numPlayer The number of players.
 */
void summerization(Player players[], int numPlayer);

/**
 * @brief Prints the game board to the screen.
 * @param board Pointer to the board structure.
 */
void showBoard(Board* board);

/**
 * @brief Frees the dynamically allocated memory for the game board.
 * @param board Pointer to the board structure.
 */
void freeBoard(Board* board);

/**
 * @brief Retrieves the ID of a player based on their name.
 * 
 * @param players Array of AutonomousPlayer objects.
 * @param name The name of the player whose ID is to be retrieved.
 * @param num_players The number of players in the array.
 * @return int The ID of the player if found, otherwise -1.
 */
int getMyId(AutonomousPlayer players[],char* name, int num_players);


/**
 * @brief Checks the presence of a player in the list of autonomous players.
 * 
 * @param players Array of AutonomousPlayer objects.
 * @param name Name of the player to check for presence.
 * @param num_players Number of players in the array.
 * @return int Returns 1 if the player is present, 0 otherwise.
 */
int checkPresence(AutonomousPlayer players[],char* name,int num_players);

/**
 * @brief Increments the score of a specified player.
 * 
 * @param players Array of AutonomousPlayer objects.
 * @param num_players Number of players in the array.
 * @param id The ID of the player whose score is to be incremented.
 * @param points The number of points to add to the player's score.
 */
void incrementScore(AutonomousPlayer players[],int num_players,int id,int points);
#endif
