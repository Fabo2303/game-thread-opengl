#include <GL/freeglut.h>
#include <iostream>
#include "../utils/drawUtils.cpp"

int vectorDefender[26][27] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 8, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0},
    {0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6, 7, 8, 8, 8, 7, 6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0},
    {0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 6, 7, 8, 8, 8, 7, 6, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 5, 1, 0, 0, 6, 7, 8, 0, 8, 7, 6, 0, 0, 1, 5, 1, 0, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0},
    {0, 1, 2, 1, 4, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 4, 1, 2, 1, 0},
    {0, 1, 2, 1, 1, 5, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 4, 1, 1, 2, 1, 0},
    {0, 1, 2, 1, 0, 1, 5, 1, 1, 2, 2, 1, 1, 2, 1, 1, 2, 2, 1, 1, 5, 1, 0, 1, 2, 1, 0},
    {0, 1, 1, 1, 0, 1, 1, 4, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 4, 1, 1, 0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0, 1, 1, 1, 5, 1, 1, 1, 1, 2, 1, 1, 1, 1, 5, 1, 1, 1, 0, 0, 1, 0, 0},
    {0, 0, 4, 0, 0, 1, 1, 1, 1, 4, 1, 1, 4, 4, 4, 1, 1, 4, 1, 1, 1, 1, 0, 0, 4, 0, 0},
    {0, 0, 5, 0, 0, 1, 1, 1, 0, 1, 1, 4, 5, 5, 5, 4, 1, 1, 0, 1, 1, 1, 0, 0, 5, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 4, 5, 5, 5, 5, 5, 4, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 4, 5, 5, 5, 4, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 1, 1, 4, 4, 4, 1, 1, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1, 1, 2, 1, 1, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

class Defender
{
public:
  int xOffset;
  Defender(int x)
  {
    xOffset = x;
  }

  void moveRight(int xVelocity)
  {
    xOffset <= 1320 ? xOffset += xVelocity : xOffset = 1320;
  }

  void moveLeft(int xVelocity)
  {
    xOffset >= 0 ? xOffset -= xVelocity : xOffset = 0;
  }
  
  void draw()
  {
    glPushMatrix();
    glTranslatef(xOffset, 0, 0);
    drawDefender();
    glPopMatrix();
  }

  void drawDefender()
  {
    for (int i = 0; i < 26; i++)
    {
      for (int j = 0; j < 27; j++)
      {
        if (vectorDefender[i][j] == 1)
        {
          glColor3f(0.0f, 0.0f, 0.0f); // Amarillo
          drawSquare(j, i);
        }
        else if (vectorDefender[i][j] == 2)
        {
          glColor3f(0.5f, 0.5f, 0.5f); // Gris
          drawSquare(j, i);
        }
        else if (vectorDefender[i][j] == 4)
        {
          glColor3f(1.0f, 0.0f, 1.0f); // Morado
          drawSquare(j, i);
        }
        else if (vectorDefender[i][j] == 5)
        {
          glColor3f(1.0f, 0.8f, 0.0f); // Lila
          drawSquare(j, i);
        }
        else if (vectorDefender[i][j] == 6)
        {
          glColor3f(1.0f, 0.0f, 0.0f); // Rojo
          drawSquare(j, i);
        }
        else if (vectorDefender[i][j] == 7)
        {
          glColor3f(1.0f, 1.0f, 1.0f); // Anaranjado
          drawSquare(j, i);
        }
        else if (vectorDefender[i][j] == 8)
        {
          glColor3f(1.0f, 1.0f, 0.0f); // Amarillo
          drawSquare(j, i);
        }
      }
    }
  }

  int getXOffset()
  {
    return xOffset;
  }
};