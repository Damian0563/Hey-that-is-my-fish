#ifndef STRUCTS_H
#define STRUCTS_H

/**
 * @brief Structure representing the game board.
 * 
 * This structure contains all the necessary information 
 * required for board operations and validations.
 */
typedef struct Board {
    int columns; /**< The number of columns on the board. */
    int rows;    /**< The number of rows on the board. */
    int **array; /**< Pointer to a dynamically allocated 2D matrix representing the board. */
    int penguins_per_player; /**< The number of penguins allocated to each player. */
} Board;

/**
 * @brief Structure representing a player in the game.
 * 
 * This structure contains information about the player's score.
 */
typedef struct Player {
    int score; /**< The total score of the player. */
} Player;

#endif /* STRUCTS_H */
