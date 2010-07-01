#include <GL/glut.h>
#include "Todasmalhas.h"

int zoom = 60;
int tipoMalha = -1;
Malhas::Malha malha;
void init(){
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST); //Habilita variavel de estado pra habilitar 3D quando uma coisa estah na frente de outra
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom, 1.0, 1.0, 30);
//    glOrtho(-5.0,    //esquerdo em x
//             5.0,    //direito em x
//            -5.0,    //bottom em y
//             5.0,    //top em y
//             -1.0,    //znear
//             10.0);  //zfar
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(6, 6, 6, 0, 0, 0, 0, 1, 0);
}
float _angle = 0.f;
void draw(){
    glColor3f(0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glRotatef(_angle, 0., 1.0, 0.);
    glColor3f(1.0, 1.0, 1.0);

    if(tipoMalha != -1)
        malha.plotarPontos();
    
    glutSwapBuffers();
}

void update(int value){
    _angle = 0.;
    if(value == 1)
        _angle += 2.0f;
    else
        _angle -= 2.0f;
}

//Trata teclas especiais
void specialKeys(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT:  update(0); break;
        case GLUT_KEY_RIGHT: update(1); break;
        case GLUT_KEY_UP: if (zoom < 250)
                                zoom += 5;
                           init(); 
                            break;
        case GLUT_KEY_DOWN: if (zoom > 10) 
                                zoom -= 5;
                            init(); 
                            break;
    }
   glutPostRedisplay();
}

void processMenuEvents(int option){
    switch(option){
        case 1: tipoMalha = option; malha.setMatrix(option); break;
        case 2: tipoMalha = option; malha.setMatrix(option); break;
        case 3: tipoMalha = option; malha.setMatrix(option); break;
    }    
    glutPostRedisplay();
}

void createGlutMenu(){
    int menu;
    menu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Malha Bezier", 1);
    glutAddMenuEntry("Malha Splines", 2);
    glutAddMenuEntry("Malha Catmul-Rom", 3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
    glutSpecialFunc(specialKeys);
    //glutTimerFunc(25, update, 0);

    createGlutMenu();
    glutMainLoop();
    return 0;
}
