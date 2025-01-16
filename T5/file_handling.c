#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_handling.h"
#include "movement.h"
#include "structs.h"
#include "utils.h"
#include "placement.h"



void ReadFile(Board *board, char *file_name, AutonomousPlayer **players, int *num_players)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(2); // Critical error: terminate program.
    }

    char buffer[1023];
    int row_index = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        buffer[strcspn(buffer, "\r\n")] = '\0'; // Strip newline characters.

        if (row_index == 0)
        {
            // Read and validate board dimensions.
            char *token = strtok(buffer, " ");
            if (token == NULL)
            {
                printf("Error: Missing board dimensions.\n");
                exit(2); // Critical error: terminate program.
            }
            board->rows = atoi(token);
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("Error: Missing board dimensions.\n");
                exit(2); // Critical error: terminate program.
            }
            board->columns = atoi(token);

            if (!ValidateBoardDimensions(board))
            {
                printf("Error: Invalid board dimensions.\n");
                exit(2); // Critical error: terminate program.
            }

            board->array = malloc(board->rows * sizeof(int *));
            for (int i = 0; i < board->rows; i++)
            {
                board->array[i] = malloc(board->columns * sizeof(int));
            }
        }
        else if (row_index <= board->rows)
        {
            // Read board contents.
            char *token = strtok(buffer, " ");
            for (int col_index = 0; col_index < board->columns; col_index++)
            {
                if (token == NULL)
                {
                    printf("Warning: Missing data in row %d.\n", row_index);
                    return; // Soft error: do not terminate.
                }
                board->array[row_index - 1][col_index] = interpretValueRead(token);
                token = strtok(NULL, " ");
            }
        }
        else
        {
            // Read player data.
            AutonomousPlayer *temp = malloc((*num_players + 1) * sizeof(AutonomousPlayer));
            if (temp == NULL)
            {
                perror("Memory allocation failed for players");
                exit(2); // Critical error: terminate program.
            }
            memcpy(temp, *players, *num_players * sizeof(AutonomousPlayer));
            free(*players);
            *players = temp;

            char *token = strtok(buffer, " ");
            if (token == NULL)
            {
                printf("Warning: Missing player name.\n");
                return; // Soft error: do not terminate.
            }
            strncpy((*players)[*num_players].name, token, sizeof((*players)[*num_players].name) - 1);
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("Warning: Missing player ID.\n");
                return; // Soft error: do not terminate.
            }
            (*players)[*num_players].id = atoi(token);
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("Warning: Missing player points.\n");
                return; // Soft error: do not terminate.
            }
            (*players)[*num_players].points = atoi(token);
            (*num_players)++;
        }

        row_index++;
    }

    fclose(file);

    // Final validation.
    if (!ValidatePlayerData(*players, *num_players))
    {
        printf("Error: Invalid player data.\n");
        exit(2); // Critical error: terminate program.
    }
}

int CheckInputValidity(Board *board)
{
    if (board == NULL || board->rows <= 0 || board->columns <= 0)
    {
        fprintf(stderr, "Error: Invalid board structure.\n");
        return 0; // Invalid input.
    }

    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->columns; j++)
        {
            if (board->array[i][j] > 3 || board->array[i][j]<-9)
            {
                printf("Error: Invalid value at row %d, column %d.\n", i, j);
                return 0; // Invalid value detected.
            }
                
        }
    }

    return 1; // Input is valid.
}

int ValidateBoardDimensions(Board *board)
{
    return (board->rows > 0 && board->columns > 0 && board->rows <= 100 && board->columns <= 100);
}

int ValidatePlayerData(const AutonomousPlayer *players, int num_players)
{
    for (int i = 0; i < num_players; i++)
    {
        if (players[i].id <= 0 ||players[i].id>9 || strlen(players[i].name) == 0 || players[i].points < 0)
        {
            printf("Error: Invalid data for player %d.\n", i);
            return 0; // Invalid player data.
        }
    }
    return 1; // All player data is valid.
}

void AppendMyPlayer(char* OutputFileName,char* name, int my_id,int num_players)
{
    FILE *pf=fopen(OutputFileName,"a");
    if(num_players!=0)
    {
        fprintf(pf,"\n");
    }
    fprintf(pf,"%s %d 1",name,my_id);
    fclose(pf);
}

int AssignId(AutonomousPlayer players[],int num_players)
{
    for(int i=1;i<10;i++)
    {
        int flag=1;
        for(int j=0;j<num_players;j++)
        {
            if(players[j].id==i)
            {
                flag=0;
            }
        }
        if(flag){
            return i;
        }
    }
}

int interpretValueRead(char *token)
{
    if (strcmp(token, "00") == 0)
    {
        return 0;
    }
    else if (strcmp(token, "10") == 0 || strcmp(token, "20") == 0 || strcmp(token, "30") == 0)
    {
        return atoi(token) / 10;
    }
    else
    {
        return -atoi(token);
    }
}

int interpretValueWrite(int value)
{
    if (value == 0)
    {
        return 0;
    }
    else if (value == 1 || value == 2 || value == 3)
    {
        value = value * 10;
        return value;
    }
    else
    {
        return abs(value);
    }
}

void WriteFile(Board *board, char *file_name, AutonomousPlayer players[], int num_players)
{
    FILE *file = fopen(file_name, "w+");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%d %d\n", board->rows, board->columns);
    for (int i = 0; i < board->rows; i++)
    {
        for (int j = 0; j < board->columns; j++)
        {
            fprintf(file, "%02d ", interpretValueWrite(board->array[i][j]));
        }
        fprintf(file, "\n");
    }
    for (int i = 0; i < num_players; i++)
    {
        if (i == num_players - 1)
        {
            fprintf(file, "%s %d %d", players[i].name, players[i].id, players[i].points);
            break;
        }
        fprintf(file, "%s %d %d\n", players[i].name, players[i].id, players[i].points);
    }

    fclose(file);
}

