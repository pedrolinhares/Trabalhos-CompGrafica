#include <GL/glut.h>

void init(){
    glEnable(GL_DEPTH_TEST);
}

void draw(){
    glColor3f(0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POINTS);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(1.5f, 0.5f, -0.5f);
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);

    glutCreateWindow("Malhas 3D");

    init();

    glutDisplayFunc(draw);

    glutMainLoop();
    return 0;
}
