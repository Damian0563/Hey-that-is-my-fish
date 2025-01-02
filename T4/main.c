#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "placement.h"
#include "movement.h"
#include "utils.h"
#include "structs.h"


int main()
{   
    int numPlayer=0;
    numPlayer = askForPlayers(numPlayer);
    Player players[numPlayer];
    // Initialize players
    initializePlayers(numPlayer, players);
    Board board;
    srand(time(NULL));
    int stuck=0;
    GenerateBoard(&board, numPlayer);
    int curPlayerIndex=0,total=board.penguins_per_player*numPlayer;
    FillBoard(&board, numPlayer);
    printf("\nGenerated board: \n");
    ShowBoard(&board);
    
    printf("\nPlacement phase commences\n\n");
    do{
        int x,y;
        int sign=curPlayerIndex+6;
        printf("\nPlayer %d place your penguin\n",curPlayerIndex +1);
        do
        {
            AskForCoordinates(&x,&y);
        }while(ValidateCoordinates(&board,x,y)==1);
        PlacePenguin(&board,x,y,sign);
        ShowBoard(&board);
        curPlayerIndex=(curPlayerIndex+1)%numPlayer;
        total-=1;
    }while(total>0); 

    //movement phase begins
    printf("\nMovement phase commences\n");
    do 
    {
        int x,y,x1,y1;
        int sign=curPlayerIndex+6;
        if(CheckStuck(&board,sign)==1)
        {
            curPlayerIndex=(curPlayerIndex+1)%numPlayer;
            stuck++;
        }
        else
        {
            do
            {
                AskForCoordinatesOfPenguin(&x,&y,sign,&board);
                AskForCoordinatesMovement(&x,&y,&x1,&y1,sign,&board);
            }while(ValidateMove(&board,x,y,x1,y1)==1);
            players[curPlayerIndex].score += board.array[x1][y1];
            MovePenguin(&board,&x,&y,&x1,&y1,sign);
            ShowBoard(&board);
            printScores(players, numPlayer);
            curPlayerIndex=(curPlayerIndex+1)%numPlayer;
            stuck=0;
        }
    }while(stuck<numPlayer);
    printf("No player can move. Game Ending...\n");
    //Summarization
    printf("Summarization\n");
    printScores(players, numPlayer);
    summerization(players, numPlayer);
    FreeBoard(&board);
    return 0;
}
