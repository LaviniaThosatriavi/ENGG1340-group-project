#include <iostream>
#include <time.h>
#include <vector>

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
int playerHealth = 100;
const int playerMaxHealth = 100;
int nextAttack = 0;
bool monsterAttack = true;

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

vector<int> calculate_score_for_each_stone(int stoneType, int numStones){
    // stone type 1 : refill player's health bar 
    // stone type 2 : skip a round of monster attack
    // stone type 3 : normal attack 
    // stone type 4 : increase the next attack
    int score = 0;
    switch (stoneType) {
        case 1:
        // stone type 1 : refill player health bar 
            score = numStones * 5;
            break;
        case 2:
        // stone type 2 : skip a round of monster attack
            score = numStones * 3;
            break;
        case 3:
        // stone type 3: normal attack by user
            score = numStones * 5;
            break;
        case 4:
        // stone type 4: increase the next attack
            score = numStones * 3;
            break;
        default:
            // Invalid stone type
            cout << "Invalid stone type." << endl;
            break;
    }
    return {stoneType, score};
}

void execute_stone_actions(vector<int> stone) {
    if (stone.size() < 2) {
        cout << "No stone actions to execute." << endl;
        return;
    }
    int stoneType = stone[0];
    int score = stone[1];
    switch (stoneType) {
        case 1:
            // Stone type 1: Refill health bar
            cout << "Refilling player's health bar " << score << endl;
            playerHealth += score;
            break;

        case 2:
            // Stone type 2: Skip a round of monster attack
            cout << "Skip round of monster attack." << endl;
            monsterAttack = false;
            break;

        case 3:
            // Stone type 3: Normal attack
            int attack = score + nextAttack;
            cout << "You damaged the monster with attack " << attack << endl;
            monsterHealth -= attack;
            nextAttack = 0;
            break;
        
        case 4:
            // Stone type 4: 
            cout << "Increasing the next attack by " << score << endl;
            nextAttack += score;
            break;

        default:
            // Invalid stone type
            cout << "Invalid stone type." << endl;
            break;
    }
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

void print_player_health_bar(){
    const int barWidth = 20;
    cout << "Player Health: [";
    double healthPercentage = static_cast<double>(playerHealth) / playerMaxHealth;
    int filledBarWidth = static_cast<int>(healthPercentage * barWidth);
    for (int i = 0; i < filledBarWidth; i++){
        cout << "#";
    }
    for (int i = filledBarWidth; i < barWidth; i++) {
        cout << "-";
    }
    cout << "]" << endl;
}

void print_board(vector<vector<int>>& connectedStones){

    vector<int> start = connectedStones[0];
    vector<int> next = connectedStones[1];

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
    vector<vector<int>> connectedStones = {{1,2},{1,3}};
    print_board(connectedStones);
    print_player_health_bar();
    return 0;
}