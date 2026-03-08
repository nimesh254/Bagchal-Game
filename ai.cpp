#include "ai.h"
#include "utils.h"
#include <vector>
using namespace std;

// Goat AI
Move goatAI(vector<vector<char>> board,bool placementPhase){
    Move m;
    m.capture=false;

    if(placementPhase){
        for(int i=0;i<5;i++)
            for(int j=0;j<5;j++)
                if(board[i][j]=='.'){
                    m.r1=-1; m.c1=-1; m.r2=i; m.c2=j;
                    return m;
                }
    }

    for(int r=0;r<5;r++)
        for(int c=0;c<5;c++)
            if(board[r][c]=='G'){
                for(int dr=-1;dr<=1;dr++)
                    for(int dc=-1;dc<=1;dc++){
                        int nr=r+dr,nc=c+dc;
                        if(validIndex(nr,nc) && board[nr][nc]=='.'){
                            m.r1=r; m.c1=c; m.r2=nr; m.c2=nc;
                            return m;
                        }
                    }
            }

    m.r1=m.c1=m.r2=m.c2=-1;
    return m;
}

// Tiger AI
Move tigerAI(vector<vector<char>> board){
    Move m;
    m.capture=false;

    // try capture first
    for(int r=0;r<5;r++)
        for(int c=0;c<5;c++)
            if(board[r][c]=='T'){
                for(int dr=-2;dr<=2;dr++)
                    for(int dc=-2;dc<=2;dc++){
                        int nr=r+dr,nc=c+dc;
                        if(validIndex(nr,nc) && board[nr][nc]=='.'){
                            int mr=r+dr/2, mc=c+dc/2;
                            if(validIndex(mr,mc) && board[mr][mc]=='G'){
                                m.r1=r; m.c1=c; m.r2=nr; m.c2=nc; m.capture=true;
                                return m;
                            }
                        }
                    }
            }

    // normal move
    for(int r=0;r<5;r++)
        for(int c=0;c<5;c++)
            if(board[r][c]=='T'){
                for(int dr=-1;dr<=1;dr++)
                    for(int dc=-1;dc<=1;dc++){
                        int nr=r+dr,nc=c+dc;
                        if(validIndex(nr,nc) && board[nr][nc]=='.'){
                            m.r1=r; m.c1=c; m.r2=nr; m.c2=nc;
                            return m;
                        }
                    }
            }

    m.r1=m.c1=m.r2=m.c2=-1;
    return m;
}