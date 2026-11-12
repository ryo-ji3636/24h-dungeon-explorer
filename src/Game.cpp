#include "Game.h"
#include "raylib.h"
#include <vector>
#include <cstdlib>
using namespace std;


//=================================
//  Map
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
// Function Declarations
//=================================
bool IsWalkableTile(int x, int y) {
    if (x < 0 || x >= dungeonMap[0].size() || y < 0 || y >= dungeonMap.size()) {
        return false;
    }
    else if (dungeonMap[y][x] == '#') {
        return false;
    }

    return true;
}

bool CanMove(int x, int y, const Enemy& enemy) {
    if (x < 0 || x >= dungeonMap[0].size() || y < 0 || y >= dungeonMap.size()) {
        return false;
    }

    else {
        if (dungeonMap[y][x] == '#') {
            return false;
        }
        if (enemy.hp > 0 && x == enemy.x && y == enemy.y) {
            return false;
        }
        return true;
    }
}

bool HandleInput(Player& player, Enemy& enemy) {

    if (IsKeyPressed(KEY_UP)) {
        if (CanMove(player.x, player.y - 1, enemy)) {
            player.y--;
            return true;
        }
    }
    else if (IsKeyPressed(KEY_DOWN)) {
        if (CanMove(player.x, player.y + 1, enemy)) {
            player.y++;
            return true;
        }
    }
    else if (IsKeyPressed(KEY_LEFT)) {
        if(CanMove(player.x - 1, player.y, enemy)) {
            player.x--;
            return true;
        }
    }
    else if (IsKeyPressed(KEY_RIGHT)) {
        if (CanMove(player.x + 1, player.y, enemy)) {
            player.x++;
            return true;
        }
    }
    else if (IsKeyPressed(KEY_SPACE)) {
        AttackEnemy(player, enemy);
        return true;
    }

    return false;
}

void UpdateGame(Player& player, Enemy& enemy, GameState& gameState) {

    bool playerActed = HandleInput(player, enemy);

    if (dungeonMap[player.y][player.x] == 'K') {
        player.haskey = true;
        dungeonMap[player.y][player.x] = '.';
    }
    if (dungeonMap[player.y][player.x] == 'E') {
        if (player.haskey == true) {
            gameState = GameState::Victory;
        }
    }
    if (gameState == GameState::Victory) {
        return;
    }
    if(playerActed && enemy.hp > 0) {
        if (IsInAttackRange(player, enemy)) {
            EnemyAttack(player, enemy);
        }
        else {
            MoveEnemy(player, enemy);
        }
    }

    if (player.hp <= 0) {
        gameState = GameState::GameOver;
    }
    
}



void DrawGame(const Player& player, const Enemy& enemy) {
    const int TILE_SIZE = 48;
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
    if (enemy.hp > 0) {
        DrawRectangle(enemy.x * TILE_SIZE,
                      enemy.y * TILE_SIZE,
                      TILE_SIZE,
                      TILE_SIZE,
                      RED);
    }

    DrawRectangle(0, 384, 576, 48, DARKGRAY);
    string hpText = "HP: " + to_string(player.hp);
    DrawText(hpText.c_str(), 10, 395, 20, WHITE);
    DrawRectangle(100, 395, 200, 20, GRAY);
    int hpWidth = 200 * player.hp / player.maxhp;
    DrawRectangle(100, 395, hpWidth, 20, GREEN);
    string haskeyText = player.haskey ? "KEY: YES" : "KEY: NO";
    DrawText(haskeyText.c_str(), 360, 395, 20, YELLOW);
    
}

bool IsInAttackRange(const Player& player, const Enemy& enemy) {
    int d = abs(player.x - enemy.x) + abs(player.y - enemy.y);
    if (d == 1) {
        return true;
    }
    return false;
}

void AttackEnemy(const Player& player, Enemy& enemy) {
    if (enemy.hp > 0 && IsInAttackRange(player, enemy)) {
        enemy.hp -= player.attack;
    }
}

void EnemyAttack(Player& player, const Enemy& enemy) {
    if(enemy.hp > 0 && IsInAttackRange(player, enemy)) {
        player.hp -= enemy.attack;
    }
}

bool CanEnemyMove(int newX, int newY, const Player& player) {
    if(!IsWalkableTile(newX, newY)) {
        return false;
    }
    if (newX == player.x && newY == player.y) {
        return false;
    }

    return true;
}

void MoveEnemy(const Player& player, Enemy& enemy) {
    if (enemy.hp <= 0) {
        return;
    }
    else {
        int dx = abs(player.x - enemy.x);
        int dy = abs(player.y - enemy.y);

        if (dx >= dy) {
            if (player.x > enemy.x) {
                if (CanEnemyMove(enemy.x + 1, enemy.y, player)) {
                    enemy.x++;
                }
            }
            else {
                if (CanEnemyMove(enemy.x - 1, enemy.y, player)) {
                    enemy.x--;
                }
            }
        }
        else {
            if (player.y > enemy.y) {
                if (CanEnemyMove(enemy.x, enemy.y + 1, player)) {
                enemy.y++;
                }
            }
            else {
                if (CanEnemyMove(enemy.x, enemy.y - 1, player)) {
                    enemy.y--;
                }
            }
        }
    }
}

void ResetGame(Player& player, Enemy& enemy, GameState& gameState) {
    player.x = 1;
    player.y = 1;
    player.hp = player.maxhp;
    player.haskey = false;
    enemy.x = 8;
    enemy.y = 3;
    enemy.hp = 50;
    gameState = GameState::Playing;
    dungeonMap[4][8] = 'K';
}