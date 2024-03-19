#include <iostream>
#include <time.h>

using namespace std;

const int row = 5;
const int col = 5;
int arr[row][col];
int monsterHealth = 90;
const int monsterMaxHealth = 100;

void create_board(){
    srand(time(0));
    for (int i=0; i< row; i++)
        for (int j=0; j< col; j++)
            arr[i][j] = 1 + (rand() % 4);
}

void checkconnection(){

}

void remove_stones_after_connection(){

}

void regenearte_stones(){

}

void calculate_score_for_each_stone(){

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
                cout << "\033[1;41m" << " " << "\033[0m ";
            } else if (arr[i][j] == 2) {
                cout << "\033[1;42m" << " " << "\033[0m ";
            } else if (arr[i][j] == 3) {
                cout << "\033[1;43m" << " "<< "\033[0m ";
            } else if (arr[i][j] == 4) {
                cout << "\033[1;44m" << " " << "\033[0m ";
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