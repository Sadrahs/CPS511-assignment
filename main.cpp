
#include "robocop.h"// Main function


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Robocop OpenGL Model");
    initOpenGL();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
