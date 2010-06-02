#include <GL/glut.h>
#include <iostream>
#include "Todasmalhas.h"


using namespace boost::numeric::ublas;

/*************************************************************************
 * NOME: M[4][4]
 * DESCRICAO: Matriz superficies de bezier.
 * **********************************************************************/
matrix<double> M (4, 4);
matrix<Malhas::Ponto> Pontos (4,4);

const double Mcpy[16] = {
    -1.0,  3.0,-3.0, 1.0,
     3.0, -6.0, 3.0, 0.0,
    -3.0,  3.0, 0.0, 0.0,
     1.0,  0.0, 0.0, 0.0
};



void matrixInitialize(matrix<double> &M, const double M_copy[]) {
    for (int i = 0; i < M.size1(); i++)
        for (int j = 0; j < M.size2(); j++)
            M(i, j) = M_copy[j * M.size1() + i];
}
/*************************************************************************
 * NOME: Mt[4][4]
 * DESCRICAO: Matriz transposta da matriz de superficie
 * **********************************************************************/
/*double Mt[4][4] = 
    { {-1.0, 3.0, -3.0, 1.0 },
      { 3.0, -6.0, 3.0, 0.0 },
      { -3.0, 3.0, 0.0, 0.0 },
      {  1.0, 0.0, 0.0, 0.0 }};
*/


/*************************************************************************
 * NOME: Malha() -Construtor
 * DESCRICAO: Cria pontos de controle da superficie
 * **********************************************************************/
Malhas::Malha::Malha(){
    matrixInitialize(M, Mcpy);
    
    double x = -0.5;
    double y = -0.6;
    std::cout << Pontos.size1() << "\t" << Pontos.size2() << std::endl;
    for(int i = 0; i < Pontos.size1(); i++){
        for(int j = 0; j < Pontos.size2(); j++){
            Ponto ponto(x, y, -5.0);
            Pontos(i, j) = ponto;
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
    matrix<double> Mtransposta = trans(M); //Matriz transposta de M
    matrix<double> Mx (4,4);
    matrix<double> My (4,4);
    matrix<double> Mz (4,4);

    for(int i = 0; i < Pontos.size1(); i++)
        for(int j = 0; j < Pontos.size2(); j++){
            Mx(i,j) = Pontos(i,j).getx();
            My(i,j) = Pontos(i,j).gety();
            Mz(i,j) = Pontos(i,j).getz();
            glBegin(GL_LINES);
                glVertex3f(Pontos(i, j).getx(), Pontos(i, j).gety(), Pontos(i, j).getz());
            
        }
    glEnd();
    
    vector<double> vetorU (4);
    vector<double> vetorV (4);
    for(u = 0.0; u <= 1.0; u += inc ){
        vetorU(0) = pow(u,3); vetorU(1) = pow(u,2);
        vetorU(2) = pow(u,1); vetorU(3) = pow(u,0);
        for(v = 0.0; v <= 1.0; v += inc ){
            vetorV(0) = pow(u,3); vetorV(1) = pow(u,2);
            vetorV(2) = pow(u,1); vetorV(3) = pow(u,0);
            vector<double> vetorVTrans = trans(vetorV);
            vector<double> aux1 = prod(vetorU, M);
            vector<double> aux2 = prod(aux1, Mx);
            vector<double> aux3 = prod(aux2, Mtransposta);
            x = inner_prod(aux3, vetorVTrans);
            
            //Calculo para componente y:
            aux2 = prod(aux1, My);
            aux3 = prod(aux2, Mtransposta);
            y = inner_prod(aux3, vetorVTrans);
            
            //Calculo para componente z:
            aux2 = prod(aux1, Mz);
            aux3 = prod(aux2, Mtransposta);
            z = inner_prod(aux3, vetorVTrans);
            
            //Desenhar Pontos na tela:
            glBegin(GL_LINES);
                glVertex3f(x, y, z);
        }
                
    }
 
    glEnd();
 
    //Repetir o processo para v primeiro:
    for(v = 0.0; v <= 1.0; v += inc ){
        vetorU(0) = pow(u,3); vetorU(1) = pow(u,2);
        vetorU(2) = pow(u,1); vetorU(3) = pow(u,0);
        for(u = 0.0; u <= 1.0; u += inc ){
            vetorV(0) = pow(u,3); vetorV(1) = pow(u,2);
            vetorV(2) = pow(u,1); vetorV(3) = pow(u,0);
            vector<double> vetorVTrans = trans(vetorV);
            vector<double> aux1 = prod(vetorU, M);
            vector<double> aux2 = prod(aux1, Mx);
            vector<double> aux3 = prod(aux2, Mtransposta);
            x = inner_prod(aux3, vetorVTrans);
            
            //Calculo para componente y:
            aux2 = prod(aux1, My);
            aux3 = prod(aux2, Mtransposta);
            y = inner_prod(aux3, vetorVTrans);
            
            //Calculo para componente z:
            aux2 = prod(aux1, Mz);
            aux3 = prod(aux2, Mtransposta);
            z = inner_prod(aux3, vetorVTrans);
            
            //Desenhar Pontos na tela:
            glBegin(GL_POINTS);
                glVertex3f(x, y, z);
        }
                
    }
    glEnd();
    
   glutSwapBuffers();

}
