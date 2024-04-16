#include <iostream>
#include <string>
#include <array>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

#ifdef _WIN32
#include <windows.h> // for Windows Operating System
#include <conio.h>
#include <curses.h>
#else
#include <sys/ioctl.h>
#include <ncurses.h>
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
#ifdef _WIN32
    // Windows specific code
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        cerr << "GetConsoleScreenBuferInfo failed" << endl;
        return -1;
    }
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;

#else
    struct winsize size;

    // Get the size of the terminal window using ioctl system call
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    int terminalWidth = size.ws_col;

    return terminalWidth;
#endif
}

// add the player character 'P' to the correct line of the map to be printed
void addPlayer(string &line, int playerX)
{
    string bluePlayer = BLUE_COLOR + "P" + RESET_COLOR; // Blue-colored player character

    if (playerX < line.length())
    {
        // Replace character at playerX with bluePlayer
        line.replace(playerX, 1, bluePlayer);
    }
    else
    {
        // if nothing is in that position in the map
        line += string(playerX - line.length(), ' ');
        // Append bluePlayer at the end of the line
        line += bluePlayer;
    }
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
    // delay for t ms
    this_thread::sleep_for(chrono::milliseconds(t));
}

// print a part of a map with colored blocks and player to terminal
void printMap(array<string, MapHeight> mapData, int terminalWidth, int startPoint, int MapWidth, int playerX, int playerY)
{
    int endPoint = min(startPoint + terminalWidth, MapWidth - 1); // end point of the map to be printed at that time
    int time = 0;
    for (const string row : mapData)
    {
        string line;
        if (startPoint < row.length())
        {
            // print from the start to the end with the length of terminalWidth
            line = row.substr(startPoint, endPoint - startPoint);
        }
        else
        {
            line = string(terminalWidth, ' ');
        }

        // update the portion of the map that will be printed
        mapPortion[time] = line;
        time++;

        // add player if that row is the one containting player
        if (row.compare(mapData[playerY]) == 0)
        {
            addPlayer(line, playerX);
        }

        // Reset terminal cursor to the beginning of the line
        cout << "\r";

        // real output line with updated block color
        string outputLine;
        for (char &c : line)
        {
            if (c == 'X') // first obstacle with brown
            {
                outputLine += BROWN_COLOR;
                outputLine += c;
                outputLine += RESET_COLOR;
            }
            else if (c == 'O') // second obstacle with red
            {
                outputLine += RED_COLOR;
                outputLine += c;
                outputLine += RESET_COLOR;
            }
            else if (c == 'P') // player with blue
            {
                outputLine += BLUE_COLOR;
                outputLine += c;
                outputLine += RESET_COLOR;
            }
            else
            {
                outputLine += c;
            }
        }
        cout << outputLine << endl;
    }
}

// print the win screen from text file called "win.txt"
void winScreen(int terminalWidth)
{
    clearScreen();
    ifstream fin;
    // open the win design page
    fin.open("blockdashScreen/win.txt");
    string line;

    // store each line of the file to variable line
    while (getline(fin, line))
    {
        string color_line = "";

        // add color to each block
        for (char c : line)
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
            // fill the empty space with whitespace to make sure the alignment is correct
            color_line += string(terminalWidth - line.length(), ' ');
        }
        cout << color_line;
    }
}

// print the game over screen from text file called "lose.txt"
void loseScreen(int terminalWidth)
{
    clearScreen();
    ifstream fin;

    // open the lose design page
    fin.open("blockdashScreen/lose.txt");
    string line;

    // store each line of the file to variable line
    while (getline(fin, line))
    {
        string color_line = "";

        // add color to each block
        for (char c : line)
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
            // fill the empty space with whitespace to make sure the alignment is correct
            color_line += string(terminalWidth - line.length(), ' ');
        }
        cout << color_line;
    }
}

// check if space bar is pressed = the command for player to go up
bool isSpaceBarPressed()
{
#ifdef _WIN32
    int ch = _getch(); // read a character from the keyboard
#else
    int ch = getch();
#endif

    // return true if space bar is pressed on the keyboard
    if (ch == ' ')
    {
        return true;
    }

    return false;
}

// check if current position of the player is safe = no collision
bool checkCollision(int MapWidth, int playerX, int playerY)
{

    // Check if the player's position is within the map boundaries
    if (playerX < 0 || playerX >= MapWidth || playerY < 0 || playerY >= MapHeight)
    {
        // return true if the player is out of the map
        return true;
    }

    // Check if the player collides with an obstacle
    char obstacle1 = 'O';
    char obstacle2 = 'X';
    if (mapPortion[playerY][playerX] == obstacle1 || mapPortion[playerY][playerX] == obstacle2)
    {
        // return true if the player collide
        return true;
    }

    // no collision, return false
    return false;
}

// controlling the main logic and operation of the games by combining many functions together:
// 1) print the map moving to the right continuously
// 2) moving player up if space bar is pressed
// 3) always check if the next move of the player collides with obstacles or be out of the map boundaries
// 4) print win when the player reaches finish point
// 5) print lose (game over) when the player collides
void moveMap(array<string, MapHeight> &mapData, int terminalWidth, int startPoint, int MapWidth, int playerX, int &playerY)
{
    int times = 0;

    // while the x of the player doesn't reach the end of the map
    while (startPoint <= (MapWidth - (terminalWidth / 2)))
    {
        // move the map to the left
        clearScreen();
        printMap(mapData, terminalWidth, startPoint, MapWidth, playerX, playerY);

        if (checkCollision(MapWidth, playerX, playerY))
        {
            // if the player collides with the obstacle, calling game over
            win = false;
            break;
        }
        // if the going up command is called
        if (isSpaceBarPressed())
        {
            // go up by 2 blocks
            playerY -= 2;
        }
        else if ((times % 4) == 1)
        {
            // serving as gravity that will make player gradually fall down
            playerY++;
        }

        startPoint++;
        times++;
        sleep(50);
    }

    clearScreen();
}

bool blockDashMain()
{
    srand(static_cast<unsigned int>(time(nullptr)));                      // random number
    int randomNumber = (rand() % 9) + 1;                                  // limit the range of number to 1-5
    string fileName = "blockdashMap/" + to_string(randomNumber) + ".txt"; // random the map file to be opened
    array<string, MapHeight> mapData = createArrMap(fileName);            // store the desired map in the array, ready for further operation

    const int MapWidth = getMapWidth(mapData);
    int terminalWidth = getTerminalWidth();
    int startPoint = 0;
    int playerY = MapHeight / 2;           // player will start from the middle of the map
    const int playerX = terminalWidth / 2; // player is always at the center of the map

    // setting for enabling the constantly checking for input function
    initscr();             // Initialize ncurses
    cbreak();              // Disable line buffering
    noecho();              // Disable automatic echoing of input
    nodelay(stdscr, true); // Enable non-blocking input

    // operating the games
    moveMap(mapData, terminalWidth, startPoint, MapWidth, playerX, playerY);
    endwin();

    return win;
}
