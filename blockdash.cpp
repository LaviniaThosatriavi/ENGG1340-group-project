#include <iostream>
#include <string>
#include <array>
#include <chrono>
#include <sys/ioctl.h>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

#ifdef _WIN32
#include <windows.h> // for Windows Operating System
#else
#include <unistd.h> // for Unix-like System
#endif

const int MapHeight = 17;
const string BROWN_COLOR = "\033[38;2;139;69;19m"; // Brown color escape code
const string BLUE_COLOR = "\033[34m";              // Blue color escape code
const string RESET_COLOR = "\033[0m";              // Reset color escape code
const string RED_COLOR = "\033[31m";               // Red color escape code
bool win = true;
array<string, MapHeight> mapPortion; // short version of map that will be printed at a time

// store each line of the map in the array
array<string, MapHeight> createArrMap(string fileName)
{
    // Open the map file for reading
    ifstream mapFile(fileName);

    // Create an array to store the map data
    array<string, MapHeight> mapData;

    // each line of the map file
    string line;

    // Check if the map file is open
    if (mapFile.is_open())
    {
        // Read each line of the map file and store it in the mapData array
        for (int i = 0; i < MapHeight && getline(mapFile, line); i++)
        {
            mapData[i] = line;
        }
    }
    else
    {
        // Print an error message if the map file cannot be opened
        cout << "Cannot open the Map file" << endl;
    }

    return mapData; // return the map array that contains each line of the map
}

// calculate the number of blocks in one row = mapWidth
int getMapWidth(const array<string, MapHeight> &mapData)
{
    // Iterate over each row in the mapData array
    for (string row : mapData)
    {
        // Return the length of the first row = the full length of the map in the game
        return row.length();
    }
    // Return 0 if the mapData array is empty
    return 0;
}

// find the terminal width of the laptop being used
int getTerminalWidth()
{
    struct winsize size;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size); // Get the size of the terminal window using ioctl system call
    int terminalWidth = size.ws_col;

    return terminalWidth;
}

// clear the terminal screen / delete all the contents previously printed
void clearScreen()
{
    // \033[2J clears the entire screen
    // \033[1;1H positions the cursor at the top-left corner of the screen
    cout << "\033[2J\033[1;1H" << endl;
}

// delay the process
void sleep(int t)
{
    this_thread::sleep_for(chrono::milliseconds(t)); // delay for t ms
}

// print a part of a map with colored blocks and player to terminal
void printMap(array<string, MapHeight> &mapData, int terminalWidth, int startPoint, int MapWidth, int playerX, int playerY)
{
    int endPoint = min(startPoint + terminalWidth, MapWidth - 1); // end point of the map to be printed at that time
    int time = 0;
    for (const string row : mapData)
    {
        string line;
        if (startPoint < row.length())
        {
            line = row.substr(startPoint, endPoint - startPoint); // print from the start to the end with the length of terminalWidth
        }
        else
        {
            line = string(terminalWidth, ' ');
        }

        mapPortion[time] = line; // update the portion of the map that will be printed
        time++;

        cout << "\r"; // Reset terminal cursor to the beginning of the line
        cout << line << endl;
    }
}

// print the win screen from text file called "win.txt"
void winScreen(int terminalWidth)
{
    ifstream fin;
    fin.open("win.txt"); // open the win design page
    string line;
    while (getline(fin, line)) // store each line of the file to variable line
    {
        string color_line = "";
        for (char c : line) // add color to each block
        {
            if (c == '=')
            {
                color_line += BROWN_COLOR;
                color_line += c;
                color_line += RESET_COLOR;
            }
            else
            {
                color_line += RED_COLOR;
                color_line += c;
                color_line += RESET_COLOR;
            }
        }
        if (line.length() < terminalWidth)
        {
            color_line += string(terminalWidth - line.length(), ' '); // fill the empty space with whitespace to make sure the alignment is correct
        }
        cout << color_line;
    }
}

// print the game over screen from text file called "lose.txt"
void loseScreen(int terminalWidth)
{

    ifstream fin;
    fin.open("lose.txt"); // open the lose design page
    string line;
    while (getline(fin, line)) // store each line of the file to variable line
    {
        string color_line = "";
        for (char c : line) // add color to each block
        {
            if (c == '=')
            {
                color_line += BROWN_COLOR;
                color_line += c;
                color_line += RESET_COLOR;
            }
            else
            {
                color_line += RED_COLOR;
                color_line += c;
                color_line += RESET_COLOR;
            }
        }
        if (line.length() < terminalWidth)
        {
            color_line += string(terminalWidth - line.length(), ' '); // fill the empty space with whitespace to make sure the alignment is correct
        }
        cout << color_line;
    }
}

// make the map move to the right
void moveMap(array<string, MapHeight> &mapData, int terminalWidth, int startPoint, int MapWidth, int playerX, int playerY)
{
    while (startPoint <= (MapWidth - (terminalWidth / 2))) // while the x of the player doesn't reach the end of the map
    {
        // move the map to the left
      clearScreen();
      printMap(mapData, terminalWidth, startPoint, MapWidth, playerX, playerY);

      startPoint++;
      sleep(50);
    }

    clearScreen();
    
    if (win) // if the player reaches the end point of the whole map, print win screen to congratulate them
    {
        winScreen(terminalWidth);
    }
    else // if the player loses, print lose screen to tell them that the game is over
    {
        loseScreen(terminalWidth);
    }
}

int main()
{
    string fileName = "1.txt";
    array<string, MapHeight> mapData = createArrMap(fileName); // store the desired map in the array, ready for further operation

    const int MapWidth = getMapWidth(mapData);
    int terminalWidth = getTerminalWidth();
    int startPoint = 0;
    int playerY = MapHeight / 2;           // player will start from the middle of the map
    const int playerX = terminalWidth / 2; // player is always at the center of the map

    moveMap(mapData, terminalWidth, startPoint, MapWidth, playerX, playerY); // operating the games
    
    return 0;
}
