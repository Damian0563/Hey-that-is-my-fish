#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "placement.h"
#include "utils.h"


void GenerateBoard(int* m, int* n, int* penguins)
{
    int ans;
    do
    {
        printf("Would you like to generate a board manually or artificially: 1[manually] or 2[artificially]: ");
        scanf("%d",&ans);
    }
    while(ans!=1 && ans!=2);
    if(ans==1)
    {
        do
        {
            AskForDimensions(m,n);
            AskForPenguins(penguins);
        }while(ValidateDimensionsAndPenguins(m,n,penguins)==0);
        
    }
    else
    {   
        //+1 needed for logic, +3 needed for clarity, readable board, it is a board at least 3x3
        do{
            *m=(rand()%10)+3;
            *n=(rand()%10)+3;
            AskForPenguins(penguins);
        }while(ValidateDimensionsAndPenguins(m,n,penguins)==0);
    }
}

void FillBoard(int m,int n,int board[m][n],int penguins)
{
    int ones=0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            board[i][j]=GenerateTile();
            if(board[i][j]==1){
                ones++;
            }
        }
    }
    if (ones<penguins){
        while(ones<penguins){
            int gen_i=rand()%m;
            int gen_j=rand()%n;
            if (board[gen_i][gen_j]!=1){
                board[gen_i][gen_j]=1;
                ones++;
            }
        }
    }
}   

int GenerateTile(){return rand()%4;}

void PlacePenguin(int m, int n, int board[m][n],int x, int y, int sign){board[x][y]=sign;}
    

