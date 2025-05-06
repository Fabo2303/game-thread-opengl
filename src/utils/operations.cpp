#include "../../include/utils/operations.h"
#include "../../include/utils/calculateSpeedUp.h"
#include <GL/freeglut.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <algorithm>

Semaphore sem(1);
std::mutex mtx;
std::mutex updateMutex;
Boss boss;

Semaphore::Semaphore(unsigned long init_count) : count_(init_count) {}

int Semaphore::acquire()
{
    std::unique_lock<std::mutex> lock(m_);
    while (count_ == 0)
        cv_.wait(lock);
    count_--;
    return 1;
}

void Semaphore::release()
{
    std::unique_lock<std::mutex> lock(m_);
    count_++;
    lock.unlock();
    cv_.notify_one();
}

Operations::Operations()
    : start(false), nextLevel(false), bossLevel(false),
      pendingEnemiesToSpawn(0), currentEnemies(0),
      currentEnemiesKilled(0), availableBullets(0), score(0)
{
    boss.setActive(false);
}

bool Operations::isGameStarted() { return start; }
bool Operations::isGameChangeLevel() { return nextLevel; }
void Operations::setGameStarted(bool value) { start = value; }

void Operations::startGame(int level)
{
    start = true;
    nextLevel = true;
    pendingEnemiesToSpawn = level;
    currentEnemiesKilled = 0;

    switch (level)
    {
    case 1:
        availableBullets = 4;
        break;
    case 2:
        availableBullets = 16;
        break;
    case 3:
        availableBullets = 10;
        generateBoss();
        break;
    default:
        break;
    }

    if (level < 3)
        generateEnemies();

    addThreads();
}

void Operations::endGame()
{
    start = false;
    bossLevel = false;
    enemies.clear();
    bullets.clear();
    pendingEnemiesToSpawn = 0;
    availableBullets = 0;
    currentEnemies = 0;
    currentEnemiesKilled = 0;
    calculateRanking();
    printf("Game Over\n");
}

void Operations::calculateRanking()
{
    saveScore(score);
    testSpeedUp();
    glutLeaveMainLoop();
}

void Operations::changeLevel()
{
    nextLevel = false;
    enemies.clear();
    bullets.clear();
    pendingEnemiesToSpawn = 0;
    availableBullets = 0;
    currentEnemies = 0;
    currentEnemiesKilled = 0;
}

void Operations::generateBoss()
{
    boss.setActive(true);
    bossLevel = true;
    std::thread(&Boss::move, &boss, 7).detach();
    std::thread(&Boss::attack, &boss).detach();
}

void Operations::generateEnemies()
{
    currentEnemies = pendingEnemiesToSpawn * 4;
    std::vector<Area> areas = {
        {{30, 900}, {350, 800}},
        {{350, 900}, {700, 800}},
        {{700, 900}, {1050, 800}},
        {{1050, 900}, {1370, 800}}};

    std::vector<std::thread> threads;
    for (const auto &area : areas)
        threads.emplace_back(&Operations::generateEnemiesInArea, this, std::ref(area));

    for (auto &t : threads)
        t.join();

    spawnEnemies();
    moveEnemies();
}

void Operations::generateEnemiesInArea(const Area &area)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> disX(area.start.x, area.end.x);
    std::uniform_int_distribution<int> disY(area.end.y, area.start.y);

    int type = 0;
    for (int i = 0; i < pendingEnemiesToSpawn; ++i)
    {
        sem.acquire();
        int x = disX(gen);
        int y = disY(gen);
        {
            std::lock_guard<std::mutex> lock(mtx);
            enemiesQueue.emplace(x, y, type);
        }
        type = 1 - type;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        sem.release();
    }
}

void Operations::spawnEnemies()
{
    while (!enemiesQueue.empty())
    {
        std::lock_guard<std::mutex> lock(mtx);
        int x = enemiesQueue.front().getX();
        int y = enemiesQueue.front().getY();
        int type = enemiesQueue.front().getType();
        enemies.push_back(std::make_shared<Enemy>(x, y, type));
        enemiesQueue.pop();
        sem.release();
    }
}

void Operations::moveEnemies()
{
    for (auto &enemy : enemies)
        std::thread(&Enemy::move, enemy, 7, std::ref(start)).detach();
}

void Operations::addThreads()
{
    std::thread(&Operations::updateBullets, this).detach();
}

void Operations::drawBoss()
{
    if (bossLevel)
    {
        boss.draw();
        boss.drawBullet();
    }
}

void Operations::drawEnemy()
{
    if (start && nextLevel)
    {
        for (auto &enemy : enemies)
        {
            if (enemy->getY() <= 3)
                endGame();
            enemy->draw();
        }
    }
}

void Operations::drawBullets()
{
    for (auto &bullet : bullets)
        bullet.draw();
}

void Operations::shoot(int xOffset)
{
    if (availableBullets > 0)
    {
        availableBullets--;
        bullets.emplace_back(xOffset + 47.5, 75);
    }
    else
    {
        printf("No bullets\n");
    }
}

void Operations::updateBullets()
{
    while (start && nextLevel)
    {
        {
            std::lock_guard<std::mutex> lock(updateMutex);
            bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                         [](Bullet &b)
                                         {
                                             b.move(10);
                                             return !b.isActive();
                                         }),
                          bullets.end());
        }

        glutPostRedisplay();
        updateBulletsAndEnemies();
        updateBulletAndBoss();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Operations::updateBulletsAndEnemies()
{
    for (auto &bullet : bullets)
    {
        for (auto &enemy : enemies)
        {
            if (bullet.checkCollision(*enemy) && enemy->isActive())
            {
                bullet.setActive(false);
                enemy->setActive(false);
                currentEnemiesKilled++;
                score += 51;

                if (currentEnemiesKilled == currentEnemies)
                    changeLevel();
            }
        }
    }
}

void Operations::updateBulletAndBoss()
{
    for (auto &bullet : bullets)
    {
        if (bullet.checkCollision(boss) && boss.isActive())
        {
            bullet.setActive(false);
            boss.decreaseLife();
            score += 48;
            if (!boss.isActive())
                endGame();
        }
    }
}

void Operations::collisionDefenderBulletBoss(int xOffset)
{
    if (boss.checkCollision(xOffset))
    {
        endGame();
    }
}
