#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "file_handling.h"
#include "placement.h"
#include "movement.h"
#include "structs.h"

void test_board_initialization() {
    Board board;
    board.rows = 3;
    board.columns = 3;
    board.penguins_per_player = 2;

    board.array = malloc(board.rows * sizeof(int *));
    for (int i = 0; i < board.rows; i++) {
        board.array[i] = malloc(board.columns * sizeof(int));
    }

    fillBoard(&board, 2);

    for (int i = 0; i < board.rows; i++) {
        for (int j = 0; j < board.columns; j++) {
            if (!(board.array[i][j] >= 0 && board.array[i][j] <= 3)) {
                printf("test_board_initialization failed\n");
                return;
            }
        }
    }

    freeBoard(&board);
    printf("test_board_initialization passed\n");
}

void test_validate_move() {
    Board board;
    board.rows = 3;
    board.columns = 3;

    board.array = malloc(board.rows * sizeof(int *));
    for (int i = 0; i < board.rows; i++) {
        board.array[i] = malloc(board.columns * sizeof(int));
    }

    board.array[0][0] = 6;
    board.array[1][0] = 2;
    board.array[2][0] = 0;

    if (validateMove(&board, 0, 0, 1, 0) != 0 || validateMove(&board, 0, 0, 2, 0) != 1) {
        printf("test_validate_move failed\n");
        return;
    }

    freeBoard(&board);
    printf("test_validate_move passed\n");
}

void test_increment_score() {
    AutonomousPlayer players[2] = {
        {"Player1", 1, 0},
        {"Player2", 2, 0}
    };

    incrementScore(players, 2, 1, 3);
    if (players[0].points != 3) {
        printf("test_increment_score failed\n");
        return;
    }

    incrementScore(players, 2, 2, 5);
    if (players[1].points != 5) {
        printf("test_increment_score failed\n");
        return;
    }

    printf("test_increment_score passed\n");
}

void test_check_presence() {
    AutonomousPlayer players[2] = {
        {"Player1", 1, 10},
        {"Player2", 2, 15}
    };

    if (checkPresence(players, "Player1", 2) != 1 || checkPresence(players, "Player3", 2) != 0) {
        printf("test_check_presence failed\n");
        return;
    }

    printf("test_check_presence passed\n");
}

void test_validate_dimensions_and_penguins() {
    Board board;
    board.rows = 3;
    board.columns = 3;
    board.penguins_per_player = 2;

    if (validateDimensionsAndPenguins(&board, 2) != 1) {
        printf("test_validate_dimensions_and_penguins failed\n");
        return;
    }

    board.penguins_per_player = 5;
    if (validateDimensionsAndPenguins(&board, 2) != 0) {
        printf("test_validate_dimensions_and_penguins failed\n");
        return;
    }

    printf("test_validate_dimensions_and_penguins passed\n");
}

void test_validate_board_dimensions() {
    Board board;
    board.rows = 10;
    board.columns = 10;

    if (validateBoardDimensions(&board) != 1) {
        printf("test_validate_board_dimensions failed\n");
        return;
    }

    board.rows = 0;
    if (validateBoardDimensions(&board) != 0) {
        printf("test_validate_board_dimensions failed\n");
        return;
    }

    board.columns = 0;
    if (validateBoardDimensions(&board) != 0) {
        printf("test_validate_board_dimensions failed\n");
        return;
    }

    printf("test_validate_board_dimensions passed\n");
}

void test_validate_player_data() {
    AutonomousPlayer players[2] = {
        {"Player1", 1, 10},
        {"Player2", 2, 15}
    };

    if (validatePlayerData(players, 2) != 1) {
        printf("test_validate_player_data failed\n");
        return;
    }

    players[1].id = -1;
    if (validatePlayerData(players, 2) != 0) {
        printf("test_validate_player_data failed\n");
        return;
    }

    players[1].id = 2;
    players[1].points = -5;
    if (validatePlayerData(players, 2) != 0) {
        printf("test_validate_player_data failed\n");
        return;
    }

    printf("test_validate_player_data passed\n");
}

void test_can_move() {
    Board board;
    board.rows = 3;
    board.columns = 3;

    board.array = malloc(board.rows * sizeof(int *));
    for (int i = 0; i < board.rows; i++) {
        board.array[i] = malloc(board.columns * sizeof(int));
    }

    AutonomousPlayer players[2] = {
        {"Player1", -1, 0},
        {"Player2", -2, 0}
    };

    board.array[0][0] = -1;
    board.array[1][0] = 2;
    board.array[2][0] = 0;

    if (canMove(&board, players, 2, 1) != 1) {
        printf("test_can_move failed\n");
        return;
    }

    board.array[0][0] = 0;
    if (canMove(&board, players, 2, 1) != 0) {
        printf("test_can_move failed\n");
        return;
    }

    freeBoard(&board);
    printf("test_can_move passed\n");
}

void test_check_input_validity() {
    Board board;
    board.rows = 3;
    board.columns = 3;

    board.array = malloc(board.rows * sizeof(int *));
    for (int i = 0; i < board.rows; i++) {
        board.array[i] = malloc(board.columns * sizeof(int));
    }

    AutonomousPlayer players[2] = {
        {"Player1", -1, 10},
        {"Player2", -2, 15}
    };

    for (int i = 0; i < board.rows; i++) {
        for (int j = 0; j < board.columns; j++) {
            board.array[i][j] = 1;
        }
    }

    if (checkInputValidity(&board) != 1) {
        printf("test_check_input_validity failed\n");
        return;
    }

    board.array[0][0] = 100;
    if (checkInputValidity(&board) != 0) {
        printf("test_check_input_validity failed\n");
        return;
    }

    freeBoard(&board);
    printf("test_check_input_validity passed\n");
}

int main() {
    test_board_initialization();
    test_validate_move();
    test_increment_score();
    test_check_presence();
    test_validate_dimensions_and_penguins();
    test_validate_board_dimensions();
    test_validate_player_data();
    test_can_move();
    test_check_input_validity();

    printf("All tests passed!\n");
    return 0;
}
