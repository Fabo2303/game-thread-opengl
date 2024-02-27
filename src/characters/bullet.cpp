#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <thread>
#include "./enemy.cpp"
#include "./boss.cpp"

int BULLET_SIZE = 10;

class Bullet
{
private:
  float x, y;
  bool active;

public:
  Bullet(float x, float y)
  {
    this->x = x;
    this->y = y;
    this->active = true;
    printf("Bullet created\n");
    printf("x: %f\n", getX());
    printf("y: %f\n", getY());
  }

  void draw()
  {
    if (active)
    {
      glBegin(GL_QUADS);
      glColor3f(1, 0, 0); // Rojo
      glVertex2f(x, y);
      glVertex2f(x + BULLET_SIZE, y);
      glVertex2f(x + BULLET_SIZE, y + 2 * BULLET_SIZE);
      glVertex2f(x, y + 2 * BULLET_SIZE);
      glEnd();
    }
  }

  float getX()
  {
    return x;
  }

  float getY()
  {
    return y;
  }

  bool isActive()
  {
    return active;
  }

  void setActive(bool active)
  {
    this->active = active;
  }

  void move(float speed)
  {
    y += speed;
    if (y > glutGet(GLUT_WINDOW_HEIGHT))
    {
        active = false;
    }
  }

  bool checkCollision(Enemy &enemy)
  {
      return (x < enemy.getX() + 75 && x + BULLET_SIZE > enemy.getX() && y < enemy.getY() + 47.5 && y + BULLET_SIZE > enemy.getY());
  }

  bool checkCollision(Boss &boss){
    return (x < boss.getX() + 310 && x + BULLET_SIZE > boss.getX() && y < boss.getY() + 355 && y + BULLET_SIZE > boss.getY());
  }
};