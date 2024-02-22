#include <gl/freeglut.h>

void teclado(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'd':
    // Mover a la derecha
    break;
  case 'a':
    // Mover a la izquierda
    break;
  case ' ':
    // Disparar
    break;
  }
  glutPostRedisplay();
}

void update(int value){
  // Actualizar el juego
  glutTimerFunc(1000/60, update, 0);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0, 0, 0.5, 0.8);
  glLoadIdentity();
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

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(1400, 900);
  glutInitWindowPosition(200, 50);
  glutCreateWindow("La ultima esperanza");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(teclado);
  glutMainLoop();
  return 0;
}