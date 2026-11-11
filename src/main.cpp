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
    if (x < 0 || x >= dungeonMap[0].size() || y < 0 || y >= dungeonMap.size()) {
        return false;
    }
    else {
        if (dungeonMap[y][x] == '#') {
            return false;
        }
        return true;
    }
}

void HandleInput(Player& player) {

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
    else if (IsKeyPressed(KEY_LEFT)) {
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

void UpdateGame(Player& player, GameState& gameState) {

    HandleInput(player);

    if (dungeonMap[player.y][player.x] == 'K') {
        player.haskey = true;
        dungeonMap[player.y][player.x] = '.';
    }
    if (dungeonMap[player.y][player.x] == 'E') {
        if (player.haskey == true) {
            gameState = GameState::Victory;
        }
    }
}


void DrawGame(const Player& player) {
    
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

    DrawRectangle(player.x * TILE_SIZE,
                  player.y * TILE_SIZE,
                  TILE_SIZE,
                  TILE_SIZE,
                  BLUE);
    
}


//=================================
// 5. Main Function
//=================================


int main() {
    Player player;
    player.x = 1;
    player.y = 1;
    player.haskey = false;
    GameState gameState = GameState::Playing;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE.c_str());
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (gameState == GameState::Playing) {
            UpdateGame(player, gameState);
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameState == GameState::Playing) {
            DrawGame(player);
        }
        if (gameState == GameState::Victory) {
            DrawText("VICTORY", 100, 100, 20, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();


    return 0;
}