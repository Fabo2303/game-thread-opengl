#ifndef BOSS_H
#define BOSS_H

#include <GL/freeglut.h>

class Boss {
private:
    float x, y;
    bool active;
    bool bulletActive;
    int life;

    static constexpr int BOSS_WIDTH = 310;
    static constexpr int BOSS_HEIGHT = 355;
    static constexpr int BULLET_WIDTH = 30;
    static constexpr int BULLET_HEIGHT = 900;

    void drawSqua(float _x, float _y, float size = 5) const;
    void drawSquaBullet(float _x, float _y, float size = 5) const;

public:
    static unsigned int vectorBoss[71][62];
    static unsigned int vectorBulletBoss[32][4];

    Boss();
    void draw() const;
    void drawBullet() const;
    
    float getX() const;
    float getY() const;
    bool isActive() const;
    void setActive(bool active);

    bool checkCollision(int xOffset) const;
    void decreaseLife();
    void attack();
    void move(float speed);
};

#endif // BOSS_H
