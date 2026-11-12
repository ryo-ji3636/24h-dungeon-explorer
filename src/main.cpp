#include <iostream>
#include <string>
#include <vector>
#include "Game.h"
#include "raylib.h"
using namespace std;

//=================================
// Constants
//=================================
const string GAME_TITLE = "Dungeon Explorer";

//TILE_SIZE
const int TILE_SIZE = 48;

//SCREEN_WIDTH
const int SCREEN_WIDTH = 576;

//SCREEN_HEIGHT
const int SCREEN_HEIGHT = 432;


//=================================
// Main Function
//=================================


int main() {
    Player player;
    player.x = 1;
    player.y = 1;
    player.hp = 100;
    player.attack = 20;
    player.haskey = false;
    Enemy enemy;
    enemy.x = 8;
    enemy.y = 3;
    enemy.hp = 50;
    enemy.attack = 10;
    GameState gameState = GameState::Playing;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE.c_str());
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (gameState == GameState::Playing) {
            UpdateGame(player, enemy, gameState);
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameState == GameState::Playing) {
            DrawGame(player, enemy);
        }
        if (gameState == GameState::Victory) {
            DrawText("VICTORY", 100, 100, 20, BLACK);
        }
        if (gameState == GameState::GameOver) {
            DrawText("GAME OVER", 100, 100, 20, BLACK);
        }
        if (IsKeyPressed(KEY_R)) {
            ResetGame(player, enemy, gameState);
        }

        EndDrawing();
    }

    CloseWindow();


    return 0;
}