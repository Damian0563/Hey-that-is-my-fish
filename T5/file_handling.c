#include <stdio.h>
#include <string.h>
#include "file_handling.h"
#include <stdlib.h>
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
        return;
    }
    char buffer[1023];
    int row_index = 0;
    int curr_player;
    int max_rows = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        max_rows++;
    }
    rewind(file);

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (row_index == 0)
        {
            // Read the dimension of the board
            char *token = strtok(buffer, " ");
            board->rows = atoi(token);
            token = strtok(NULL, " ");
            board->columns = atoi(token);

            board->array = (int **)malloc(board->rows * sizeof(int *));
            if (board->array == NULL)
            {
                perror("Memory allocation failed for rows");
                exit(EXIT_FAILURE);
            }
            for (int i = 0; i < board->rows; i++)
            {
                board->array[i] = (int *)malloc(board->columns * sizeof(int));
                if (board->array[i] == NULL)
                {
                    perror("Memory allocation failed for columns");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            // Store the contents of the file in matrix
            if (row_index - 1 < board->rows)
            {
                int col_index = 0;
                for (int i = 0; i < board->columns; i++)
                {
                    char *token = strtok(i == 0 ? buffer : NULL, " ");
                    if (token == NULL)
                    {
                        fprintf(stderr, "Error: Insufficient data in row %d.\n", row_index);
                        exit(EXIT_FAILURE);
                    }
                    board->array[row_index - 1][col_index] = interpretValueRead(token);
                    col_index++;
                }
            }
            else
            {
                // Read player information
                AutonomousPlayer *temp = malloc((*num_players + 1) * sizeof(AutonomousPlayer));
                if (temp == NULL)
                {
                    perror("Memory allocation failed for players");
                    free(*players); 
                    exit(EXIT_FAILURE);
                }
                if (*players != NULL)
                {
                    memcpy(temp, *players, *num_players * sizeof(AutonomousPlayer));
                    free(*players);
                }
                *players = temp;
                char *token = strtok(buffer, " ");
                strncpy((*players)[*num_players].name, token, sizeof((*players)[*num_players].name) - 1);
                (*players)[*num_players].name[sizeof((*players)[*num_players].name) - 1] = '\0';
                token = strtok(NULL, " ");
                (*players)[*num_players].id = atoi(token);
                token = strtok(NULL, " ");
                (*players)[*num_players].points = atoi(token);
                (*num_players)++;
                // debug purposes
                // printf("Player added: %s, ID: %d, Points: %d\n", (*players)[*num_players - 1].name, (*players)[*num_players - 1].id, (*players)[*num_players - 1].points); // Debug statement
            }
        }

        row_index++;
    }

    fclose(file);
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

int CheckInputValidity(Board* board)
{
    return 1;
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
