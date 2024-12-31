#ifndef structs_h
#define structs_h


typedef struct Board{
    int columns;    //amount of columns of the board
    int rows;       //amount of rows of the board
    int **array;    //pointer to 2D matrix
    int penguins_per_player;//amount of penguins each player has
}Board; //Structure containing neccessary information for board operations and validations


#endif