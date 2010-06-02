#include <GL/glut.h>
#include "Todasmalhas.h"

void init(){
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST); //Habilita variavel de estado pra habilitar 3D quando uma coisa estah na frente de outra
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0,    //esquerdo em x
             3.0,    //direito em x
            -3.0,    //bottom em y
             3.0,    //top em y
             1.0,    //near
             20.0);  //far
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 2, 3, 0, 1, 0, 0, 1, 0);
}

void draw(){
    Malhas::Malha malhaExemplo;
    glColor3f(0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_TRIANGLES);

	/*//Triangle
	glVertex3f(0.0f, 1.0f, -5.0f);
	glVertex3f(-1.0f, -2.0f, -5.0f);
	glVertex3f(2.0f, -2.0f, -5.0f);
	/*glVertex3f(-0.5f, -0.5f, -5.0f);
	glVertex3f(0.5f, -0.5f, -5.0f);
	glVertex3f(-0.5f, 0.0f, -5.0f);*

	glEnd();*/

    malhaExemplo.plotarPontos();
    glutSwapBuffers();
}

void Resize(int width, int height){
  /*  //Mostra Opengl como mapear para tela
    glViewport(0, 0, width, height);
    //Altera pra configuraçao da camera perpectiva
    glMatrixMode(GL_PROJECTION);
    //Define a perpectiva da camera
    glLoadIdentity(); //Reseta a camera
    /*gluPerspective(30.0,                            // angulo da camera
                   (double)width / (double)height,  // Aspect ratio
                   1.0,                             // coord z proxima
                   20.0);                          // coord z + distante
    */
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
