#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

const int row = 5;
const int col = 5;
const string bred = "\033[1;41m"; // background red
const string bgreen = "\033[1;42m"; // background green
const string byellow = "\033[1;43m"; // background yellow
const string bblue = "\033[1;44m"; // background blue
const string fblack = "\033[30m"; // foreground magenta
const string reset = "\033[0m"; // reset color
int arr[row][col];// it is the board 
int monsterHealth = 90;
const int monsterMaxHealth = 100;
int playerHealth = 100;
const int playerMaxHealth = 100;
int nextAttack = 0;
bool monsterAttack = true;

struct gamestatus// a structure used to save all the game status 
{
    int MonsterH;
    int PlayerH;
    int board[row][col];
};
bool isVectorInVector(const vector<vector<int> >& outer, const vector<int>& target) {// check whther the current stone is in the connected stone history 
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
            temp[0] = j;
            temp[1] = i;
            bool t = isVectorInVector(connectedStones, temp);
            bool empty = connectedStones.empty();
            if (arr[i][j] == 1) {
                if (!empty && connectedStones.back() == temp) {
                    cout << bred << fblack << "*" << reset << " ";
                } else if (t){
                    cout << bred << fblack << "•" << reset << " ";
                } else {
                    cout << bred << " " << reset << " ";
                }
            } else if (arr[i][j] == 2) {
                if (!empty && connectedStones.back() == temp) {
                    cout << bgreen << fblack << "*" << reset << " ";
                } else if (!empty && t){
                    cout << bgreen << fblack << "•" << reset << " ";
                } else {
                    cout << bgreen << " " << reset << " ";
                }
            } else if (arr[i][j] == 3) {
                if (!empty && connectedStones.back() == temp) {
                    cout << byellow << fblack << "*" << reset << " ";
                } else if (!empty && t){
                    cout << byellow << fblack << "•" << reset << " ";
                } else {
                    cout << byellow << " " << reset << " ";
                }
            } else if (arr[i][j] == 4) {
                if (!empty && connectedStones.back() == temp) {
                    cout << bblue << fblack << "*" << reset << " ";
                } else if (!empty && t){
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


void writeStructToFile(const gamestatus& data, const std::string& filename) {
    // Open the file in binary mode for writing
    ofstream fout(filename, std::ios::binary);
    if (fout) {
        // Write the binary representation of the structure to the file
        fout.write(reinterpret_cast<const char*>(&data), sizeof(gamestatus));
        fout.close();
        cout << "Structure data written to file." << endl;
    } else {
        cout << "Failed to open file for writing." << endl;
    }
}

// Function to read structure data from a file
gamestatus readStructFromFile(const std::string& filename, int default_ph, int default_mh,int default_b[row][col]) {
    gamestatus data;
    data.PlayerH=default_ph;// set the default value of the player health 
    data.MonsterH=default_mh;// set the default value of the monster heatlth 
    for(int i=0;i<row;i++){// set the default value of the board 
        for (int j=0;j<col;j++){
            data.board[i][j]=default_b[i][j];
        }
    }
    // Open the file in binary mode for reading
    ifstream fin(filename, ios::binary);
    if (fin) {
        // Read the binary data from the file into the structure
        fin.read(reinterpret_cast<char*>(&data), sizeof(gamestatus));
        fin.close();
        cout << "Structure data read from file." << endl;
    } else {
        // we create a file for them 
        ofstream file(filename);
        cout <<"we have created a file for you name" <<filename<< endl;
    }
    return data;
}


// to change the value of player health , monster health and board content to the values from last game status 
void updatestatus(int& player_health,int& monster_health,gamestatus update){
    // input : player_health , monster_health and data from last game status, all pass by refernece so the values are modified 
    // process: to update the values of player health , monter health and the board position , importing data from the last game 
    player_health= update.PlayerH;
    monster_health= update.MonsterH;
    for(int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            arr[i][j]=update.board[i][j];
        }
    }
}

void create_board(){// tracy 
    srand(time(0));
    for (int i=0; i< row; i++)
        for (int j=0; j< col; j++)
            arr[i][j] = 1 + (rand() % 4);
}

char prompt_user_move(vector<int> stone_position, int row, int col) {
    // get the user move from this function , it will perform checks of whthe the move is valid 
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
    // it ask for the position of the stone to start with 
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


int move_stones(int s_row,int s_col){
    //this function basically connect the stone according to the user selected move and selected stone
    //input : s_row(starting row ),s_col(starting column)
    //output: the number of successfuk connections 

    int start_stone= arr[s_row][s_col];// this is the starting stone being selected to connect
    int current_stone=start_stone; // this is to keep track of the current stone being connected
    int c_row=s_row;// the current row is the starting row
    int c_col=s_col;// the current column is the strating column
    int number_of_connections=0;
    vector <vector<int> > connection_history;
    vector <int> temp(2);
    temp[0]=s_col;// set the initial connection as the starting posiiton
    temp[1]=s_row;
    connection_history.push_back(temp);

    while(true){
        vector<int> stone_position={c_col,c_row};
        char move = prompt_user_move(stone_position,row,col);// prompt the user for the move

        if (move=='w'){//when stone is connected upward
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
    vector <int> connection(2);

    connection[0]=c_col;// appending the position of the connection 
    connection[1]=c_row;
    connection_history.push_back(connection);

    // print the board out , the connection will be passed into the print board function
    //print_board(connection_history);
    print_board(connection_history);
    }
    return number_of_connections;
}


void remove_stones_after_connection(){// replace the connected stones with zero 

}


void regenearte_stones(){// animation 

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
            // Stone type 4: increasing attack 
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
    cout << "]" ;
    cout<<" "<<monsterHealth<<"\n";

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
    cout << "]" ;
    cout<<" "<<playerHealth<<"\n";
}
void print_instructions(){
    cout<<"the game works like this"<<"\n";
}

// function to check whether the game has ended
bool game_ended(int player_health , int monster_health){
    // the game ends when either player health or monster health goes to zero 
    if (player_health<=0){
        cout << "unlucky you have lost the game "<<"\n";
        return true;
    }
    else if (monster_health<=0){
        cout<<"congrafulation you have won the game "<<"\n";
        return true;
    }
    return false;
    
}

void remove_stones_after_connection(vector<vector<int> > connectedStones){
    // replace stone to 0
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            vector<int> temp(2);
            temp[0] = i;
            temp[1] = j;
            if (isVectorInVector(connectedStones, temp)) {
                arr[i][j] = 0;
            }
        }
    }
}






int main() {// integration 
    int default_ph=100;
    int default_mh=100;
    create_board();
    string status_file="gamestatus.txt";
    gamestatus last_game_status = readStructFromFile(status_file,default_ph,default_mh,arr);
    updatestatus(playerHealth,monsterHealth,last_game_status);// to update the current player health and monster health and board 
    // first read from the file to get the data from the last game 
    // Second we update the value of the player health , monster health and board from the last game
    while(true){
        print_instructions();
        
        vector <vector<int> > connected_stones;
        print_board(connected_stones);

        vector<int>stone_position= prompt_stone_position(row,col);// get the user selected stone position 
        cout<<"testing prompt stone no problem"<<"\n";
        int stone_type= arr[stone_position[1]][stone_position[0]];// determine the stone type 
        cout<<"test stone type"<<"\n";

        int connections=move_stones(stone_position[1],stone_position[0]);// going to continue prompting user for the move until a stone which is not the same type is connected 
        cout<<"testing move stone"<<"\n";
        print_monster();
        print_monster_health_bar();
        print_player_health_bar();
        // print the monster health bar 
        // print the player health bar 

        vector <int> result = calculate_score_for_each_stone(stone_type,connections);// calculatig the score for the connected stones
        execute_stone_actions(result);// apply the scores to the game scenario

        // after this we have to grab the connection history and replace all the stones 

        if (game_ended(playerHealth,monsterHealth)){
            // check if the game has ended after every connection ;
            // ask if the player would like to play again 
            char restart;
            cout<<"the game has ended would you like to restart press , press y to restart and any key to end "<<"\n";
            cin>>restart;
            if (restart=='y'){
                cout<<"hi";
            }
            else{
                cout<<"bye";

            }
            gamestatus new_game ;// creating a new game status object 
            new_game.PlayerH=default_ph;// set the default value of the player health 
            new_game.MonsterH=default_mh;// set the default value of the monster heatlth 
            create_board();// regenerate board again
            for(int i=0;i<row;i++){// set the default value of the board 
                for (int j=0;j<col;j++){
                    new_game.board[i][j]=arr[i][j];
            }
        }
            writeStructToFile(new_game,status_file);// storing the content into the file so next time the value are fetched will be the default values 
            // set the values in the game status.txt back to defualt values so next time when it is fetched can run it 
        }



        // add a wanting to quit option and save the game status 
        // we enter the main game loop 
        // first we have to print out the instruction to exaplin how to play the game 
        // print out the board 
        // ask the player to pick a stone to start with 
        // ask player to select move 
        // call the connect stone function , it will then print the board out 
        // after they finish the game , we reset the game status to the default setting in the game status file 
    }
}
