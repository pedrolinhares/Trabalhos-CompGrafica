#include <fstream>
#include <vector>
#include <GL/glut.h>

struct Vertices{
    float coordX;  
    float coordY;
    float coordZ;
};

typedef Vertices Vertice; 

struct Face{
    std::vector<Vertice> vertices;
};

typedef Face Faces;

int readFile(char* fileStr);

std::vector<Faces> globalFaces;

void init(){
    glEnable(GL_DEPTH_TEST); //Habilita variavel de estado pra habilitar 3D quando uma coisa estah na frente de outra
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0,    //esquerdo em x
             10.0,    //direito em x
            -10.0,    //bottom em y
             10.0,    //top em y
             -5.0,    //znear
             20.0);  //zfar
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0);
}

void handleResize(int w, int h) {
/*Tratar o aumento da tela aqui.*/
}

float _angle = 0.f;

void draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(_angle, 1.0f, 1.0f, 0.0f);
    
    //Faces obtidas lendo arquivo
        for(int i = 0; i < globalFaces.size(); i++){
            glBegin(GL_LINE_LOOP);
            for(int j = 0; j < globalFaces[i].vertices.size(); j++){
                glVertex3f(globalFaces[i].vertices[j].coordX, globalFaces[i].vertices[j].coordY, globalFaces[i].vertices[j].coordZ);
            }
            glEnd();
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

