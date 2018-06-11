//
//  main.cpp
//  ConnectFour
//
//  Created by Jiakai Chen on 6/8/18.
//  Copyright © 2018 Jiakai Chen. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

/* Structure:
 * Hold Player's Name and PlayerID;
 */
struct player{
    string playerName;  //record the name of player 1 and player2
    int playerId;       // 'X' for player1 or 'O' for player2
};

void DisplayBoard ( char board[][10] );
int PlayerMove (player activePlayer, char board[][10] );
void DropTheMove(int move,player activePlayer, char board[][10]);
bool CheckWin(player activePlayer, char board[][10]);
bool CheckFull(char board[][10]);
bool RestartGame(char board[][10]);

int main(int argc, const char * argv[]) {
    
    player p1, p2;
    bool win = false;
    bool full = false;
    bool restart = false;
    char board[9][10];
    int move;
    
    cout << endl << "Hello! Welcome to my Connect Four game play!" << endl;
    //player1 Name
    cout << "Player1's Name: ";
    cin >> p1.playerName;
    p1.playerId = 'X';
    cout << "Welcome " << p1.playerName << " join the game!" << endl;
    //player2 Name
    cout << "Player2's Name: ";
    cin >> p2.playerName;
    p2.playerId = 'O';
    cout << "Welcome " << p2.playerName << " join the game!" << endl << endl;
    //Press to start the game
    
    cout << "********************************************" << endl << "* Player 1: " << p1.playerName << " Hold: X" << endl;
    cout << "* Player 2: " << p2.playerName << " Hold: O" << endl;
    cout << "* Are you ready to start a new game?" << endl << "********************************************" <<endl;
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
    cout << endl;
    
    while(true){
        while (!win){
            DisplayBoard(board);
            move = PlayerMove(p1,board);
            DropTheMove(move, p1, board);
            full = CheckFull(board);
            if (full){
                DisplayBoard(board);
                cout << " Draw!!! The board is full!" << endl;
                restart = RestartGame(board);
                if (restart == false){
                    return 0;
                }
            }
            win = CheckWin(p1, board);
            if(win){
                DisplayBoard(board);
                cout << endl << "******************************" << endl << "* Player: " << p1.playerName << "(" << string(1,p1.playerId) << ") " << " Win!" << endl << "******************************" << endl;
                restart = RestartGame(board);
                if (restart == false){
                    return 0;
                }else{
                    win = !win;
                }
            }
            if (!win){
                DisplayBoard(board);
                move = PlayerMove(p2,board);
                DropTheMove(move, p2, board);
                full = CheckFull(board);
                if (full){
                    DisplayBoard(board);
                    cout << endl << " *** Draw!!! The board is full! ***" << endl << endl;
                    restart = RestartGame(board);
                    if (restart == false){
                        return 0;
                    }
                }
                win = CheckWin(p2, board);
                if(win){
                    DisplayBoard(board);
                    cout << endl <<"******************************" << endl << "* Player: " << p2.playerName << "(" << string(1,p2.playerId) << ") " << " Win!" << endl << "******************************" << endl;
                    restart = RestartGame(board);
                    if (restart == false){
                        return 0;
                    }else{
                        win = !win;
                    }
                }
                
                
            }
        }
    }
    return 0;
}

void DisplayBoard ( char board[][10] )
{
    cout << endl;
    cout << "    " ;
    cout << "     Connect Four!" <<endl<<endl;
    int rows = 6, columns = 7;
    
    for(int i = 1; i <= rows; i++)
    {
        cout << "| | ";
        for(int j = 1; j <= columns; j++)
        {
            if(board[i][j] != 'X' && board[i][j] != 'O')
                board[i][j] = '*';
            
            cout << board[i][j];
            cout << " | ";
            
        }
        cout << "|" << endl << "  -----------------------------"<< endl;
    }
    
}

int PlayerMove (player activePlayer, char board[][10]){
    string move;
    
    while(atoi(move.c_str()) < 1 || atoi(move.c_str()) > 7){
        
        cout << "Now is " << activePlayer.playerName << "'s move" << "(" << string(1,activePlayer.playerId) << ") "<< endl;
        cout << "Type in the column number (1~7) you want to drop: ";
        cin >> move;
        while(board[1][atoi(move.c_str())] == 'X' || board[1][atoi(move.c_str())] == 'O'){
            cout << "*** Warning: The column is full! Choose another column to drop your move! *** " << endl;
            cin  >> move;
        }
        if(atoi(move.c_str()) < 1 || atoi(move.c_str()) > 7){
            cout << endl << "*** Warning: You need to choose a column from 1 to 7! ***" << endl << endl;
        }
    }
    return atoi(move.c_str());
}

void DropTheMove(int move, player activePlayer, char board[][10]){
    int adjusting = 1;
    int row = 6;
    while(adjusting){
        if (board[row][move] != 'X' && board[row][move] != 'O'){
            board[row][move] = activePlayer.playerId;
            adjusting = 0;
        }
        row--;
    }
}

bool CheckWin(player activePlayer, char board[][10]){
    char playerRole = activePlayer.playerId;
    bool win = false;
    for (int i = 6; i>=1; i--){
        for (int j = 7; j >=1; j--){
            
            if(board[i][j] == playerRole && board[i-1][j] == playerRole && board[i-2][j] == playerRole && board[i-3][j] == playerRole){
                win = true;
            }
            
            if(board[i][j] == playerRole && board[i][j-1] == playerRole && board[i][j-2] == playerRole && board[i][j-3] == playerRole){
                win = true;
            }
            
            if(board[i][j] == playerRole && board[i-1][j-1] == playerRole && board[i-2][j-2] == playerRole && board[i-3][j-3] == playerRole){
                win = true;
            }
            
            if(board[i][j] == playerRole && board[i-1][j+1] == playerRole && board[i-2][j+2] == playerRole && board[i-3][j+3] == playerRole){
                win = true;
            }
            
        }
    }
    return win;
}

bool CheckFull(char board[][10]){
    bool full = true;
    for(int i = 1; i<8;i++){
        if(board[0][i] != 'X' && board[0][i] != 'O')
            full = false;
    }
    return full;
}

bool RestartGame(char board[][10]){
    string choice;
    cout << endl << "Do you want to have another Game?(Type in the Number)" << endl << "(1)YES  (2)NO " << endl << endl;
    cout << "***** For a fair game, the offensive(1st) position will be the defensive(2nd) position in the next run! *****" << endl << endl;
    cin >> choice;
    while(atoi(choice.c_str()) != 1 || atoi(choice.c_str()) != 2){
    if (atoi(choice.c_str()) == 1){
        for(int i = 1; i <= 6; i++)
        {
            for(int j = 1; j <= 7; j++)
            {
                board[i][j] = '*';
            }
        }
        DisplayBoard(board);
        cout << "Game Restarted. HAVE FUN! " << endl;
        return true;
    }
    else if (atoi(choice.c_str()) == 2){
        cout << "Goodbye. Have a nice day!" << endl;
        return false;
    }
    else{
        cout << "I know you want to have another game, but please enter the right number! (1: Restart Game 2: Game Over)" << endl;
        cin >> choice;
    }
    }
    
    return false;
}

