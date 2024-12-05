#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "placement.h"


void ShowBoard(int m,int n,int board[m][n])
{
    //displays the board
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {   
            if (board[i][j]==8){
                printf("\033[1;31m %d \033[0m", board[i][j]);
            }else if(board[i][j]==9){
                printf("\033[1;34m %d \033[0m", board[i][j]);
            }else{
                printf(" %d ",board[i][j]);
            }
        }
        printf("\n");
    }
}

void MovePenguin(int m, int n,int board[m][n],int x, int y, int sign){
    //Moves penguin in the movement phase
}

void AskForCoordinatesMovement(int *x, int *y, int *x1, int *y1)
{
    //asks user for input in movement/placement phase
}


int ValidateMove(int m, int n, int board[m][n],int x, int y,int x1,int y1)
{
    //Validates players move and selected coordinates of a penguins to move
    return rand()%4;
}

int CollectPoints(int m,int n,int board[m][n],int x,int y)
{
    //collects point from a tile, rand for testing
    return (rand()%3)+1;
}

int CheckStuck(int m, int n,int board[m][n],int sign)
{
    //checking if a player is stuck ,rand for now
    return rand()%4;
}

int main()
{
    srand(time(NULL));
    int m,n,stuck=0,penguins=0;
    GenerateBoard(&m,&n,&penguins);
    int board[m][n];
    int total=2*penguins,last_player=2;
    FillBoard(m,n,board,total);
    int points1=penguins, points2=penguins;
    printf("\nGenerated board: \n");
    ShowBoard(m,n,board);   //other showboards comented for testing/clarity purposes
    //initializing points1 and points2 as the amount of penguins each player should have- players can place their 
    //penguins only on tiles with one fish on it, therefor after the placement phase players points are equal to amount
    //of their penguins

    // placement phase begins
    printf("\nPlacement phase commences\n\n");
    do{
        int x,y;
        int sign=last_player==2?8:9;
        printf("\nPlayer %s place your penguin\n",last_player==2?"one":"two");
        do
        {
            AskForCoordinates(&x,&y);
        }while(ValidateCoordinates(m,n,board,x,y)==1);
        PlacePenguin(m,n,board,x,y,sign);
        ShowBoard(m,n,board);
        last_player=last_player==2?1:0;
        total-=1;
    }while(total>0); 

    // movement phase begins
    printf("\nMovement phase commences\n");
    do 
    {
        int x,y,x1,y1;
        int sign=last_player==2?8:9;
        if(CheckStuck(m,n,board,sign)==1)
        {
            last_player=last_player==2?1:2;
            stuck++;
        }
        else
        {
            do
            {
                AskForCoordinatesMovement(&x,&y,&x1,&y1);
            }while(ValidateMove(m,n,board,x,y,x1,y1)==1);
            points1+=CollectPoints(m,n,board,x,y);
            MovePenguin(m,n,board,x,y,sign);
            //ShowBoard(m,n,board);
            last_player=last_player==2?1:2;
            stuck=0;
        }
    }while(stuck<2);
    printf("Neither player can move. Game Ending...");
    //Summarization
    printf("\nSummarization phase\n");
    printf("Player 1: %d, Player 2: %d",points1,points2);
    if (points1>points2)
    {
        printf("\nPlayer one wins\n");
    }
    else if(points2>points1)
    {
        printf("\nPlayer two wins\n");
    }
    else
    {
        printf("\nGame ended in a draw\n");
    }

}
