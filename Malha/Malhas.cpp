#include <GL/glut.h>
#include <iostream>
#include "Todasmalhas.h"


using namespace boost::numeric::ublas;

matrix<double> M (4, 4);
matrix<Malhas::Ponto> Pontos (4,4);

/*************************************************************************
 * NOME: M[4][4]
 * DESCRICAO: Matriz superficies de bezier.
 * **********************************************************************/

//Matriz Bezier
const double MBezier[16] = {
    -1.0,  3.0,-3.0, 1.0,
     3.0, -6.0, 3.0, 0.0,
    -3.0,  3.0, 0.0, 0.0,
     1.0,  0.0, 0.0, 0.0
};


/*************************************************************************
 * NOME: MSplines[16]
 * DESCRICAO: Matriz superficies de Splines.
 * **********************************************************************/
const double MSplines[16] = {
    -1.0/6.,  3.0/6., -3.0/6., 1.0/6.,
     3.0/6,  -6.0/6,   0.0,    4.0/6.,
    -3.0/6.,  3.0/6,   3.0/6., 1.0/6., 
     1.0/6.,  0.0,     0.0,    0.0
};

//Matrix original de Splines. Foi necessario usar a transposta dessa matrix devido a forma
//como foi implementada a funcao matrixInitialize que pega as colunas da matrix
//ao inves das linhas
//    -1.0,  3.0, -3.0, 1.0.,
//     3.0., -6.0,  3.0., 0.0,
//    -3.0,    0.0,  3.0, 0.0,
//     1.0,  4.0,  1.0, 0.0
//};

/*************************************************************************
 * NOME: MSplines[16]
 * DESCRICAO: Matriz superficies de Catmull-Rom.
 * **********************************************************************/
const double MCatmullRom[16] = {
    -1.0,  2.0, -1.0, 0.0,
     3.0, -5.0,  0.0, 2.0,
    -3.0,  4.0,  1.0, 0.0,
     1.0, -1.0,  0.0, 0.0
};

//Matrix original de Catmull-Rom. Foi necessario usar a transposta dessa matrix devido a forma
//como foi implementada a funcao matrixInitialize que pega as colunas da matrix
//ao inves das linhas
//    -1.0,  3.0, -3.0,  1.0,
//     2.0, -5.0,  4.0, -1.0,
//    -1.0,  0.0,  1.0,  0.0,
//     0.0,  2.0,  0.0,  0.0
//};

//Matriz de elementos z dos Pontos de referencia
const double matrixZ[16] = {
     3.0, 2.0, 3.0, 2.0,
     3.0, 2.5, 3.0, 3.5,
     2.7, 3.0, 1.2, 1.7,
     1.0, 1.5, 2.0, 3.0
}; 

void matrixInitialize(matrix<double> &M, const double M_copy[]) {
    for (int i = 0; i < M.size1(); i++)
        for (int j = 0; j < M.size2(); j++){
            M(i, j) = M_copy[j * M.size1() + i];
        }
}

/*************************************************************************
 * NOME: Malha() -Construtor
 * DESCRICAO: Cria pontos de controle da superficie
 * **********************************************************************/
Malhas::Malha::Malha(){
    double x = -2.5;
    double y = -1.6;
    for(int i = 0; i < Pontos.size1(); i++){
        for(int j = 0; j < Pontos.size2(); j++){
            Ponto ponto(x, y, matrixZ[j * Pontos.size1() + i]);
            Pontos(i, j) = ponto;
            y += 1.3;
        }
        x  += 1.0;
        y = -1.6;
    }
}
void Malhas::Malha::setMatrix(int matrixType){
    if(matrixType == 1)
        matrixInitialize(M, MBezier);
    if(matrixType == 2)
        matrixInitialize(M, MSplines);
    if(matrixType == 3)
        matrixInitialize(M, MCatmullRom);
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
    int contador = 0;
    for(int i = 0; i < Pontos.size1(); i++)
        for(int j = 0; j < Pontos.size2(); j++){
            Mx(i,j) = Pontos(i,j).getx();
            My(i,j) = Pontos(i,j).gety();
            Mz(i,j) = Pontos(i,j).getz();
            glBegin(GL_POINTS);
                glVertex3f(Pontos(i, j).getx(), Pontos(i, j).gety(), Pontos(i, j).getz());
            glEnd();
            
        }
    //std::cout << M << std::endl; 
    
    vector<double> vetorU (4);
    vector<double> vetorV (4);
    for(u = 0.0; u <= 1.0; u += inc ){
        vetorU(0) = pow(u,3); vetorU(1) = pow(u,2);
        vetorU(2) = pow(u,1); vetorU(3) = pow(u,0);
        for(v = 0.0; v <= 1.0; v += inc ){
            vetorV(0) = pow(v,3); vetorV(1) = pow(v,2);
            vetorV(2) = pow(v,1); vetorV(3) = pow(v,0);
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
            glBegin(GL_LINE_STRIP);
                glVertex3f(x, y, z);
        }
        glEnd();
                
    }
 
 
    //Repetir o processo para v primeiro:
    for(v = 0.0; v <= 1.0; v += inc ){
        vetorV(0) = pow(v,3); vetorV(1) = pow(v,2);
        vetorV(2) = pow(v,1); vetorV(3) = pow(v,0);
        for(u = 0.0; u <= 1.0; u += inc ){
        vetorU(0) = pow(u,3); vetorU(1) = pow(u,2);
        vetorU(2) = pow(u,1); vetorU(3) = pow(u,0);
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
            glBegin(GL_LINE_STRIP);
                glVertex3f(x, y, z);
        }
        glEnd();
                
    }
    
   glutSwapBuffers();

}
