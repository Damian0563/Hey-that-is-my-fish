#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "placement.h"
#include "movement.h"
#include "utils.h"
#include "structs.h"
#include "file_handling.h"

int main(int argc, char *argv[])
{
    Board board;
    AutonomousPlayer *players;
    int num_players = 0;
    char *extension = strrchr(argv[0], '.');
    if ((extension && strcmp(extension, ".exe") == 0)||(extension && strcmp(extension,".out")==0))
    {
        *extension = '\0'; // Truncate the string at the ".exe" or ".out"
    }
    char* name=basename(argv[0]);
    if (argc == 1)
    {
        int numPlayer = 0;
        numPlayer = askForPlayers(numPlayer);
        Player players[numPlayer];
        // Initialize players
        initializePlayers(numPlayer, players);
        srand(time(NULL));
        int stuck = 0;
        GenerateBoard(&board, numPlayer);
        int curPlayerIndex = 0, total = board.penguins_per_player * numPlayer;
        FillBoard(&board, numPlayer);
        printf("\nGenerated board: \n");
        ShowBoard(&board);

        printf("\nPlacement phase commences\n\n");
        do
        {
            int x, y;
            int sign = curPlayerIndex + 6;
            printf("\nPlayer %d place your penguin\n", curPlayerIndex + 1);
            do
            {
                AskForCoordinates(&x, &y);
            } while (ValidateCoordinates(&board, x, y) == 1);
            PlacePenguin(&board, x, y, sign);
            ShowBoard(&board);
            curPlayerIndex = (curPlayerIndex + 1) % numPlayer;
            total -= 1;
        } while (total > 0);

        // movement phase begins
        printf("\nMovement phase commences\n");
        do
        {
            int x, y, x1, y1;
            int sign = curPlayerIndex + 6;
            if (CheckStuck(&board, sign) == 1)
            {
                curPlayerIndex = (curPlayerIndex + 1) % numPlayer;
                stuck++;
            }
            else
            {
                do
                {
                    AskForCoordinatesOfPenguin(&x, &y, sign, &board);
                    AskForCoordinatesMovement(&x, &y, &x1, &y1, sign, &board);
                } while (ValidateMove(&board, x, y, x1, y1) == 1);
                players[curPlayerIndex].score += board.array[x1][y1];
                MovePenguin(&board, &x, &y, &x1, &y1, sign);
                ShowBoard(&board);
                printScores(players, numPlayer);
                curPlayerIndex = (curPlayerIndex + 1) % numPlayer;
                stuck = 0;
            }
        } while (stuck < numPlayer);
        printf("No player can move. Game Ending...\n");
        // Summarization
        printf("Summarization\n");
        printScores(players, numPlayer);
        summerization(players, numPlayer);
        FreeBoard(&board);
        return 0;
    }
    else if (argc == 5 && strcmp(argv[1], "phase=placement") == 0)
    {
        // autonomous placement phase

        int PenguinsToPlace;
        if (sscanf(argv[2], "penguins=%d", &PenguinsToPlace) != 1)
        {
            fprintf(stderr, "Invalid format for penguins argument");
            return 3;
        }
        char *InputFileName = argv[3];
        char *OutputFileName = argv[4];
        ReadFile(&board, InputFileName, &players, &num_players);
        if(CheckInputValidity(&board))
        {
            if(CheckPresence(players,name,num_players))
            {
                int my_id=GetMyId(players,name,num_players);
                if(CheckPenguinsToPlace(&board,PenguinsToPlace,my_id))
                {
                    PlaceAutonomously(players,&board,my_id,num_players);
                    WriteFile(&board, OutputFileName, players, num_players);
                    FreeBoard(&board);
                    free(players);
                    return 0;
                }else
                {
                    return 1;
                }
            }
            else
            {
                int my_id=AssignId(players,num_players);
                PlaceAutonomously(players,&board,my_id,num_players);
                WriteFile(&board, OutputFileName, players, num_players);
                AppendMyPlayer(OutputFileName,name,my_id,num_players);
                FreeBoard(&board);
                free(players);
                return 0;
            }
            
        }
        return 2;
    }
    else if (argc == 4 && strcmp(argv[1], "phase=movement") == 0)
    {
        char *InputFileName = argv[2];
        char *OutputFileName = argv[3];
        ReadFile(&board, InputFileName, &players, &num_players);
        if(CheckInputValidity(&board))
        {   
            if(CanMove(&board))
            {
                MoveAutonomously(&board);
                WriteFile(&board, OutputFileName, players, num_players);
                FreeBoard(&board);
                return 0;
            }
            return 1;
        }
    }
    else if (argc == 2 && strcmp(argv[1], "name") == 0)
    {
        printf("%s",name);
    }
    else
    {
        printf("Invalid amount of command line arguments or arguments");
        return 3;
    }
}
