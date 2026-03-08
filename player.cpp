#include "player.h"
#include <iostream>
using namespace std;

// Check if coordinates are inside the board
static bool validIndex(int r,int c){
    return r>=0 && r<SIZE && c>=0 && c<SIZE;
}

// Goat move / placement
Move playerMoveGoat(vector<vector<char>> &board, bool placementPhase){
    Move m;
    while(true){
        if(placementPhase)
            cout<<"Goat placement (row col): ";
        else
            cout<<"Goat move (r1 c1 r2 c2): ";

        if(placementPhase){
            cin>>m.r2>>m.c2;
            m.r1=m.c1=-1;
            if(!cin.good() || !validIndex(m.r2,m.c2) || board[m.r2][m.c2]!='.'){
                cout<<"Invalid input, try again.\n";
                cin.clear(); cin.ignore(10000,'\n');
                continue;
            }
        } else {
            cin>>m.r1>>m.c1>>m.r2>>m.c2;
            if(!cin.good() || !validIndex(m.r1,m.c1) || !validIndex(m.r2,m.c2) ||
               board[m.r1][m.c1]!='G' || board[m.r2][m.c2]!='.'){
                cout<<"Invalid move, try again.\n";
                cin.clear(); cin.ignore(10000,'\n');
                continue;
            }
        }
        break;
    }
    return m;
}

// Tiger move with selection from all available tigers
Move playerMoveTiger(vector<vector<char>> &board){
    Move m;
    vector<pair<int,int>> tigers;
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(board[i][j]=='T')
                tigers.push_back({i,j});

    int choice=-1;
    while(true){
        cout<<"Available tigers:\n";
        for(size_t i=0;i<tigers.size();i++)
            cout<<i+1<<". ("<<tigers[i].first<<","<<tigers[i].second<<")\n";
        cout<<"Choose tiger to move (1-" << tigers.size() << "): ";
        cin>>choice;
        if(!cin.good() || choice<1 || choice>(int)tigers.size()){
            cout<<"Invalid choice. Try again.\n";
            cin.clear(); cin.ignore(10000,'\n');
            continue;
        }
        break;
    }

    m.r1 = tigers[choice-1].first;
    m.c1 = tigers[choice-1].second;

    while(true){
        cout<<"Enter destination row and column: ";
        cin>>m.r2>>m.c2;
        if(!cin.good() || !validIndex(m.r2,m.c2)){
            cout<<"Invalid coordinates. Try again.\n";
            cin.clear(); cin.ignore(10000,'\n');
            continue;
        }

        int dr = m.r2 - m.r1;
        int dc = m.c2 - m.c1;
        bool isCapture = (abs(dr)==2 || abs(dc)==2) &&
                         validIndex(m.r1+dr/2,m.c1+dc/2) &&
                         board[m.r1+dr/2][m.c1+dc/2]=='G';

        if((board[m.r2][m.c2]=='.') && (isCapture || 
           (abs(dr)<=1 && abs(dc)<=1 && (dr==0||dc==0 || (dr==1&&dc==1 && m.r1%2==m.c1%2))))){
            m.capture=isCapture;
            break;
        } else {
            cout<<"Illegal move. Try again.\n";
        }
    }
    return m;
}