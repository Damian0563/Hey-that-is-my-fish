#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "placement.h"


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

int ValidateDimensionsAndPenguins(int* m,int* n,int* penguins)
{
    if (*m>0 && *n>0 && *penguins*2>(*m)*(*n)){
        printf("Invalid parameters\n");
        return 0;
    }
    return 1;
}

void AskForPenguins(int *penguins)
{
    int ans;
    printf("How many penguins each player should have: ");
    scanf("%d",&ans);
    *penguins=ans;
}


void AskForDimensions(int* m, int* n)
{
    int x,y;
    printf("\nHow many rows should the board have: ");
    scanf("%d",&x);
    printf("How many columns should the board have: ");
    scanf("%d",&y);
    *m=x;
    *n=y;
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
    

void AskForCoordinates(int *x, int *y)
{
    printf("Enter where would you like to place your penguin(x y): ");
    scanf("%d %d",x,y);
}

int ValidateCoordinates(int m, int n, int board[m][n],int x, int y)
{
    if (x<m && x>=0 && y<n && y>=0){
        if (board[x][y]==1){
            return 0;
        }else{
            printf("Invalid tile selected\n");
            return 1;
        }
    }
    printf("Selected tile is out of bounds\n");
    return 1;
}
