#include <iostream>
#include <time.h>

using namespace std;

const int row = 5;
const int col = 5;
int arr[row][col];

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

}

void print_board(){
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (arr[i][j] == 1) {
                cout << "\033[1;31m" << arr[i][j] << "\033[0m ";
            } else if (arr[i][j] == 2) {
                cout << "\033[1;32m" << arr[i][j] << "\033[0m ";
            } else if (arr[i][j] == 3) {
                cout << "\033[1;33m" << arr[i][j] << "\033[0m ";
            } else if (arr[i][j] == 4) {
                cout << "\033[1;34m" << arr[i][j] << "\033[0m ";
            }
        }
        cout << endl;
    }
}

int main() {
    create_board();
    print_board();
    return 0;
}