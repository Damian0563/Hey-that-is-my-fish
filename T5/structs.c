#include <stdio.h>

typedef struct Board{
    int columns;
    int rows;
    int **array;
    int penguins_per_player;
}Board;

typedef struct Player{
    int score;
}Player;

typedef struct AutonomousPlayer{
    char name[50];
    int id;
    int points;
}AutonomousPlayer;