#include <GL/freeglut.h>
#include <iostream>
#include "../include/utils/drawUtils.h"

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawSquare(0.0f, 0.0f, 5.0f);

    drawLevel(-2.5f, 3.0f, 1);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow("Juego OpenGL");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutMainLoop();

    return 0;
}
