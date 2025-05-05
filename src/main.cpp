#include <GL/freeglut.h>
#include <iostream>

// Función para manejar la visualización
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Configura el color de dibujo (rojo)
    glColor3f(1.0f, 0.0f, 0.0f);

    // Dibuja un triángulo
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
    glEnd();

    glutSwapBuffers(); // Cambia los buffers de la ventana
}

// Función principal
int main(int argc, char** argv) {
    // Inicializa GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Test OpenGL");

    // Configura la función de visualización
    glutDisplayFunc(display);

    // Inicia el bucle principal de GLUT
    glutMainLoop();

    return 0;
}
