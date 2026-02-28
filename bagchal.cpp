#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

const int SIZE = 5;
char board[SIZE][SIZE];

int goatsPlaced = 0;
int goatsCaptured = 0;
bool goatTurn = true;
bool placementPhase = true;

// ================= INITIALIZE =================
void initializeBoard() {
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            board[i][j]='.';

    board[0][0]='T';
    board[0][4]='T';
    board[4][0]='T';
    board[4][4]='T';
}

// ================= PRINT BOARD =================
void printBoard() {
    cout << "\n   ";
    for(int i=0;i<SIZE;i++) cout << i << " ";
    cout << "\n";

    for(int i=0;i<SIZE;i++){
        cout << i << "  ";
        for(int j=0;j<SIZE;j++)
            cout << board[i][j] << " ";
        cout << "\n";
    }

    cout << "\nGoats Placed: " << goatsPlaced;
    cout << "  Goats Captured: " << goatsCaptured << "\n";
}

// ================= MOVE VALIDATION =================
bool isValidMove(int r1,int c1,int r2,int c2){

    if(r2<0||r2>=SIZE||c2<0||c2>=SIZE)
        return false;

    int dr=abs(r2-r1);
    int dc=abs(c2-c1);

    // Horizontal & Vertical
    if((dr==1 && dc==0) || (dr==0 && dc==1))
        return true;

    // Diagonal only on valid intersections
    if(dr==1 && dc==1 && (r1%2==c1%2))
        return true;

    return false;
}

// ================= TIGER CAPTURE =================
bool tigerCapture(int r1,int c1,int r2,int c2){

    int dr=r2-r1;
    int dc=c2-c1;

    if(abs(dr)==2 || abs(dc)==2){

        int midR=r1+dr/2;
        int midC=c1+dc/2;

        if(board[midR][midC]=='G' && board[r2][c2]=='.'){
            board[midR][midC]='.';
            goatsCaptured++;
            return true;
        }
    }
    return false;
}

// ================= TIGER CAN MOVE CHECK =================
bool tigerCanMove(int r,int c){

    for(int i=-2;i<=2;i++){
        for(int j=-2;j<=2;j++){

            int nr=r+i;
            int nc=c+j;

            if(nr>=0 && nr<SIZE && nc>=0 && nc<SIZE){

                if(board[nr][nc]=='.'){

                    if(isValidMove(r,c,nr,nc))
                        return true;

                    if(tigerCapture(r,c,nr,nc))
                        return true;
                }
            }
        }
    }
    return false;
}

// ================= GOAT WIN CHECK =================
bool checkGoatWin(){

    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            if(board[i][j]=='T')
                if(tigerCanMove(i,j))
                    return false;

    return true;
}

// ================= TIGER WIN CHECK =================
bool checkTigerWin(){
    return goatsCaptured>=5;
}

// ================= GOAT TURN =================
void goatMove(){

    int r1,c1,r2,c2;

    if(placementPhase){

        cout<<"Enter row and col to place goat: ";
        cin>>r1>>c1;

        if(board[r1][c1]=='.'){
            board[r1][c1]='G';
            goatsPlaced++;
        }
        else{
            cout<<"Invalid placement!\n";
            return;
        }

        if(goatsPlaced==20)
            placementPhase=false;

    }
    else{

        cout<<"Enter goat current position: ";
        cin>>r1>>c1;
        cout<<"Enter destination: ";
        cin>>r2>>c2;

        if(board[r1][c1]=='G' && board[r2][c2]=='.'
           && isValidMove(r1,c1,r2,c2)){

            board[r2][c2]='G';
            board[r1][c1]='.';
        }
        else{
            cout<<"Invalid move!\n";
            return;
        }
    }

    goatTurn=false;
}

// ================= TIGER TURN =================
void tigerMove(){

    int r1,c1,r2,c2;

    cout<<"Enter tiger current position: ";
    cin>>r1>>c1;
    cout<<"Enter destination: ";
    cin>>r2>>c2;

    if(board[r1][c1]!='T'){
        cout<<"Not a tiger!\n";
        return;
    }

    if(board[r2][c2]!='.'){
        cout<<"Destination not empty!\n";
        return;
    }

    // Capture
    if(tigerCapture(r1,c1,r2,c2)){
        board[r2][c2]='T';
        board[r1][c1]='.';
        goatTurn=true;
        return;
    }

    // Normal move
    if(isValidMove(r1,c1,r2,c2)){
        board[r2][c2]='T';
        board[r1][c1]='.';
        goatTurn=true;
        return;
    }

    cout<<"Invalid tiger move!\n";
}

// ================= MAIN GAME LOOP =================
void gameLoop(){

    while(true){

        printBoard();

        if(checkTigerWin()){
            cout<<"\n🐯 TIGERS WIN!\n";
            break;
        }

        if(checkGoatWin()){
            cout<<"\n🐐 GOATS WIN!\n";
            break;
        }

        if(goatTurn)
            goatMove();
        else
            tigerMove();
    }
}

// ================= MAIN =================
int main(){

    initializeBoard();

    cout<<"==== BAGCHAL GAME ====\n";
    cout<<"Traditional 5x5 Version\n";

    gameLoop();

    return 0;
}