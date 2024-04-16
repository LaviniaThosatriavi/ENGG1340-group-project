#ifndef BLOCKDASH_H
#define BLOCKDASH_H

#include <array>
#include <string>

const int MapHeight = 10; // Example value, adjust as needed

std::array<std::string, MapHeight> createArrMap(const std::string &fileName);
int getMapWidth(const std::array<std::string, MapHeight> &mapData);
int getTerminalWidth();
void moveMap(std::array<std::string, MapHeight> &mapData, int terminalWidth, int startPoint, int MapWidth, int playerX, int playerY);
bool blockDashMain();
void winScreen(int terminalWidth);
void loseScreen(int terminalWidth);
void sleep(int t);

#endif // BLOCKDASH_H
