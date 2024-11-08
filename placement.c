#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Reads dimensions of the grid
void ReadGrid(int *m,int *n){
    printf("Enter board dimensions: ");
    scanf("%d %d",m,n);
}

//Asks for the amount of penguins EACH player will have
void PenguinsPerPlayer(int *penguins){
    printf("Enter how many penguins each player should have: ");
    scanf("%d",penguins);
}

//generates a number representing the amount of fish on the tile
int GenerateTile(){
    int number=(rand()%4);
    return number;
}

//initializes the board with provided dimensions and fills it with values 1 through 3
void GenerateBoard(int m,int n,int board[m][n]){
    
    srand(time(NULL));
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            board[i][j]=GenerateTile();
        }
    }
    printf("Placement phase commences\n");
}

//Displays the board to the screen
void ShowBoard(int m,int n,int board[m][n]){

    printf("\n");
    for (int j = 0; j < n+1; j++) {
        printf("%4d", j);  // Print column headers
    }
    printf("\n   ");
    for (int j = 0; j < n; j++) {
        printf("-----");       // Separator line below headers
    }
    printf("\n");

    for(int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            if (j==0){
                printf("%2d |",i+1);
            }
            printf("%4d",board[i][j]);
        }
        printf("\n");
    }
}

void AskForCoordinates(int *x,int *y){
    printf("Where would you like to place your penguin, enter coordinates(X Y): ");
    scanf("%d %d",x,y);
}

int ValidateCoordinatesPlacement(int m,int n, int board[m][n],int x, int y){
    if (x<0 || y<0){
        return 1;
    }
    if (x<m && x<n && y<n && y<m){

        if (board[x][y]!=1){
            return 1;
        }
        return 0;

    }
}

void PlacementPhase(int m,int n,int totalPenguins,int lastPlayer,int board[m][n],int P1,int P2){

    while(totalPenguins>0){
        
        int x,y;
        if(lastPlayer==2){
            do{
                printf("Player one, place your penguin on the board\n");
                AskForCoordinates(&x,&y);
                x-=1;
                y-=1;
                if (ValidateCoordinatesPlacement(m,n,board,x,y)==1){
                    printf("Invalid tile selected, no changes made\n");
                }
            }
            while(ValidateCoordinatesPlacement(m,n,board,x,y)==1);
            lastPlayer=1;
            board[x][y]=8;
            printf("\n");
            ShowBoard(m,n,board);
        }else{
            do{
                printf("\nPlayer two, place your penguin on the board\n");
                AskForCoordinates(&x,&y);
                x-=1;
                y-=1;
                if (ValidateCoordinatesPlacement(m,n,board,x,y)==1){
                    printf("Invalid tile selected, no changes made\n");
                }
            }while(ValidateCoordinatesPlacement(m,n,board,x,y)==1);
            lastPlayer=2;
            board[x][y]=9;
            printf("\n");
            ShowBoard(m,n,board);
        }
        totalPenguins-=1;
    }
    printf("Placement phase ended, movement phase commences\n");
}

int ValidateBoard(int m, int n, int board[m][n],int totalPenguins){

    int ones=0;
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            if (board[i][j]==1){
                ones+=1;
            }
        }
    }
    if (ones<totalPenguins || m*n<totalPenguins){
        return 0;
    }
    return 1;
}

void play(){
    int m,n,penguins;
    int lastPlayer=2,P1=0,P2=0;
    int totalPenguins=2*penguins;
    ReadGrid(&m,&n);
    int board[m][n];
    PenguinsPerPlayer(&penguins);
    GenerateBoard(m,n,board);
    if (ValidateBoard(m,n,board,totalPenguins)==1){
        ShowBoard(m,n,board);
        PlacementPhase(m,n,totalPenguins,lastPlayer,board,P1,P2);
    }else{
        printf("Invalid amount of penguins for given dimensions. Game terminated.\n\n");
        exit(1);
    }
}

int main(){
    play();
}