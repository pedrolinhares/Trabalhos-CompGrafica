#include <GL/glut.h>
#include <iostream>
#include "Todasmalhas.h"

/*************************************************************************
 * NOME: M[4][4]
 * DESCRICAO: Matriz superficies de bezier.
 * **********************************************************************/
double M[4][4] =
    { {-1.0,  3.0,-3.0, 1.0 },
      { 3.0, -6.0, 3.0, 0.0 },
      {-3.0,  3.0, 0.0, 0.0 },
      { 1.0,  0.0, 0.0, 0.0 }};

/*************************************************************************
 * NOME: Mt[4][4]
 * DESCRICAO: Matriz transposta da matriz de superficie
 * **********************************************************************/
double Mt[4][4] = 
    { {-1.0, 3.0, -3.0, 1.0 },
      { 3.0, -6.0, 3.0, 0.0 },
      { -3.0, 3.0, 0.0, 0.0 };
      {  1.0, 0.0, 0.0, 0.0 }};

/*************************************************************************
 * NOME: Malha() -Construtor
 * DESCRICAO: Cria pontos de controle da superficie
 * **********************************************************************/
Malhas::Malha::Malha(){
    double x = -0.5;
    double y = -0.6;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            Ponto ponto(x, y, -5.0);
            Pontos[i][j] = ponto;
            y += 0.3;
        }
        x  += 0.25;
        y = -0.6;
    }
}
/**************************************************************************
 * NOME: plotarPontos()
 * DESCRICAO: Calcula e mostra os pontos de controle e da superficie 
 * na tela.
 * ***********************************************************************/
void Malhas::Malha::plotarPontos(){
    double u, v, inc = 0.1; 
    double x, y, z;
    double uM[4]  = {0, 0, 0, 0}; //Matriz multiplicacao das matrizes [1 u1 u2 u3] * M
    double vMt[4] = {0, 0, 0, 0}; //Matriz multiplicacao das matrizes Mt * [1 v1 v2 v3]

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++){
            glBegin(GL_POINTS);
                glVertex3f(Pontos[i][j].Getx(), Pontos[i][j].Gety(), Pontos[i][j].Getz());
            
        }
    glEnd();

    for(u = 0.0; u <= 1.0; u += inc ){
        for(v = 0.0; v <= 1.0; v += inc )
            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++){
                    uM[j] += pow(u, i) * M[i][j];  
                    vMt[i] += pow(v, j) * Mt[i][j];   
                }
    }

    for(v = 0.0; v <= 1.0; v += inc ){
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                vMt[i] += pow(v, j) * Mt[i][j];   
    }

    glutSwapBuffers();

}



//            std::cout<< Pontos[i][j].Getx() << '\t' << Pontos[i][j].Gety() <<'\t' << Pontos[i][j].Getz() << '\n';
