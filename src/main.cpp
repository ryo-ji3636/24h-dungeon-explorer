#include <iostream>
#include <string>
#include <vector>
#include "raylib.h"
using namespace std;

//=================================
// 1. Constants
//=================================
const string GAME_TITLE = "Dungeon Explorer";

//TILE_SIZE
const int TILE_SIZE = 48;

//SCREEN_WIDTH
const int SCREEN_WIDTH = 576;

//SCREEN_HEIGHT
const int SCREEN_HEIGHT = 384;

//=================================
// 2. Data Structures
//=================================

struct Player {
    int x;
    int y;
    bool haskey = false;
};

enum class GameState {
    Menu,
    Playing,
    Paused,
    Victory,
    GameOver
};

//=================================
// 3. Map
//=================================

vector<string> dungeonMap = {
    "############", 
    "#..........#",
    "#...##.....#",
    "#..........#",
    "#.......K..#",
    "#..........#",
    "#.........E#",
    "############"
};



//=================================
// 4. Function Declarations
//=================================

bool CanMove(int x, int y) {
    
}

void HandleInput() {
    Player player;
    player.x = 1;
    player.y = 1;
    player.haskey = false;

    if (IsKeyPressed(KEY_UP)) {
        if (CanMove(player.x, player.y - 1)) {
            player.y--;
        }
    }
    else if (IsKeyPressed(KEY_DOWN)) {
        if (CanMove(player.x, player.y + 1)) {
            player.y++;
        }
    }
    elseif (IsKeyPressed(KEY_LEFT)) {
        if(CanMove(player.x - 1, player.y)) {
            player.x--;
        }
    }
    else if (IsKeyPressed(KEY_RIGHT)) {
        if (CanMove(player.x + 1, player.y)) {
            player.x++;
        }
    }
}

void UpdateGame() {
    Player player;
    player.x = 1;
    player.y = 1;
    player.haskey = false;

    HandleInput();

    if (dungeonMap[player.x][player.y] == 'K') {
        player.haskey = true;
        dungeonMap[player.x][player.y] = '.';
    }
    if (dungeonMap[player.x][player.y] == 'E') {
        if (player.haskey == true) {
            gameState = GameState::Victory;
        }
    }
}


void DrawGame() {
    
    for (int y = 0; y < dungeonMap.size(); y++) {
        for (int x = 0; x < dungeonMap[y].size(); x++) {
            if (dungeonMap[y][x] == '#') {
                DrawRectangle(x * TILE_SIZE,
                              y * TILE_SIZE,
                              TILE_SIZE,
                              TILE_SIZE,
                              DARKGRAY);
            }
            else if (dungeonMap[y][x] == '.') {
                DrawRectangle(x * TILE_SIZE,
                              y * TILE_SIZE,
                              TILE_SIZE,
                              TILE_SIZE,
                              WHITE);
            }
            else if (dungeonMap[y][x] == 'K') {
                DrawRectangle(x * TILE_SIZE,
                              y * TILE_SIZE,
                              TILE_SIZE,
                              TILE_SIZE,
                              YELLOW);
            }
            else if (dungeonMap[y][x] == 'E') {
                DrawRectangle(x * TILE_SIZE,
                              y * TILE_SIZE,
                              TILE_SIZE,
                              TILE_SIZE,
                              GREEN);
            }
        }
    }
}


//=================================
// 5. Main Function
//=================================


int main() {

}