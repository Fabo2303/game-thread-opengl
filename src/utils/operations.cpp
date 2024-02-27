#include <vector>
#include <thread>
#include <queue>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>
#include <iostream>
#include <condition_variable>
#include <math.h>
#include <random>
#include <fstream>
#include "../characters/bullet.cpp"
#include "../utils/calculateSpeedUp.cpp"

struct Point
{
  int x, y;
  Point(int x, int y)
  {
    this->x = x;
    this->y = y;
  }
};

struct Area
{
  Point start, end;
};

class Semaphore
{
public:
  Semaphore(unsigned long init_count)
  {
    count_ = init_count;
  }

  int acquire()
  {
    std::unique_lock<std::mutex> lock(m_);
    while (count_ == 0)
    {
      cv_.wait(lock);
    }
    count_--;
    return 1;
  }

  void release()
  {
    std::unique_lock<std::mutex> lock(m_);
    count_++;
    lock.unlock();
    cv_.notify_one();
  }

private:
  unsigned long count_;
  std::mutex m_;
  std::condition_variable cv_;
};

Semaphore sem(1);
std::mutex mtx;
std::mutex updateMutex;
Boss boss;

class Operations
{
private:
  bool start = false;
  bool nextLevel = false;
  bool bossLevel = false;
  int pendingEnemiesToSpawn = 0;
  int currentEnemies = 0;
  int currentEnemiesKilled = 0;
  int availableBullets = 0;
  int score = 0;
  std::vector<Enemy> enemies;
  std::vector<Bullet> bullets;
  std::queue<Enemy> enemiesQueue;

public:
  Operations()
  {
    this->start = false;
    this->nextLevel = false;
    this->pendingEnemiesToSpawn = 0;
    this->availableBullets = 0;
    this->currentEnemies = 0;
    this->currentEnemiesKilled = 0;
    boss.setActive(false);
  }

  bool isGameStarted()
  {
    return start;
  }

  bool isGameChangeLevel()
  {
    return nextLevel;
  }

  void setGameStarted(bool start)
  {
    this->start = start;
  }

  void startGame(int level)
  {
    start = true;
    nextLevel = true;
    pendingEnemiesToSpawn = level;
    currentEnemies = pendingEnemiesToSpawn * 4;
    currentEnemiesKilled = 0;
    if (level == 1)
    {
      availableBullets = 4;
      generateEnemies();
      addThreads();
    }
    else if (level == 2)
    {
      availableBullets = 16;
      generateEnemies();
      addThreads();
    }
    else if (level == 3)
    {
      availableBullets = 10;
      generateBoss();
      addThreads();
    }
  }

  void addThreads()
  {
    std::thread updateBulletsThread(&Operations::updateBullets, this);
    updateBulletsThread.detach();
  }

  void endGame()
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

  void calculateRanking()
  {
    saveScore(score);
    testSpeedUp();
    glutLeaveMainLoop();
  }

  void changeLevel()
  {
    nextLevel = false;
    pendingEnemiesToSpawn = 0;
    availableBullets = 0;
    currentEnemies = 0;
    currentEnemiesKilled = 0;
    enemies.clear();
    bullets.clear();
  }

  void generateBoss()
  {
    boss.setActive(true);
    bossLevel = true;
    std::thread bossThread(&Boss::move, &boss, 7);
    bossThread.detach();
    std::thread bossShootThread(&Boss::attack, &boss);
    bossShootThread.detach();
  }

  void generateEnemiesInArea(const Area &area)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> disX(area.start.x, area.end.x);
    std::uniform_int_distribution<int> disY(area.end.y, area.start.y);
    int type = 0;
    for (int i = 0; i < pendingEnemiesToSpawn; i++)
    {
      sem.acquire();
      int x = disX(gen);
      int y = disY(gen);
      mtx.lock();
      enemiesQueue.push(Enemy(x, y, type));
      type == 0 ? type = 1 : type = 0;
      mtx.unlock();
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      sem.release();
    }
  }

  void generateEnemies()
  {
    std::vector<Area> areas = {
        {{30, 900}, {350, 800}},
        {{350, 900}, {700, 800}},
        {{700, 900}, {1050, 800}},
        {{1050, 900}, {1370, 800}}};

    std::vector<std::thread> threads;
    for (const auto &area : areas)
    {
      threads.emplace_back(&Operations::generateEnemiesInArea, this, std::ref(area));
    }

    for (auto &thread : threads)
    {
      thread.join();
    }
    spawnEnemies();
    moveEnemies();
  }

  void spawnEnemies()
  {
    while (!enemiesQueue.empty())
    {
      mtx.lock();
      enemies.push_back(enemiesQueue.front());
      enemiesQueue.pop();
      mtx.unlock();
      sem.release();
    }
  }

  void moveEnemies()
  {
    for (auto &enemy : enemies)
    {
      std::thread moveEnemy(&Enemy::move, &enemy, 7, std::ref(start));
      moveEnemy.detach();
    }
  }

  void drawBoss()
  {
    if (bossLevel)
    {
      boss.draw();
      boss.drawBullet();
    }
  }

  void checkEnemyPass(Enemy &enemy)
  {
    if (enemy.getY() <= 3)
    {
      endGame();
    }
  }

  void drawEnemy()
  {
    if (start && nextLevel)
    {
      for (auto &enemy : enemies)
      {
        checkEnemyPass(enemy);
        enemy.draw();
      }
    }
  }

  void drawBullets()
  {
    for (auto &bullet : bullets)
    {
      bullet.draw();
    }
  }

  void collisionDefenderBulletBoss(int xOffset)
  {
    if (boss.checkCollision(xOffset))
    {
      endGame();
    }
  }

  void updateBulletsAndEnemies()
  {
    for (auto &bullet : bullets)
    {
      for (auto &enemy : enemies)
      {
        if (bullet.checkCollision(enemy) && enemy.isActive())
        {
          bullet.setActive(false);
          enemy.setActive(false);
          currentEnemiesKilled++;
          score += 51;
          if (currentEnemiesKilled == currentEnemies)
          {
            changeLevel();
          }
        }
      }
    }
  }

  void updateBulletAndBoss()
  {
    for (auto &bullet : bullets)
    {
      if (bullet.checkCollision(boss) && boss.isActive())
      {
        bullet.setActive(false);
        boss.decreaseLife();
        score += 48;
        if (!boss.isActive())
        {
          endGame();
        }
      }
    }
  }

  void updateBullets()
  {
    while (start && nextLevel)
    {
      updateMutex.lock();
      auto it = bullets.begin();
      while (it != bullets.end())
      {
        auto &bullet = *it;
        bullet.move(10);
        if (!bullet.isActive())
        {
          it = bullets.erase(it);
        }
        else
        {
          ++it;
        }
      }
      glutPostRedisplay();
      updateMutex.unlock();
      updateBulletsAndEnemies();
      updateBulletAndBoss();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }

  void shoot(int xOffset)
  {
    if (availableBullets > 0)
    {
      availableBullets--;
      bullets.push_back(Bullet(xOffset + 47.5, 75));
    }
    else
    {
      printf("No bullets\n");
    }
  }
};