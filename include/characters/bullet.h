#ifndef BULLET_H
#define BULLET_H

#include <GL/freeglut.h>
#include "enemy.h"
#include "boss.h"

class Bullet {
private:
    float x, y;
    bool active;

public:
    static constexpr int BULLET_SIZE = 10;

    Bullet(float x, float y);

    void draw() const;
    void move(float speed);
    
    float getX() const;
    float getY() const;
    bool isActive() const;
    void setActive(bool state);

    bool checkCollision(Enemy& enemy);
    bool checkCollision(Boss& boss);
};

#endif // BULLET_H
