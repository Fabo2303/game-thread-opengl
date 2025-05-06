#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <random>
#include <string>
#include "../characters/boss.h"
#include "../characters/enemy.h"
#include "../characters/bullet.h"

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

struct Area {
    Point start, end;
};

class Semaphore {
public:
    Semaphore(unsigned long init_count);
    int acquire();
    void release();

private:
    unsigned long count_;
    std::mutex m_;
    std::condition_variable cv_;
};

class Operations {
public:
    Operations();
    void startGame(int level);
    void endGame();
    void shoot(int xOffset);
    void drawEnemy();
    void drawBullets();
    void drawBoss();
    bool isGameStarted();
    bool isGameChangeLevel();
    void setGameStarted(bool start);
    void collisionDefenderBulletBoss(int xOffset);

private:
    void changeLevel();
    void calculateRanking();
    void generateEnemies();
    void generateEnemiesInArea(const Area& area);
    void generateBoss();
    void addThreads();
    void spawnEnemies();
    void moveEnemies();
    void updateBullets();
    void updateBulletsAndEnemies();
    void updateBulletAndBoss();
    void checkEnemyPass(Enemy& enemy);

    bool start;
    bool nextLevel;
    bool bossLevel;
    int pendingEnemiesToSpawn;
    int currentEnemies;
    int currentEnemiesKilled;
    int availableBullets;
    int score;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<Bullet> bullets;
    std::queue<Enemy> enemiesQueue;
};

#endif // OPERATIONS_H
