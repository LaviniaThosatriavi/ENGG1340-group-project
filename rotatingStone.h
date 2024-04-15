#ifndef ROTATINGSTONE_H
#define ROTATINGSTONE_H

#include <array>
#include <string>

using namespace std;

const int row = 5;
const int col = 5;
const string bred = "\033[1;41m"; // background red
const string bgreen = "\033[1;42m"; // background green
const string byellow = "\033[1;43m"; // background yellow
const string bblue = "\033[1;44m"; // background blue
const string fblack = "\033[30m"; // foreground magenta
const string reset = "\033[0m"; // reset color
struct gamestatus// a structure used to save all the game status 
{
    int MonsterH;
    int PlayerH;
    int board[row][col];
};
const int monsterMaxHealth = 100;
const int playerMaxHealth = 100;

bool isVectorInVector(const vector<vector<int> >& outer, const vector<int>& target);
void print_board(vector <vector<int> > connectedStones);
void writeStructToFile(const gamestatus& data, const std::string& filename);
gamestatus readStructFromFile(const std::string& filename, int default_ph, int default_mh,int default_b[row][col]);
void updatestatus(gamestatus update);
void create_board();
char prompt_user_move(vector<int> stone_position, int row, int col);
vector<int> prompt_stone_position(int board_row,int board_col);
void regenearte_stones(vector <vector<int> > connected_stones);
int move_stones(int s_row,int s_col);
vector<int> calculate_score_for_each_stone(int stoneType, int numStones);
void print_monster();
void print_monster_health_bar();
void print_player_health_bar();
void print_instructions();
bool game_ended(int player_health , int monster_health);
bool prompt_quit(); 
bool rotatingStoneMain(); 


#endif // ROTATINGSTONE_H