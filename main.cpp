//
//  main.cpp
//  tic-tac-toe_with_minimax
//
//  Created by Rejwana Haque on 2020-03-06.
//


#include <iostream>
#include <list>
#include <algorithm>

using namespace std;
class Move;

class Board
{
    //char position[3][3]={{'x','o',' '},{'o',' ',' '},{'x',' ',' '}};
    char position[3][3];

    
public:
    int value;
    Board()
    {
        for (int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                position[i][j] = ' ';
            }
        }
    }
    

    void show_board();
    void set_mark(char mark, int row, int col);

    
    friend bool chkgameover(Board &b);
    //friend void empty_cells(Board &b, int &row, int &col);
    friend list<Move> legal_moves(Board &b);
    friend int minimax(Board &b,char mark);
    
};


class Move
{
public:
    
    int row,col;
public:
    void set_move(int x, int y)
    {
        row=x;
        col=y;
    }
    //Move *next;
};


//draw board
void Board::show_board()
{
    for (int i=0;i<3;i++){
        cout <<endl<< "     |     |     |" << endl;
        for(int j=0;j<3;j++)
            cout<<"  "<<position[i][j]<<"  |";
        cout <<endl<< "_____|_____|_____|" ;
    }
    cout<<endl;
    
}



void Board::set_mark(char mark, int row, int col)
{
    
    //check legality for user input
    while(position[row][col]!=' '){
        cout<<"invalid move select again"<<endl;
        cout<<"select row:";
        cin>>row;
        row--;
        cout<<"select col";
        cin>>col;
        col--;
    }
    
    position[row][col] = mark;
}

// take player selection and put x/o on the specific cell
void play(Board &b, char mark, Move *best_move=NULL)
{
    int row,col;
    if(best_move==NULL)
    {
        
        cout<<"select row:";
        cin>>row;
        row--;
        cout<<"select clo:";
        cin>>col;
        col--;
        
    }
    else{
        row = best_move->row;
        col = best_move->col;
    }
    
    
    
    b.set_mark(mark, row,col);
    
    
}


//check if leaf node
bool chkgameover(Board &b)
{
    //bool allCellMarked=true; // check if all cells are played
    
    //diagonal win
    
    if(b.position[0][0]==b.position[1][1] && b.position[1][1] ==b.position[2][2]&&b.position[0][0]!= ' ')
    {
        if(b.position[0][0]== 'x')
            b.value=1;
        else
            b.value=-1;

        return true;
    }
    else if(b.position[0][2]==b.position[1][1] && b.position[1][1]==b.position[2][0] && b.position[0][2]!=' ')
    {
        if(b.position[0][2]== 'x')
            b.value=1;
        else
            b.value=-1;

        return true;
    }
    
    //row or column win
    else
    {
        for (int i=0;i<3;i++)
        {
            //row win
            if(b.position[i][0]==b.position[i][1] && b.position[i][1]==b.position[i][2] && b.position[i][0]!=' ')
            {
                if(b.position[i][0]== 'x')
                    b.value=1;
                else
                    b.value=-1;

            
                return true;
            }
            //column win
            else if(b.position[0][i]==b.position[1][i] && b.position[1][i]==b.position[2][i] && b.position[0][i]!=' ')
            {
                if(b.position[0][i]== 'x')
                    b.value=1;
                else
                    b.value=-1;

                return true;
            };
        }
    }
    

    


    //check if all cells are marked
    if (all_of(&b.position[0][0], &b.position[2][2], [](char x){return x!=' ';}))
    {
        b.value=0;
        return true;
    }
    else
    {
        return false;
    }


}


//list of legal moves
list<Move> legal_moves(Board &b)
{
    list<Move> move_list;
    Move new_move;
    for (int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(b.position[i][j]==' ')
            {
                new_move.set_move(i,j);
                move_list.push_back(new_move);
            }
    return move_list;
    
}

int minimax(Board &b,char mark, Move &best_move)
{
    int best_value; //holds the best possible outcome from current position
    
    //b.show_board();
    list <Move> move_list;
    Move new_move;

    
    //if terminal position is reached return the board value
    if(chkgameover(b))
    {
        //cout<<"minimax value returned "<<b.value<<endl;
        return b.value;
    }
    
  
    else{
        
        //get all the legal moves
        move_list= legal_moves(b);
        
        //initialize best value to a large negative for max and vice versa
        best_value=(mark=='x')?-10:10;
        
        //check all legal moves
        //while (move_list!=NULL)
        while(move_list.size()> 0){
            Board new_board = b;
            new_move = move_list.front();
            new_board.set_mark(mark, new_move.row, new_move.col);
            
            //max player
            if(mark=='x')
            {
                //value of the child positions
                new_board.value = minimax(new_board, 'o', best_move);
                //best move from current position
                if(new_board.value>best_value)
                {
                    best_value=new_board.value;
                    best_move = new_move;
                }
            }
            
            //min player
            else{
                //value of the child positions
                new_board.value = minimax(new_board, 'x', best_move);
                //best move from current position
                if(new_board.value<best_value)
                {
                    best_value=new_board.value;
                    best_move = new_move;
                }
            }
            
            //cout<<"new board value"<<new_board.value<<"best value"<<best_value<<"mark"<<mark<<endl;
            
            //remove checked move from list
            move_list.pop_front();
        }
        b.value = best_value;
        

        return b.value;
    }
    
}


int main(int argc, const char * argv[]) {
    
    Board b1;
    int player =1; //human player. player 2 minimax player
    int gameOutcome;
    char mark;
    Move best_move;
  

    mark=(player == 1) ? 'x' : 'o';
    
    //only start if game is not over
    bool gameover = chkgameover(b1);
    
    //need to rewrite this section
    while(gameover==false)
    {
        b1.show_board();

        //cout<<"game value"<<b1.value<<endl;
        cout<<"player to play"<<player<<endl;
        
        //if computer player
        if(player == 2)
        {
            b1.value = minimax(b1, mark, best_move);
            //update board value basesd on minimax game outcome

            play(b1, mark, &best_move);
            
        }
        
        //if human player
        else{
            play(b1, mark);
        }
        
        gameover = chkgameover(b1);
        
        //switch player
        player=(player%2==0)?1:2;
        mark=(player == 1) ? 'x' : 'o';
        
    }
    
    b1.show_board();
    
    //calculate final game outcome
    gameOutcome = minimax(b1, mark, best_move);

    
    if(gameOutcome==0)
        cout<<"Game drawn"<<endl;
    
    else
    {
        int winner=(gameOutcome==1)?1:2;
        
        cout<<"Game Over! Winner is player"<<winner<<endl;
    }

    return 0;
}

