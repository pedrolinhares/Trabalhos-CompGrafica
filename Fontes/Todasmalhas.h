#ifndef TODASMALHAS_H
#define TODASMALHAS_H

namespace Malhas{
    class Ponto{
        double x;
        double y;
        double z;
    public:
        Ponto(double _x, double _y, double _z):x(_x), y(_y), z(_z){};
        Ponto(){};
        double Getx(){return x;};
        double Gety(){return y;};
        double Getz(){return z;};
    };

    class Malha{
    protected:
        Ponto Pontos[4][4];
    public: 
        Malha();
        void plotarPontos();
    };
}

#endif
