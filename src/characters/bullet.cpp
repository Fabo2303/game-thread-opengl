#include "../../include/characters/bullet.h"
#include <iostream>

Bullet::Bullet(float x, float y) : x(x), y(y), active(true) {
    std::cout << "Bullet created at (" << x << ", " << y << ")\n";
}

void Bullet::draw() const {
    if (!active) return;

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + BULLET_SIZE, y);
    glVertex2f(x + BULLET_SIZE, y + 2 * BULLET_SIZE);
    glVertex2f(x, y + 2 * BULLET_SIZE);
    glEnd();
}

void Bullet::move(float speed) {
    y += speed;
    if (y > glutGet(GLUT_WINDOW_HEIGHT)) {
        active = false;
    }
}

float Bullet::getX() const { return x; }
float Bullet::getY() const { return y; }
bool Bullet::isActive() const { return active; }
void Bullet::setActive(bool state) { active = state; }

bool Bullet::checkCollision(Enemy& enemy) {
    return (x < enemy.getX() + 75 && x + BULLET_SIZE > enemy.getX() &&
            y < enemy.getY() + 47.5f && y + BULLET_SIZE > enemy.getY());
}

bool Bullet::checkCollision(Boss& boss) {
    return (x < boss.getX() + 310 && x + BULLET_SIZE > boss.getX() &&
            y < boss.getY() + 355 && y + BULLET_SIZE > boss.getY());
}
