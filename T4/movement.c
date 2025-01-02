#include <stdio.h>
#include <stdlib.h>
#include "movement.h"
#include "utils.h"

void MovePenguin(Board* board,int *x, int *y, int *x1, int *y1, int sign)
{
    int newX=*x1;
    int newY=*y1;
    int oldX=*x;
    int oldY=*y;
    board->array[newX][newY]= sign;
    board->array[oldX][oldY] = 0;
}

int ValidateMove(Board* board,int x, int y,int x1,int y1)
{
    if(x==x1 && y==y1)
    {
        printf("Penguin unselected, choose another penguin");
        return 1;
    }
    
    if(x1>x)
    {
        for(int i = x+1; i <= x1;i++)
        {
            if(board->array[i][y1]==0||board->array[i][y1]==6||board->array[i][y1]==7||board->array[i][y1]==8||board->array[i][y1]==9)
            {
                printf("Path is blocked, choose another coordinate to move to\n");
                return 1;
            }
        }
        return 0;
    }

    if(x1<x)
    {
        for(int i = x-1; i >= x1;i--)
        {
            if(board->array[i][y1]==0||board->array[i][y1]==6||board->array[i][y1]==7||board->array[i][y1]==8||board->array[i][y1]==9)
            {
                printf("Path is blocked, choose another coordinate to move to\n");
                return 1;
            }
        }
        return 0;
    }

    if(y1>y)
    {
        for(int i = y+1; i <= y1;i++)
        {
            if(board->array[x1][i]==0||board->array[x1][i]==6||board->array[x1][i]==7||board->array[x1][i]==8||board->array[x1][i]==9)
            {
                printf("Path is blocked, choose another coordinate to move to\n");
                return 1;
            }
        }
        return 0;
    }

    if(y1<y)
    {
        for(int i = y-1; i >= y1;i--)
        {
            if(board->array[x1][i]==0||board->array[x1][i]==6||board->array[x1][i]==7||board->array[x1][i]==8||board->array[x1][i]==9)
            {
                printf("Path is blocked, choose another coordinate to move to\n");
                return 1;
            }
        }
        return 0;
    }
}

int CheckSurrounding(int i, int j, Board* board)
{
    // Check if the penguin can move to any of the four adjacent cells
    if (i + 1 < board->rows && (board->array[i + 1][j] == 1 || board->array[i + 1][j] == 2 || board->array[i + 1][j] == 3)) return 0; // Down
    if (i - 1 >= 0 && (board->array[i - 1][j] == 1 || board->array[i - 1][j] == 2 || board->array[i - 1][j] == 3)) return 0; // Up
    if (j + 1 < board->columns && (board->array[i][j + 1] == 1 || board->array[i][j + 1] == 2 || board->array[i][j + 1] == 3)) return 0; // Right
    if (j - 1 >= 0 && (board->array[i][j - 1] == 1 || board->array[i][j - 1] == 2 || board->array[i][j - 1] == 3)) return 0; // Left
    return 1;
}


int CheckStuck(Board* board,int sign)
{
    int totalCounter = 0;
    for(int i = 0; i< board->rows; i++)
    {
        for(int j  = 0; j< board->columns; j++)
        {
            if(board->array[i][j] == sign)
            {
                if(CheckSurrounding(i,j,board)==0)
                {
                    continue;
                }
                else
                {
                    totalCounter++;
                }
            }
        }
    }

    if(totalCounter == board->penguins_per_player)
    {
        printf("\nPlayer %d can not move.\n", sign -5);
        return 1;
    }
    else
    {   
        printf("\nPlayer %d can move.\n", sign -5);
        return 0;
    }
}