#include "Todasmalhas.h"
#include <GL/glut.h>

Malhas::Malha::Malha(){
    for(int i = 0; i < 4; i++){
        double x = -0.5;
        for(int j = 0; j < 4; j++){
            double y = -0.6;
            Ponto ponto(x, y, -5.0);
            Pontos[i][j] = ponto;
            y += 0.3;
        }
        x  += 0.25;
    }
}

void Malhas::Malha::plotarPontos(){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++){
            glBegin(GL_POINTS);
                glVertex3f(Pontos[i][j].Getx(), Pontos[i][j].Gety(), Pontos[i][j].Getz());
            
        }
    glEnd();
    glutSwapBuffers();

}
