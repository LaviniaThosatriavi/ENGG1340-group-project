#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <sstream>

using namespace std;

const int MapHeight = 17;
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
