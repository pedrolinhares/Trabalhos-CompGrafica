#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <GL/glut.h>

struct Vertice{
    float coordX;  
    float coordY;
    float coordZ;
};

struct VetorNormal {
    float coordX;
    float coordY;
    float coordZ;
};

struct Face{
    std::vector<Vertice> vertices;
    VetorNormal normal;
};

typedef Face Faces;

int readFile(char* fileStr);

std::vector<Faces> globalFaces;

void init(){
    glEnable(GL_DEPTH_TEST);     //Habilita variavel de estado pra habilitar 3D quando uma coisa estah na frente de outra
    glEnable(GL_CULL_FACE);      //Habilita remocao de faces traseiras
    glEnable(GL_COLOR_MATERIAL); //Habilita a definicao da cor do material a partir da cor corrente
    glEnable(GL_LIGHTING);       //Habilita o uso de iluminacao
    glEnable(GL_LIGHT0);         //Habilita luz de numero 0
    glEnable(GL_DEPTH_TEST);     //Habilita o depth-buffer

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0,    //esquerdo em x
             10.0,    //direito em x
            -10.0,    //bottom em y
             10.0,    //top em y
             -5.0,    //znear
             20.0);   //zfar
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0);
}

void handleResize(int w, int h) {
/*Tratar o aumento da tela aqui.*/
}

float _angle = 0.f;

void calcularVetorNormalDaFace(Face& face){
    Vertice vetor1, vetor2;
    Vertice vetorNormal;

//Calcula vetor 1
    vetor1.coordX = face.vertices[1].coordX - face.vertices[0].coordX;
    vetor1.coordY = face.vertices[1].coordY - face.vertices[0].coordY;
    vetor1.coordZ = face.vertices[1].coordZ - face.vertices[0].coordZ;

//Calcula vetor 2
    vetor2.coordX = face.vertices[3].coordX - face.vertices[0].coordX;
    vetor2.coordY = face.vertices[3].coordY - face.vertices[0].coordY;
    vetor2.coordZ = face.vertices[3].coordZ - face.vertices[0].coordZ;
      
//Calcular vetor normal entre vetor1 e vetor2
    vetorNormal.coordX = vetor1.coordY * vetor2.coordZ - vetor1.coordZ * vetor2.coordY;
    vetorNormal.coordY = vetor1.coordZ * vetor2.coordX - vetor1.coordX * vetor2.coordZ;
    vetorNormal.coordZ = vetor1.coordX * vetor2.coordY - vetor1.coordY * vetor2.coordX;

//Normalizar vetor normal
  float tamanho = std::sqrt(vetorNormal.coordX * vetorNormal.coordX + vetorNormal.coordY * vetorNormal.coordY + vetorNormal.coordZ * vetorNormal.coordZ);
  vetorNormal.coordX /= tamanho; 
  vetorNormal.coordY /= tamanho;
  vetorNormal.coordZ /= tamanho;

//Atribui o vetor normal calculado a face
    face.normal.coordX = vetorNormal.coordX;
    face.normal.coordY = vetorNormal.coordY;
    face.normal.coordZ = vetorNormal.coordZ;

}

void draw(){
    float varCor = 0.0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(_angle, 1.0f, 1.0f, 0.0f);
    glCullFace(GL_BACK);
    //Faces obtidas lendo arquivo
        for(int i = 0; i < globalFaces.size(); i++){
            glColor3f(.1 + varCor, .9, .7);
            glBegin(GL_QUADS);//GL_LINE_LOOP
                glNormal3f(globalFaces[i].normal.coordX, globalFaces[i].normal.coordY, globalFaces[i].normal.coordZ);
                for(int j = 0; j < globalFaces[i].vertices.size(); j++){
                    glVertex3f(globalFaces[i].vertices[j].coordX, globalFaces[i].vertices[j].coordY, globalFaces[i].vertices[j].coordZ);
                }
            glEnd();
            varCor += .2;
        }
    
    glutSwapBuffers();
}

void update(int value){
    _angle += 2.0f;
    if(_angle > 360)
        _angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int readFile(char* fileStr){
    const int MAX = 80;
    char buff[80], verticesStr[10], facesStr[10];
    int numVertices, numFaces;
    float pointX, pointY, pointZ;
    int vertice;
    FILE* file;
    if(!(file = fopen(fileStr, "r")))
        return 1;
    fscanf(file,"%s %d", verticesStr, &numVertices);
    Vertice vertices[numVertices];

    for(int i = 0; i < numVertices; i++){
        fscanf(file, "%f %f %f", &pointX, &pointY, &pointZ );
        vertices[i].coordX = pointX;
        vertices[i].coordY = pointY;
        vertices[i].coordZ = pointZ;
    }
    
    fscanf(file,"%s %d", facesStr, &numFaces);
    std::vector<Faces> face(numFaces);
    globalFaces  = face;
    for(int i = 0; i < numFaces; i++){
        fscanf(file, "%i", &numVertices);
        for(int j = 0; j < numVertices; j++){
            fscanf(file, "%i", &vertice);
            globalFaces[i].vertices.push_back(vertices[vertice]);
        }
        calcularVetorNormalDaFace(globalFaces[i]);
    //Imprime o vetor normal calculado para a face
        std::cout << globalFaces[i].normal.coordX << '\t' << globalFaces[i].normal.coordY << '\t' << globalFaces[i].normal.coordZ << std::endl;
    }
}

int main(int argc, char* argv[]){
    //Iniciando o Glut
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Criando a janela indiscreta!
    glutInitWindowSize(500,500);
    glutCreateWindow("3D Cube");

    //habilita GL_DEPTH_TEST
    init();

    readFile("cubo.txt");
    glutDisplayFunc(draw);
    glutReshapeFunc(handleResize);

    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}

