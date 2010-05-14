#include <GL/glut.h>
#include <iostream>
#include "Todasmalhas.h"

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

void Malhas::Malha::plotarPontos(){
    std::cout << "teste...\n";
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++){
            std::cout<< Pontos[i][j].Getx() << '\t' << Pontos[i][j].Gety() <<'\t' << Pontos[i][j].Getz() << '\n';
            glBegin(GL_POINTS);
                glVertex3f(Pontos[i][j].Getx(), Pontos[i][j].Gety(), Pontos[i][j].Getz());
            
        }
    glEnd();
    glutSwapBuffers();

}
