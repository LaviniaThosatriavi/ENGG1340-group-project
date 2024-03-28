#include <iostream>
#include <time.h>

using namespace std;

const int row = 5;
const int col = 5;
const string red = "\033[1;41m";
const string green = "\033[1;42m";
const string yellow = "\033[1;43m";
const string blue = "\033[1;44m";
const string reset = "\033[0m";
int arr[row][col];
int monsterHealth = 90;
const int monsterMaxHealth = 100;

void create_board(){// tracy 
    srand(time(0));
    for (int i=0; i< row; i++)
        for (int j=0; j< col; j++)
            arr[i][j] = 1 + (rand() % 4);
}

void prompt_user_move(){ //henry
    // get the user move and feed into move stones 
}
void move_stones(char move,int s_row,int s_col){
    //this function basically move the stone according to the user selected move and selected stone
    //input : move(wasd) , s_row(starting row ),s_col(starting column)
    //output: update the board base on the user movement 


    int start_stone= arr[s_row][s_col];// this is the starting stone being selected to connect
    int current_stone=start_stone; // this is to keep track of the current stone being connected
    int c_row=s_row;// the current row is the starting row
    int c_col=s_col;// the current column is the strating column

    while(true){
        // check out of range 
    if (move=='w'){//when stone is connected upward
        //later need to add whether the move is valid 
        int next_stone = arr[c_row-1][c_col];// get the stone to be connected with
        if (next_stone==current_stone){// check whether the 2 are the same type 
            c_row=c_row-1;
        }
        else{
            break ;// if the stones are not the same type break out of the loop 
        }
    }

    else if (move=='a'){// when stone being moved to left
        int next_stone = arr[c_row][c_col-1];// get the stone to be connected with
        if (next_stone==current_stone){// check whether the 2 are the same type 
            c_col=c_col-1;
        }
        else{
            break ;// if the stones are not the same type break out of the loop 
        }
       
    }

    else if (move=='s'){// when stone being moved to downward
        int next_stone = arr[c_row+1][c_col];// get the stone to be connected with
        if (next_stone==current_stone){// check whether the 2 are the same type 
            c_row=c_row+1;
        }
        else{
            break ;// if the stones are not the same type break out of the loop 
        }
    }

    else if (move =='d'){// when stone being mooved to right 
        int next_stone = arr[c_row][c_col+1];// get the stone to be connected with
        if (next_stone==current_stone){// check whether the 2 are the same type 
            c_col=c_col+1;
        }
        else{
            break ;// if the stones are not the same type break out of the loop 
        }
    }

    else{
        cout<<"move not valid";
    }
    
    // return a vector for the print board function 
    // update board 
    // print the board out 
}
}


void remove_stones_after_connection(){

}

void regenearte_stones(){

}

void calculate_score_for_each_stone(){
    // stone type 1 : refill health bar 
    // stone type 2: skip a round of monster attack
    // stone type 3 : normal attack 
    // stone type 4 : double the next attack 
}

void print_monster(){
    cout << " ʕ•ᴥ•ʔ" << endl;
    cout << "/(   )\\" << endl;
    cout << " ^^ ^^" << endl; 
}

void print_monster_health_bar(){
    const int barWidth = 20;
    cout << "Monster Health: [";
    double healthPercentage = static_cast<double>(monsterHealth) / monsterMaxHealth;
    int filledBarWidth = static_cast<int>(healthPercentage * barWidth);
    for (int i = 0; i < filledBarWidth; i++){
        cout << "#";
    }
    for (int i = filledBarWidth; i < barWidth; i++) {
        cout << "-";
    }
    cout << "]" << endl;

}

void print_board(){
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (arr[i][j] == 1) {
                cout << red << " " << reset << " ";
            } else if (arr[i][j] == 2) {
                cout << green << " " << reset << " ";
            } else if (arr[i][j] == 3) {
                cout << yellow << " " << reset << " ";
            } else if (arr[i][j] == 4) {
                cout << blue << " " << reset << " ";
            }
        }
        cout << endl;
        cout << endl;
    }
}

int main() {
    print_monster();
    print_monster_health_bar();
    create_board();
    print_board();
    return 0;
}