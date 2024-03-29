#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

const int row = 5;
const int col = 5;
const string bred = "\033[1;41m"; // background red
const string bgreen = "\033[1;42m"; // background green
const string byellow = "\033[1;43m"; // background yellow
const string bblue = "\033[1;44m"; // background blue
const string fblack = "\033[30m"; // foreground magenta
const string reset = "\033[0m"; // reset color
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

char prompt_user_move(vector<int> stone_position, int row, int col) {
    char move;
    int current_stone_column = stone_position[0];
    int current_stone_row = stone_position[1];
    vector<char> valid_move;
    valid_move.push_back('w');
    valid_move.push_back('a');
    valid_move.push_back('s');
    valid_move.push_back('d');
    cout << "Please select a move using 'w', 'a', 's', or 'd': ";
    cin >> move;

    // Check if the move is valid
    while (find(valid_move.begin(), valid_move.end(), move) == valid_move.end()) {
        cout << "Invalid move. Please choose a move using 'w', 'a', 's', or 'd': ";
        cin >> move;
    }

    // Check if the move is within range
    while (true) {
        // Break out of the loop when the move is valid and within range
        if ((move == 'w' && current_stone_row - 1 >= 0) ||
             (move == 'a' && current_stone_column - 1 >=0) ||
             (move == 's' && current_stone_row + 1 < row) ||
             (move == 'd' && current_stone_column + 1 < col)) {
            break;
        }
        else{
            cout << "Move out of range. Please choose another move: ";
            cin >> move;
        }
    }

    return move;
}



vector<int> prompt_stone_position(int board_row,int board_col){ //henry

    int row;
    int column;
    vector<int> position;
    // 2 do while loop to check whether the selected posiiton is on the board 
    do {
        cout<<"please select the column of the stone which you would like to connect from";
        cin>>column;}

    while(column>=board_col||column<0);

    position.push_back(column);

    do {
        cout<<"please select the row of the stone which you would like to connect from";
        cin>>row;}
    while(row>=board_row||row<0);

    position.push_back(row);


    // index 0 is column , index 1 is row 
    return position ;
}


void move_stones(char move,int s_row,int s_col){
    //this function basically move the stone according to the user selected move and selected stone
    //input : move(wasd) , s_row(starting row ),s_col(starting column)
    //output: update the board base on the user movement 

    int start_stone= arr[s_row][s_col];// this is the starting stone being selected to connect
    int current_stone=start_stone; // this is to keep track of the current stone being connected
    int c_row=s_row;// the current row is the starting row
    int c_col=s_col;// the current column is the strating column
    int number_of_connections=0;
    vector <vector<int> > connection_history;
    connection_history[number_of_connections][0]=s_col;// set the initial connection as the starting posiiton
    connection_history[number_of_connections][1]=s_row;
    

    while(true){
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
    number_of_connections+=1;
    connection_history[number_of_connections][0]=c_col;// appending the position of the connection 
    connection_history[number_of_connections][1]=c_row;

    // print the board out , the connection will be passed into the print board function
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
    vector<int> result(2);
    result[0] = stoneType;
    result[1] = score;
    return result;
}

void execute_stone_actions(vector<int> stone) {
    if (stone.size() < 2) {
        cout << "No stone actions to execute." << endl;
        return;
    }
    int stoneType = stone[0];
    int score = stone[1];
    int attack = score + nextAttack;
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

bool isVectorInVector(const vector<vector<int> >& outer, const vector<int>& target) {
    for (size_t i = 0; i < outer.size(); i++) {
        if (outer[i] == target) {
            return true;
        }
    }
    return false;
}

void print_board(vector <vector<int> > connectedStones){
    // * = current stone
    // • = connected stone
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            vector<int> temp(2);
            temp[0] = i;
            temp[1] = j;
            bool t = isVectorInVector(connectedStones, temp);
            if (arr[i][j] == 1) {
                if (connectedStones.back() == temp) {
                    cout << bred << fblack << "*" << reset << " ";
                } else if (t){
                    cout << bred << fblack << "•" << reset << " ";
                } else {
                    cout << bred << " " << reset << " ";
                }
            } else if (arr[i][j] == 2) {
                if (connectedStones.back() == temp) {
                    cout << bgreen << fblack << "*" << reset << " ";
                } else if (t){
                    cout << bgreen << fblack << "•" << reset << " ";
                } else {
                    cout << bgreen << " " << reset << " ";
                }
            } else if (arr[i][j] == 3) {
                if (connectedStones.back() == temp) {
                    cout << byellow << fblack << "*" << reset << " ";
                } else if (t){
                    cout << byellow << fblack << "•" << reset << " ";
                } else {
                    cout << byellow << " " << reset << " ";
                }
            } else if (arr[i][j] == 4) {
                if (connectedStones.back() == temp) {
                    cout << bblue << fblack << "*" << reset << " ";
                } else if (t){
                    cout << bblue << fblack << "•" << reset << " ";
                } else {
                    cout << bblue << " " << reset << " ";
                }
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
    vector <vector<int> > connectedStones;
    vector<int> temp(2);
    temp[0] = 1;
    temp[1] = 2;
    connectedStones.push_back(temp);
    temp[0] = 2;
    temp[1] = 2;
    connectedStones.push_back(temp);
    temp[0] = 1;
    temp[1] = 3;
    connectedStones.push_back(temp);
    print_board(connectedStones);
    print_player_health_bar();
    return 0;
}
