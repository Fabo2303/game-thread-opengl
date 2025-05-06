#ifndef ENEMY_H
#define ENEMY_H

#include <GL/freeglut.h>
#include <atomic>

class Enemy {
private:
    float x, y;
    int type;
    std::atomic<bool> active;

    void drawSquare(float _x, float _y, float size = 2.5f);

public:
    Enemy(float x, float y, int type);
    void draw();
    void drawExplosion();
    void move(float speed, bool &start);

    bool isActive() const;
    float getX() const;
    float getY() const;
    int getType() const;
    void setActive(bool active);
};

#endif // ENEMY_H
