#include <stdio.h>

/**
 * @brief Structure representing the game board.
 * @var columns The number of columns in the game board.
 * @var rows The number of rows in the game board.
 * @var array A 2D array representing the game board.
 * @var penguins_per_player The number of penguins each player has.   
 * @name Board
 */
typedef struct Board{
    int columns;
    int rows;
    int **array;
    int penguins_per_player;
}Board;

/**
 * @brief Structure representing a player in the game.
 * @var score The score of the player.
 * @name Player
 */
typedef struct Player{
    int score;
}Player;

/**
 * @brief Structure representing an autonomous player in the game.
 * @var name The name of the player.
 * @var id The ID of the player.
 * @var points The points of the player.
 * @name AutonomousPlayer
 */
typedef struct AutonomousPlayer{
    char name[50];
    int id;
    int points;
}AutonomousPlayer;