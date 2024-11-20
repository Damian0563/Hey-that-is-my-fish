#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void AskForDimensions(int *m, int *n){
    //asks for board dimensions
}

void AskForCoordinates(int *x, int *y){
    //asks user for input in movement/placement phase
}

int ValidateCoordinates(int m, int n, int board[m][n],int x, int y){
    //validates user provided coordinates for movement/placement phase
    //rand for testing
    return rand()%4;
}

int ValidateDimensionsAndPenguins(int *m,int *n,int *penguins){
    //validates dimensions and penguins
    return rand()%3;
}

void AskForPenguins(int *penguins){
    //asks for the amount of penguins each player should have
    *penguins=(rand()%3)+1;
}

int GenerateTile(){
    //generates a random number between 0 and 3
    return rand()%4;
}

void GenerateBoard(int m, int n, int board[m][n]){
    //generates the board
}

void ShowBoard(int m,int n,int board[m][n]){
    //displays the board
}


void PlacePenguin(int m, int n, int board[m][n],int x, int y, int sign){
    //places penguins on th x y coordinates on the board
}

int ValidateMove(int m, int n, int board[m][n],int x, int y){
    //Validates players move, rand for testing
    return rand()%4;
}

int CollectPoints(int m,int n,int board[m][n],int x,int y){
    //collects point from a tile, rand for testing
    return (rand()%3)+1;
}

int CheckStuck(int m, int n,int board[m][n],int sign){
    //checking if a player is stuck ,rand for now
    return rand()%4;
}

int main(){
    srand(time(NULL));
    int m,n,penguins=0;
    do{
        AskForDimensions(&m,&n);
        AskForPenguins(&penguins);
    }while(ValidateDimensionsAndPenguins(&m,&n,&penguins)==1);
    int total=2*penguins,last_player=2;
    int points1=penguins, points2=penguins;
    //initializing points1 and points2 as the amount of penguins each player should have- players can place their 
    //penguins only on tiles with one fish on it, therefor after the placement phase players points are equal to amount
    //of their penguins
    int board[m][n];
    GenerateBoard(m,n,board);
    // placement phase begins
    do{
        int x,y;
        if (last_player==2){
            do{
                AskForCoordinates(&x,&y);
            }while(ValidateCoordinates(m,n,board,x,y)==1);
            PlacePenguin(m,n,board,x,y,8);
            ShowBoard(m,n,board);
            last_player=1;
        }else{
            do{
                AskForCoordinates(&x,&y);
            }while(ValidateCoordinates(m,n,board,x,y)==1);
            PlacePenguin(m,n,board,x,y,9);
            ShowBoard(m,n,board);
            last_player=2;
        }
        total-=1;
    }while(total>0); 

    // movement phase begins
    do {
        int x,y;
        int stuck=0;
        if (last_player==2){
            if(CheckStuck(m,n,board,8)==1){
                last_player=1;
                continue;
            }else if(CheckStuck(m,n,board,8)==1 && CheckStuck(m,n,board,9)==1){
                printf("Neither player can move");
                break;
            }else{
                do{
                    AskForCoordinates(&x,&y);
                }while(ValidateCoordinates(m,n,board,x,y)==1 && ValidateMove(m,n,board,x,y)==1);
                points1+=CollectPoints(m,n,board,x,y);
                PlacePenguin(m,n,board,x,y,8);
                ShowBoard(m,n,board);
                last_player=1;
            }
        }else{
            if(CheckStuck(m,n,board,9)==1){
                last_player=2;
                continue;
            }else if(CheckStuck(m,n,board,8)==1 || CheckStuck(m,n,board,9)==1){
                printf("Neither player can move\n");
                break;
            }else{
                do{
                    AskForCoordinates(&x,&y);
                }while(ValidateCoordinates(m,n,board,x,y)==1 || ValidateMove(m,n,board,x,y)==1);
                points2+=CollectPoints(m,n,board,x,y);
                PlacePenguin(m,n,board,x,y,9);
                ShowBoard(m,n,board);
                last_player=2;
            }}
    }while(1);

    //Summarization
    printf("\nPlayer 1: %d, Player 2: %d",points1,points2);
    if (points1>points2){
        printf("\nPlayer one wins\n");
    }else if(points2>points1){
        printf("\nPlayer two wins\n");
    }else{
        printf("\nGame ended in a draw\n");
    }

}