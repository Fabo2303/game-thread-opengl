#include <GL/freeglut.h>
#include <string>
#include <thread>
#include <chrono>
#include "../include/characters/defender.h"
#include "../include/utils/operations.h"
#include "../include/utils/drawUtils.h"

Defender defender(500);
Operations operation;
int level = 0;
bool isChangeLevel = true;

void teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':
        defender.moveRight(10);
        break;
    case 'a':
        defender.moveLeft(10);
        break;
    case ' ':
        operation.shoot(defender.getXOffset());
        break;
    }
    glutPostRedisplay();
}

void updateLevel()
{
    while (level <= 2)
    {
        if (!operation.isGameChangeLevel() && isChangeLevel && level <= 2)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            level++;
            isChangeLevel = false;
            printf("Level: %d\n", level);
        }
    }
}

void update(int value)
{
    glutTimerFunc(1000 / 60, update, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0.5, 0.8);
    glLoadIdentity();

    defender.draw();

    if (operation.isGameChangeLevel())
    {
        operation.drawBoss();
        operation.drawEnemy();
        operation.drawBullets();
        operation.collisionDefenderBulletBoss(defender.getXOffset());
        isChangeLevel = true;
    }
    else
    {
        if (level > 0 && level <= 3 && !isChangeLevel)
        {
            operation.startGame(level);
        }
        else
        {
            drawText(650, 500, level == 3 ? "YOU WIN" : "Level: " + std::to_string(level + 1));
        }
    }

    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

void initOpenGL(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(1400, 900);
    glutInitWindowPosition(200, 50);
    glutCreateWindow("La ultima esperanza");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
}

int main(int argc, char **argv)
{
    initOpenGL(argc, argv);
    
    std::thread levelThread(updateLevel);
    glutMainLoop();
    
    return 0;
}
