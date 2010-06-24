#include <GL/glut.h>
#include "Todasmalhas.h"

void init(){
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST); //Habilita variavel de estado pra habilitar 3D quando uma coisa estah na frente de outra
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0,    //esquerdo em x
             5.0,    //direito em x
            -5.0,    //bottom em y
             5.0,    //top em y
             -1.0,    //near
             10.0);  //far
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(6, 6, 6, 0, 0, 0, 0, 0, 1);
}
float _angle = 0.f;
void draw(){
    Malhas::Malha malhaExemplo;
    glColor3f(0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //glRotatef(_angle, 0., 1.0, 0.);
    glColor3f(1.0, 1.0, 1.0);

    malhaExemplo.plotarPontos();
    glutSwapBuffers();
}

void update(int value){
    _angle += 2.0f;
    if(_angle > 360)
        _angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

void Resize(int width, int height){
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);

    glutCreateWindow("Malhas 3D");

    init();

    glutDisplayFunc(draw);
    glutReshapeFunc(Resize);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
