#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include "structs.h"


/**
 * @brief Reads the game board and player information from a file.
 * 
 * This function reads the contents of the specified file and initializes the game board
 * and player information based on the file data.
 * 
 * @param board A pointer to the Board structure that will be initialized with the file data.
 * @param file_name A string representing the name of the file to be read.
 * @param players A pointer to an array of AutonomousPlayer pointers that will be initialized with the player data.
 * @param num_players A pointer to an integer that will be set to the number of players read from the file.
 */
void ReadFile(Board* board,char* file_name, AutonomousPlayer **players, int* num_players);

/**
 * @brief Writes the current state of the board and player information to a file.
 * 
 * @param board Pointer to the Board object containing the game state.
 * @param filename The name of the file to write the data to.
 * @param players Array of AutonomousPlayer objects representing the players.
 * @param num_players The number of players in the players array.
 */
void WriteFile(Board* board,char* filename, AutonomousPlayer players[], int num_players);

/**
 * @brief Interprets a value read from a token.
 * 
 * This function takes a character pointer to a token and interprets its value.
 * The interpretation logic is defined within the function.
 * 
 * @param token A character pointer to the token to be interpreted.
 * @return An integer representing the interpreted value of the token.
 */
int interpretValueRead(char* token);

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
int interpretValueWrite(int value);

/**
 * @brief Checks the validity of the input on the given board.
 * 
 * This function verifies whether the input provided to the board is valid
 * according to the game's rules and constraints.
 * 
 * @param board A pointer to the Board object that needs to be checked.
 * @return An integer indicating the validity of the input. Typically, 
 *         a non-zero value indicates invalid input, while zero indicates valid input.
 */
int CheckInputValidity(Board* board);

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
int AssignId(AutonomousPlayer players[],int num_players);

/**
 * @brief Appends player information to the specified output file.
 * 
 * This function takes the name of an output file, a player's name, and their ID,
 * and appends the player's information to the file.
 * 
 * @param OutputFileName The name of the file to which the player's information will be appended.
 * @param name The name of the player to be appended.
 * @param my_id The ID of the player to be appended.
 */
void AppendMyPlayer(char* OutputFileName,char* name, int my_id);
#endif