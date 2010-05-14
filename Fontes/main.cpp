#include <GL/glut.h>
#include "Todasmalhas.h"

void init(){
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);
}

void draw(){
    Malhas::Malha malhaExemplo;
    glColor3f(0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0, 1.0, 1.0);

//    glBegin(GL_POINTS);
//        glVertex3f(0.0f, 0.0f, -5.0f);
//        glVertex3f(0.7f, 0.5f, -0.5f);
//    glEnd();
    malhaExemplo.plotarPontos();
    glutSwapBuffers();
}

void Resize(int width, int height){
    //Mostra Opengl como mapear para tela
    glViewport(0, 0, width, height);
    //Altera pra configuraçao da camera perpectiva
    glMatrixMode(GL_PROJECTION);
    //Define a perpectiva da camera
    glLoadIdentity(); //Reseta a camera
    gluPerspective(45.0,                            // angulo da camera
                   (double)width / (double)height,  // Aspect ratio
                   1.0,                             // coord z proxima
                   200.0);                          // coord z + distante
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);

    glutCreateWindow("Malhas 3D");

    init();

    glutDisplayFunc(draw);
    glutReshapeFunc(Resize);
    glutMainLoop();
    return 0;
}
