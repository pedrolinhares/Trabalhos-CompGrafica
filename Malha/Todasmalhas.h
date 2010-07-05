/*************************************************************************
 * NOME: Todasmalhas.h 
 * DESCRICAO: Define a o namespace Malhas que contem as classes Ponto e 
 * Malha.
 * AUTOR: Pedro Henrique Linhares Mota da Silva  
 * E-mail: pedrolmota@gmail.com 
 * DATA: 05/07/2010
 * ***********************************************************************/

#ifndef TODASMALHAS_H
#define TODASMALHAS_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

namespace Malhas{
    class Ponto{
        double x;
        double y;
        double z;
    public:
        Ponto(double _x, double _y, double _z):x(_x), y(_y), z(_z){};
        Ponto(const Ponto& );
        Ponto(){};
        double getx() const {return x;};
        double gety() const {return y;};
        double getz() const {return z;};
    };

    class Malha{
    protected:
       // matrix<Ponto> Pontos;
      
    public: 
        Malha();
        void plotarPontos();
        void setMatrix(int);
    };
}

inline Malhas::Ponto::Ponto(const Ponto& pt){
    x = pt.getx();
    y = pt.gety();
    z = pt.getz();
}
#endif
