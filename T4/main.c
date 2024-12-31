#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "placement.h"
#include "movement.h"
#include "utils.h"
#include "structs.h"

int main()
{   
    Board board;
    srand(time(NULL));
    int stuck=0;
    GenerateBoard(&board);
    int cur_player=1,total=board.penguins_per_player*2;
    FillBoard(&board);
    int points2;
    int points1=points2=board.penguins_per_player;
    printf("\nGenerated board: \n");
    ShowBoard(&board);
    
    printf("\nPlacement phase commences\n\n");
    do{
        int x,y;
        int sign=cur_player==1?8:9;
        printf("\nPlayer %s place your penguin\n",cur_player==1?"one":"two");
        do
        {
            AskForCoordinates(&x,&y);
        }while(ValidateCoordinates(&board,x,y)==1);
        PlacePenguin(&board,x,y,sign);
        ShowBoard(&board);
        cur_player=cur_player==1?2:1;
        total-=1;
    }while(total>0); 

    //movement phase begins
    printf("\nMovement phase commences\n");
    do 
    {
        int x,y,x1,y1;
        int sign=cur_player==1?8:9;
        int *point=cur_player==1?&points1:&points2;
        if(CheckStuck(&board,sign)==1)
        {
            cur_player=cur_player==1?2:1;
            stuck++;
        }
        else
        {
            do
            {
                AskForCoordinatesOfPenguin(&x,&y,sign,&board);
                AskForCoordinatesMovement(&x,&y,&x1,&y1,sign,&board);
            }while(ValidateMove(&board,x,y,x1,y1)==1);
            CollectPoints(&board,&x1,&y1,point);
            //printf("Points1: %d, Points2: %d",points1,points2); printing intermediate scores?
            MovePenguin(&board,&x,&y,&x1,&y1,sign);
            ShowBoard(&board);
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
    FreeBoard(&board);
    return 0;
}
