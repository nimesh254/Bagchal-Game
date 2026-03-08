#include "ai.h"
#include <cstdlib>


static bool validIndex(int r,int c){
    return r>=0 && r<SIZE && c>=0 && c<SIZE;
}

bool diagonalAllowed(int r,int c){
    return (r%2==c%2);
}

// ================= GOAT AI =================
Move goatAI(vector<vector<char>> board,bool placementPhase){
    Move m;
    m.capture=false;

    if(placementPhase){
        for(int i=0;i<SIZE;i++)
            for(int j=0;j<SIZE;j++)
                if(board[i][j]=='.'){
                    m.r1=-1;
                    m.c1=-1;
                    m.r2=i;
                    m.c2=j;
                    return m;
                }
    }

    int dr[8]={1,-1,0,0,1,1,-1,-1};
    int dc[8]={0,0,1,-1,1,-1,1,-1};

    for(int r=0;r<SIZE;r++)
    for(int c=0;c<SIZE;c++)
    if(board[r][c]=='G'){

        for(int k=0;k<8;k++){
            int nr=r+dr[k];
            int nc=c+dc[k];
            if(!validIndex(nr,nc)) continue;
            if(board[nr][nc]!='.') continue;
            if(k>=4 && !diagonalAllowed(r,c)) continue;

            m.r1=r;
            m.c1=c;
            m.r2=nr;
            m.c2=nc;
            return m;
        }
    }

    m.r1=m.c1=m.r2=m.c2=-1;
    return m;
}

// ================= TIGER AI =================
Move tigerAI(vector<vector<char>> board){
    Move m;
    m.capture=false;

    int dr[8]={2,-2,0,0,2,2,-2,-2};
    int dc[8]={0,0,2,-2,2,-2,2,-2};

    // capture first
    for(int r=0;r<SIZE;r++)
    for(int c=0;c<SIZE;c++)
    if(board[r][c]=='T'){

        for(int k=0;k<8;k++){
            int nr=r+dr[k];
            int nc=c+dc[k];
            int mr=r+dr[k]/2;
            int mc=c+dc[k]/2;

            if(nr<0 || nr>=SIZE || nc<0 || nc>=SIZE) continue;
            if(mr<0 || mr>=SIZE || mc<0 || mc>=SIZE) continue;

            if(board[nr][nc]=='.' && board[mr][mc]=='G'){
                if(k>=4 && !(r%2==c%2)) continue;

                m.r1=r;
                m.c1=c;
                m.r2=nr;
                m.c2=nc;
                m.capture=true;
                return m;
            }
        }
    }

    int dr2[8]={1,-1,0,0,1,1,-1,-1};
    int dc2[8]={0,0,1,-1,1,-1,1,-1};

    // normal move
    for(int r=0;r<SIZE;r++)
    for(int c=0;c<SIZE;c++)
    if(board[r][c]=='T'){

        for(int k=0;k<8;k++){
            int nr=r+dr2[k];
            int nc=c+dc2[k];
            if(!validIndex(nr,nc)) continue;
            if(board[nr][nc]!='.') continue;
            if(k>=4 && !(r%2==c%2)) continue;

            m.r1=r;
            m.c1=c;
            m.r2=nr;
            m.c2=nc;
            return m;
        }
    }

    m.r1=m.c1=m.r2=m.c2=-1;
    return m;
}