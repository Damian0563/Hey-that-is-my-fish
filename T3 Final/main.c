#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "placement.h"
#include "movement.h"
#include "utils.h"

int main()
{
    srand(time(NULL));
    int m,n,stuck=0,penguins=0;
    GenerateBoard(&m,&n,&penguins);
    int board[m][n];
    int total=2*penguins,cur_player=1;
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
        int sign=cur_player==1?8:9;
        printf("\nPlayer %s place your penguin\n",cur_player==1?"one":"two");
        do
        {
            AskForCoordinates(&x,&y);
        }while(ValidateCoordinates(m,n,board,x,y)==1);
        PlacePenguin(m,n,board,x,y,sign);
        ShowBoard(m,n,board);
        cur_player=cur_player==1?2:1;
        total-=1;
    }while(total>0); 

    // movement phase begins
    printf("\nMovement phase commences\n");
    do 
    {
        int x,y,x1,y1;
        int sign=cur_player==1?8:9;
        int *point=cur_player==1?&points1:&points2;
        if(CheckStuck(m,n,board,sign,penguins)==1)
        {
            cur_player=cur_player==1?2:1;
            stuck++;
        }
        else
        {
            do
            {
                AskForCoordinatesOfPenguin(&x,&y,m,n,sign,board);
                AskForCoordinatesMovement(&x,&y,&x1,&y1,m,n, sign,board);
            }while(ValidateMove(m,n,board,x,y,x1,y1)==1);
            CollectPoints(m,n,board,&x1,&y1,point);
            //printf("Points1: %d, Points2: %d",points1,points2); printing intermediate scores?
            MovePenguin(m,n,board,&x,&y,&x1,&y1,sign);
            ShowBoard(m,n,board);
            cur_player=cur_player==1?2:1;
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
    return 0;
}
