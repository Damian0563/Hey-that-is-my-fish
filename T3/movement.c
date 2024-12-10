#include <stdio.h>
#include <stdlib.h>
#include "movement.h"

void MovePenguin(int m, int n,int board[m][n],int *x, int *y, int *x1, int *y1, int sign)
{
    //Moves penguin in the movement phase
    int newX=*x1;
    int newY=*y1;
    int oldX=*x;
    int oldY=*y;
    board[newX][newY]= sign;
    board[oldX][oldY] = 0;
}

void AskForCoordinatesOfP(int *x, int *y, int m, int n, int sign, int board[m][n])
{
    int newX;
    int newY;
    do
    {
        printf("Where is the penguin you want to move? (x y):\n");
        scanf("%d %d",x,y);
        newX=*x;
        newY=*y;
        if(board[newX][newY] != sign)
        {
            printf("That is not your penguin, yours is denoted by: %d\n", sign);
        }
    } while (board[newX][newY] != sign);
}

void AskForCoordinatesMovement(int *x, int *y, int *x1,int *y1, int m, int n, int sign, int board[m][n])
{
    int newX;
    int newY;
    int oldX=*x;
    int oldY=*y;
    do
    {
        printf("Where do you want to move your penguin? (x y):\n");
        scanf("%d %d",x1,y1);
        newX=*x1;
        newY=*y1;
        do
        {
            if(newX<0 || newX>=m || newY<0 || newY>n)
            {
                printf("Your inputs are out of bounds\n");
            }
        } while (newX<0 || newX>=m || newY<0 || newY>n);
        
        if(newX!=oldX && newY!=oldY)
        {
            printf("You can only move either on the same row or column inside bounds\n");
        }
    } while (newX!=oldX && newY!=oldY);
}

int ValidateMove(int m, int n, int board[m][n],int x, int y,int x1,int y1)
{
    //Validates players move and selected coordinates of a penguins to move
    if(x1>x)
    {
        for(int i = x+1; i <= x1;i++)
        {
            if(board[i][y1]==0||board[i][y1]==8||board[i][y1]==9)
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
            if(board[i][y1]==0||board[i][y1]==8||board[i][y1]==9)
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
            if(board[x1][i]==0||board[x1][i]==8||board[x1][i]==9)
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
            if(board[x1][i]==0||board[x1][i]==8||board[x1][i]==9)
            {
                printf("Path is blocked, choose another coordinate to move to\n");
                return 1;
            }
        }
        return 0;
    }
}

void CollectPoints(int m,int n,int board[m][n],int *x1,int *y1, int points1, int points2,int cur_player)
{
    int newX = *x1;
    int newY = *y1;
    if(cur_player==1)
    {
        points1+=board[newX][newY];
    }
    else
    {
        points2+=board[newX][newY];
    }
}

//check the surrounding of the chosen index to see if it could move
int checkSurr(int i, int j, int m, int n, int board[m][n])
{
    // Check if the penguin can move to any of the four adjacent cells
    if (i + 1 < m && (board[i + 1][j] == 1 || board[i + 1][j] == 2 || board[i + 1][j] == 3)) return 0; // Down
    if (i - 1 >= 0 && (board[i - 1][j] == 1 || board[i - 1][j] == 2 || board[i - 1][j] == 3)) return 0; // Up
    if (j + 1 < n && (board[i][j + 1] == 1 || board[i][j + 1] == 2 || board[i][j + 1] == 3)) return 0; // Right
    if (j - 1 >= 0 && (board[i][j - 1] == 1 || board[i][j - 1] == 2 || board[i][j - 1] == 3)) return 0; // Left
    return 1;
}


//check if the index could move and output appropriate response
int CheckStuck(int m, int n,int board[m][n],int sign, int penguins)
{
    int totalCounter = 0;
    for(int i = 0; i< m; i++)
    {
        for(int j  = 0; j< n; j++)
        {
            if(board[i][j] == sign)
            {
                if(checkSurr(i,j,m,n,board)==0)
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

    if(totalCounter == penguins)
    {
        if(sign == 8)
        {
            printf("Player one cannot move.\n");
        }
        else
        {
            printf("Player two cannot move.\n");
        }
        return 1;
    }
    else
    {
        if(sign == 8)
        {
            printf("Player one can move.\n");
        }
        else
        {
            printf("Player two can move.\n");
        }
        return 0;
    }
}