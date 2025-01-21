/**
 * @file main.c
 * @author Team D
 * @brief This file contains the main function and the entry point of the program.
 * @date 2025-01-02
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#define Autonomous
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "placement.h"
#include "movement.h"
#include "utils.h"
#include "structs.h"
#include "file_handling.h"

/**
 * @brief Main function of the program.
 * 
 * This function is the entry point of the program. It handles the game logic
 * and player interactions based on the command line arguments provided.
 * 
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 * @return An integer indicating the success or failure of the program.
 */
int main(int argc, char *argv[])
{
    Board board;
    AutonomousPlayer *players;
    int num_players = 0;
    char *name = "ChillGuys";
    #ifndef Autonomous
        int num_players = 0;
        num_players = askForPlayers(num_players);
        Player players[num_players];
        // Initialize players
        initializePlayers(num_players, players);
        srand(time(NULL));
        int stuck = 0;
        generateBoard(&board, num_players);
        int curPlayerIndex = 0, total = board.penguins_per_player * num_players;
        fillBoard(&board, num_players);
        printf("\nGenerated board: \n");
        showBoard(&board);

        printf("\nPlacement phase commences\n\n");
        do
        {
            int x, y;
            int sign = curPlayerIndex + 6;
            printf("\nPlayer %d place your penguin\n", curPlayerIndex + 1);
            do
            {
                askForCoordinates(&x, &y);
            } while (validateCoordinates(&board, x, y) == 1);
            placePenguin(&board, x, y, sign);
            showBoard(&board);
            curPlayerIndex = (curPlayerIndex + 1) % num_players;
            total -= 1;
        } while (total > 0);

        // movement phase begins
        printf("\nMovement phase commences\n");
        do
        {
            int x, y, x1, y1;
            int sign = curPlayerIndex + 6;
            if (checkStuck(&board, sign) == 1)
            {
                curPlayerIndex = (curPlayerIndex + 1) % num_players;
                stuck++;
            }
            else
            {
                do
                {
                    askForCoordinatesOfPenguin(&x, &y, sign, &board);
                    askForCoordinatesMovement(&x, &y, &x1, &y1, sign, &board);
                } while (validateMove(&board, x, y, x1, y1) == 1);
                players[curPlayerIndex].score += board.array[x1][y1];
                movePenguin(&board, &x, &y, &x1, &y1, sign);
                showBoard(&board);
                printScores(players, num_players);
                curPlayerIndex = (curPlayerIndex + 1) % num_players;
                stuck = 0;
            }
        } while (stuck < num_players);
        printf("No player can move. Game Ending...\n");
        // Summarization
        printf("Summarization\n");
        printScores(players, num_players);
        summerization(players, num_players);
        freeBoard(&board);
        return 0;
    #else
        if (argc == 5 && strcmp(argv[1], "phase=placement") == 0)
        {
            // autonomous placement phase
            if(strcmp(argv[2],"name")==0 || strcmp(argv[3],"name")==0|| strcmp(argv[4],"name")==0){
                printf("%s",name);
            }else
            {
                int penguins_to_place;
                if (sscanf(argv[2], "penguins=%d", &penguins_to_place) != 1)
                {
                    fprintf(stderr, "Invalid format for penguins argument");
                    return 3;
                }if(penguins_to_place<=0){
                    printf("Invalid amount of penguins specified");
                    return 2;
                }
                char *input_file_name = argv[3];
                char *output_file_name = argv[4];
                readFile(&board, input_file_name, &players, &num_players);
                if (checkInputValidity(&board))
                {
                    if (checkPresence(players, name, num_players))
                    {
                        int my_id = getMyId(players, name, num_players);
                        if (checkPenguinsToPlace(&board, penguins_to_place, my_id))
                        {
                            placeAutonomously(players, &board, my_id, num_players);
                            writeFile(&board, output_file_name, players, num_players);
                            freeBoard(&board);
                            free(players);
                            return 0;
                        }
                        else
                        {
                            writeFile(&board, output_file_name, players, num_players);
                            freeBoard(&board);
                            free(players);
                            return 1;
                        }
                    }
                    else
                    {
                        int my_id = assignId(players, num_players);
                        if(my_id<10)
                        {
                            placeAutonomously(players, &board, my_id, num_players);
                            writeFile(&board, output_file_name, players, num_players);
                            appendMyPlayer(output_file_name, name, my_id, num_players);
                            freeBoard(&board);
                            free(players);
                            return 0;
                        }
                        printf("Maximum amount of players, can not place a penguin");
                        return 2;
                    }
                }
                return 2;
            }
        }
        else if (argc == 4 && strcmp(argv[1], "phase=movement") == 0)
        {
            if(strcmp(argv[2],"name")==0 || strcmp(argv[3],"name")==0)
            {
                printf("%s",name);
            }else
            {
                char *input_file_name = argv[2];
                char *output_file_name = argv[3];
                readFile(&board, input_file_name, &players, &num_players);
                if (checkInputValidity(&board))
                {
                    
                    int my_id=(-1)*getMyId(players,name,num_players);
                    if (my_id!=0)
                    {
                        if (canMove(&board, players, num_players, my_id))
                        {
                            // Moveable
                            moveAutonomously(&board, players, num_players, my_id);
                            writeFile(&board, output_file_name, players, num_players);
                            freeBoard(&board);
                            free(players);
                            return 0;
                        }
                        else
                        {
                            // Unmoveable
                            writeFile(&board, output_file_name, players, num_players);
                            freeBoard(&board);
                            free(players);
                            return 1;
                        }
                    }else
                    {   
                        printf("Our player is not present");
                        exit(2);
                    }
                    
                }
                return 2;
            }
        }
        else
        {
            int flag=0;
            for(int i=0;i<argc;i++){
                if(strcmp(argv[i],"name")==0){
                    flag=1;
                }
            }
            if (flag){
                printf("%s",name);
            }else{
                printf("Invalid amount of command line arguments or arguments");
                return 3;
            }
        }
    #endif
}
