/*************************************************************************
 * NOME: main.cpp
 * DESCRICAO: Cria tela em OpenGl e plota malhas na tela.
 * AUTOR: Pedro Henrique Linhares Mota da Silva  
 * E-mail: pedrolmota@gmail.com 
 * DATA: 05/07/2010
 * ***********************************************************************/

#include <GL/glut.h>
#include "Todasmalhas.h"

//Variaveis globais
float _angle = 0.f;
int zoom = 60;
int tipoMalha = -1;
Malhas::Malha malha;

/*************************************************************************
 * NOME: init
 * DESCRICAO: Inicializa variaveis de ambiante do OpenGl e cria plano 3D.
 * **********************************************************************/
void init(){
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom, 1.0, 1.0, 30);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(6, 6, 6, 0, 0, 0, 0, 1, 0);
}

/*************************************************************************
 * NOME: draw
 * DESCRICAO: Desenha pontos da malha atraves da chamada plotarPontos do
 * objeto malha da classe Malha.
 * **********************************************************************/
void draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(tipoMalha != -1)
        malha.plotarPontos();
    
    glutSwapBuffers();
}
/*************************************************************************
 * NOME: update
 * DESCRICAO: Rotaciona a cena.
 * **********************************************************************/
void update(int value){
    _angle = 0.;
    if(value == 1)
        _angle += 2.0f;
    else
        _angle -= 2.0f;
    
    glRotatef(_angle, 0., 1.0, 0.);
}

/*************************************************************************
 * NOME: specialKeys
 * DESCRICAO: Trata o uso de teclas especiais. Tecla <- rotaciona cena para
 * a esquerda, tecla -> rotaciona para a direita e tecla seta pra cima e pra
 * baixo faz zoom in e zoom out.
  * **********************************************************************/
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

/*************************************************************************
 * NOME: processMenuEvents
 * DESCRICAO: Executa as opcoes do menu. Cria a respectiva malha de acordo
 * com a opcao (option) escolhida no menu.
 * **********************************************************************/
void processMenuEvents(int option){
    switch(option){
        case 1: tipoMalha = option; malha.setMatrix(option); break;
        case 2: tipoMalha = option; malha.setMatrix(option); break;
        case 3: tipoMalha = option; malha.setMatrix(option); break;
    }    
    glutPostRedisplay();
}

/*************************************************************************
 * NOME: createGlutMenu
 * DESCRICAO: Cria o menu como as opcoes de criar as malhas de Bezier, 
 * Splines e de Catmull-Rom.
 * **********************************************************************/
void createGlutMenu(){
    int menu;
    menu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Malha Bezier", 1);
    glutAddMenuEntry("Malha Splines", 2);
    glutAddMenuEntry("Malha Catmul-Rom", 3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/*************************************************************************
 * NOME: Resize
 * DESCRICAO: Trata evento de redimensionamento da janela.
 * **********************************************************************/
void Resize(int width, int height){
}

/*************************************************************************
 * NOME: main
 * DESCRICAO: Cria janela do Glut e registra as funcoes de callback.
 * **********************************************************************/
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);

    glutCreateWindow("Malhas 3D");

    init();

    glutDisplayFunc(draw);
    glutReshapeFunc(Resize);
    glutSpecialFunc(specialKeys);

    createGlutMenu();
    glutMainLoop();
    return 0;
}
