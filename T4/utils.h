#ifndef UTILS_H
#define UTILS_H

#include "structs.h"

/**
 * @brief Clears the console screen.
 */
void ClearConsole();

/**
 * @brief Waits for the user to press Enter.
 */
void WaitForEnter();

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
void AskForDimensions(Board* board);

/**
 * @brief Prompts the user to specify the number of penguins per player.
 * @param board Pointer to the board structure.
 */
void AskForPenguins(Board* board);

/**
 * @brief Validates the dimensions and total penguin count on the board.
 * @param board Pointer to the board structure.
 * @param numPlayer The number of players.
 * @return 1 if valid, 0 otherwise.
 */
int ValidateDimensionsAndPenguins(Board* board, int numPlayer);

/**
 * @brief Prompts the user to enter coordinates for placing a penguin.
 * @param x Pointer to the x-coordinate.
 * @param y Pointer to the y-coordinate.
 */
void AskForCoordinates(int* x, int* y);

/**
 * @brief Validates the provided coordinates for placing a penguin.
 * @param board Pointer to the board structure.
 * @param x The x-coordinate to validate.
 * @param y The y-coordinate to validate.
 * @return 1 if valid, 0 otherwise.
 */
int ValidateCoordinates(Board* board, int x, int y);

/**
 * @brief Prompts the user to specify a penguin to move.
 * @param x Pointer to the x-coordinate of the penguin.
 * @param y Pointer to the y-coordinate of the penguin.
 * @param sign The player's penguin identifier.
 * @param board Pointer to the board structure.
 */
void AskForCoordinatesOfPenguin(int *x, int *y, int sign, Board* board);

/**
 * @brief Prompts the user to specify movement coordinates for a penguin.
 * @param x Pointer to the x-coordinate of the penguin.
 * @param y Pointer to the y-coordinate of the penguin.
 * @param x1 Pointer to the new x-coordinate of the penguin.
 * @param y1 Pointer to the new y-coordinate of the penguin.
 * @param sign The player's penguin identifier.
 * @param board Pointer to the board structure.
 */
void AskForCoordinatesMovement(int *x, int *y, int *x1, int *y1, int sign, Board* board);

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
void ShowBoard(Board* board);

/**
 * @brief Frees the dynamically allocated memory for the game board.
 * @param board Pointer to the board structure.
 */
void FreeBoard(Board* board);

#endif
