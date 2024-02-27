#include <GL/freeglut.h>
#include <iostream>
#include <string>

void drawSquare(float x, float y, float size = 3)
{
  x = x * size;
  y = y * size;
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + size, y);
  glVertex2f(x + size, y + size);
  glVertex2f(x, y + size);
  glEnd();
}

void drawText(float x, float y, std::string text)
{
  glPushMatrix();
  glColor3f(1.0, 1.0, 1.0);
  glRasterPos2f(x, y);
  for (char c : text)
  {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
  }
  glPopMatrix();
}

void drawLevel(float x, float y, int level){
  std::string levelText = "LEVEL " + std::to_string(level);
  drawText(x, y, levelText);
}