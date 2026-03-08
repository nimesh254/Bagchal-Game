#include <iostream>
#include <vector>
#include "ai.h"
#include "player.h"
using namespace std;

vector<vector<char>> board(5,vector<char>(5,'.'));
int goatsPlaced=0, goatsCaptured=0;
bool goatTurn=true;
bool placementPhase=true;

// ================= INIT =================
void initializeBoard(){
    board[0][0]='T';
    board[0][4]='T';
    board[4][0]='T';
    board[4][4]='T';
}

// ================= PRINT =================
void printBoard(){
    cout<<"\n  ";
    for(int i=0;i<5;i++) cout<<i<<" ";
    cout<<"\n";

    for(int i=0;i<5;i++){
        cout<<i<<" ";
        for(int j=0;j<5;j++)
            cout<<board[i][j]<<" ";
        cout<<"\n";
    }

    cout<<"\nGoats placed: "<<goatsPlaced<<"  Captured: "<<goatsCaptured<<"\n";
}

// ================= MOVE VALID =================
bool validMove(int r1,int c1,int r2,int c2){
    if(r2<0||r2>=5||c2<0||c2>=5) return false;
    int dr=abs(r2-r1);
    int dc=abs(c2-c1);
    if((dr==1 && dc==0)||(dr==0 && dc==1)) return true;
    if(dr==1 && dc==1 && (r1%2==c1%2)) return true;
    return false;
}

// ================= GOAT =================
bool applyGoat(Move m){
    if(placementPhase){
        if(board[m.r2][m.c2]=='.'){
            board[m.r2][m.c2]='G';
            goatsPlaced++;
            if(goatsPlaced==20) placementPhase=false;
            return true;
        }
        return false;
    }
    if(board[m.r1][m.c1]=='G' && board[m.r2][m.c2]=='.'
       && validMove(m.r1,m.c1,m.r2,m.c2)){
        board[m.r2][m.c2]='G';
        board[m.r1][m.c1]='.';
        return true;
    }
    return false;
}

// ================= TIGER =================
bool applyTiger(Move m){
    if(board[m.r1][m.c1]!='T') return false;
    int dr=m.r2-m.r1;
    int dc=m.c2-m.c1;

    if(abs(dr)==2 || abs(dc)==2){
        int mr=m.r1+dr/2;
        int mc=m.c1+dc/2;
        if(board[mr][mc]=='G' && board[m.r2][m.c2]=='.'){
            board[mr][mc]='.';
            goatsCaptured++;
            board[m.r2][m.c2]='T';
            board[m.r1][m.c1]='.';
            return true;
        }
    }
    if(validMove(m.r1,m.c1,m.r2,m.c2) && board[m.r2][m.c2]=='.'){
        board[m.r2][m.c2]='T';
        board[m.r1][m.c1]='.';
        return true;
    }
    return false;
}

// ================= MENU =================
int chooseMode(){
    int mode;
    while(true){
        cout<<"==== BAGCHAL ====\n";
        cout<<"1 Player vs Player\n2 Player vs AI\n3 AI vs AI\n";
        cout<<"Enter mode: ";
        cin>>mode;
        if(!cin.good() || mode<1 || mode>3){
            cout<<"Invalid mode, try again.\n";
            cin.clear(); cin.ignore(10000,'\n');
            continue;
        }
        break;
    }
    return mode;
}

// ================= GAME LOOP =================
void gameLoop(int mode){
    while(true){
        printBoard();
        Move m;

        if(goatTurn){
            if(mode==2 || mode==3)
                m=goatAI(board,placementPhase);
            else
                m=playerMoveGoat(board,placementPhase);

            if(!applyGoat(m)){ cout<<"Illegal goat move!\n"; continue; }
        }else{
            if(mode==1)
                m=playerMoveTiger(board);
            else
                m=tigerAI(board);

            if(!applyTiger(m)){ cout<<"Illegal tiger move!\n"; continue; }
        }

        if(goatsCaptured>=5){ cout<<"\nTIGERS WIN\n"; break; }

        // Check if all tigers trapped
        bool trapped=true;
        for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(board[i][j]=='T'){
                for(int dr=-1;dr<=1;dr++)
                for(int dc=-1;dc<=1;dc++){
                    int nr=i+dr, nc=j+dc;
                    if(nr>=0 && nr<5 && nc>=0 && nc<5 && board[nr][nc]=='.' && validMove(i,j,nr,nc))
                        trapped=false;
                }
            }
        if(trapped){ cout<<"\nGOATS WIN\n"; break; }

        goatTurn=!goatTurn;
    }
}

// ================= MAIN =================
int main(){
    int mode=chooseMode();
    initializeBoard();
    gameLoop(mode);
    return 0;
}