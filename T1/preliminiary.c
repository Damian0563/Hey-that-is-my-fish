#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

void AskForCoordinates(int *x, int *y)
{
    //asks user for input in movement/placement phase
}

int ValidateCoordinates(int m, int n, int board[m][n],int x, int y)
{
    //validates user provided coordinates for movement/placement phase
    //rand for testing
    return rand()%4;
}

int ValidateDimensionsAndPenguins(int* m,int* n,int* penguins)
{
    if (*m>0 && *n>0 && *penguins*2>(*m)*(*n)){
        printf("Invalid parameters");
        return 0;
    }
    return 1;
}

void AskForPenguins(int *penguins)
{
    //asks for the amount of penguins each player should have
    int ans;
    printf("How many penguins each player should have: ");
    scanf("%d",&ans);
    *penguins=ans;
}

int GenerateTile()
{
    //generates a random number between 0 and 3
    return rand()%4;
}

void GenerateBoard(int* m, int* n, int* penguins)
{
    //generates the board
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
        *m=(rand()%10)+1;
        *n=(rand()%10)+1;
        AskForPenguins(penguins);
    }
}

void FillBoard(int m,int n,int board[m][n],int penguins)
{
    //to do: ensure the amount of ones one the board is atleast that of penguins
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            board[i][j]=GenerateTile();
        }
    }
} 


void ShowBoard(int m,int n,int board[m][n])
{
    //displays the board
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf(" %d ",board[i][j]);
        }
        printf("\n");
    }
}


void PlacePenguin(int m, int n, int board[m][n],int x, int y, int sign)
{
    //places penguins on th x y coordinates on the board
}

int ValidateMove(int m, int n, int board[m][n],int x, int y)
{
    //Validates players move, rand for testing
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
    FillBoard(m,n,board,penguins);
    int total=2*penguins,last_player=2;
    int points1=penguins, points2=penguins;
    printf("\nGenerated board: \n");
    ShowBoard(m,n,board);   //other showboards comented for testing/clarity purposes
    //initializing points1 and points2 as the amount of penguins each player should have- players can place their 
    //penguins only on tiles with one fish on it, therefor after the placement phase players points are equal to amount
    //of their penguins

    // placement phase begins
    printf("\nPlacement phase commences\n");
    do{
        int x,y;
        if (last_player==2)
        {
            do
            {
                AskForCoordinates(&x,&y);
            }while(ValidateCoordinates(m,n,board,x,y)==1);
            PlacePenguin(m,n,board,x,y,8);
            //ShowBoard(m,n,board);
            last_player=1;
        }
        else
        {
            do
            {
                AskForCoordinates(&x,&y);
            }while(ValidateCoordinates(m,n,board,x,y)==1);
            PlacePenguin(m,n,board,x,y,9);
            //ShowBoard(m,n,board);
            last_player=2;
        }
        total-=1;
    }while(total>0); 

    // movement phase begins
    printf("\nMovement phase commences\n");
    do 
    {
        int x,y;
        
        if (last_player==2){
            if(CheckStuck(m,n,board,8)==1)
            {
                last_player=1;
                stuck++;
                
            }
            else
            {
                do
                {
                    AskForCoordinates(&x,&y);
                }while(ValidateCoordinates(m,n,board,x,y)==1 && ValidateMove(m,n,board,x,y)==1);
                points1+=CollectPoints(m,n,board,x,y);
                PlacePenguin(m,n,board,x,y,8);
                //ShowBoard(m,n,board);
                last_player=1;
                stuck =0;
            }
        }
        else
        {
            if(CheckStuck(m,n,board,9)==1)
            {
                last_player=2;
                stuck++;
                
            }
            else
            {
                do
                {
                    AskForCoordinates(&x,&y);
                }while(ValidateCoordinates(m,n,board,x,y)==1 || ValidateMove(m,n,board,x,y)==1);
                points2+=CollectPoints(m,n,board,x,y);
                PlacePenguin(m,n,board,x,y,9);
                //ShowBoard(m,n,board);
                last_player=2;
                stuck =0;
            }
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