#ifndef GAME_H
#define GAME_H

struct Player {
    int x;
    int y;
    int hp = 100;
    int attack = 20;
    bool haskey = false;
};

struct Enemy {
    int x = 8;
    int y = 3;
    int hp = 50;
    int attack = 10;
};

enum class GameState {
    Menu,
    Playing,
    Paused,
    Victory,
    GameOver
};

// Function declarations
bool CanMove(int x, int y, const Enemy& enemy);

bool HandleInput(Player& player, Enemy& enemy);

void UpdateGame(Player& player, Enemy& enemy, GameState& gameState);

void DrawGame(const Player& player, const Enemy& enemy);

bool IsInAttackRange(const Player& player, const Enemy& enemy);

void AttackEnemy(const Player& player, Enemy& enemy);

void EnemyAttack(Player& player, const Enemy& enemy);


#endif // GAME_H