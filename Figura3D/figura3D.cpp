#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <vector>

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

std::vector<Faces> facesGlobal;

void init(){
    glEnable(GL_DEPTH_TEST); //Habilita variavel de estado pra habilitar 3D quando uma coisa estah na frente de outra
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0,    //esquerdo em x
             3.0,    //direito em x
            -3.0,    //bottom em y
             3.0,    //top em y
             1.0,    //near
             20.0);  //far
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4, 4, 4, 0, 1, 0, 0, 1, 0);
}

void handleResize(int w, int h) {
	//glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION); //indicado usar somente aqui...eu acho
//	glLoadIdentity();            //carrega matrix identidade para transformaçoes
//	gluPerspective(45.0f, (double)w / (double)h, 1.0, 200.0);   //ponto de vista do olho..

}

float _angle = 30.f;
float _cameraAngle = 0.0f;

void draw(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    //glColor3f(0.0,1.0,1.0);

    glRotatef(_angle,0.0f,0.0f,1.0f);
    //Começa a desenhar...
  
   /* glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(2.3f, 1.0f, -5.0f);
	glVertex3f(1.0f, -2.0f, -5.0f);
	glVertex3f(-2.5f, 0.5f, 5.0f); */
	/*glVertex3f(-0.5f, -0.5f, -5.0f);
	glVertex3f(0.5f, -0.5f, -5.0f);
	glVertex3f(-0.5f, 0.0f, -5.0f);*/

//	glEnd(); 
    glRotatef(_angle, 0.0f, 1.0f, 0.0f);
    //Faces obtidas lendo arquivo
    glBegin(GL_LINE_STRIP);
        for(int i = 0; i < facesGlobal.size(); i++){
           // std::cout << "face " << i << std::endl;
            for(int j = 0; j < facesGlobal[i].vertices.size(); j++){
                glVertex3f(facesGlobal[i].vertices[j].coordX, facesGlobal[i].vertices[j].coordY, facesGlobal[i].vertices[j].coordZ);
                //std::cout << facesGlobal[i].vertices[j].coordX <<  facesGlobal[i].vertices[j].coordY <<  facesGlobal[i].vertices[j].coordZ << std::endl;
            }
        }
    glEnd();

/*
	glBegin(GL_QUADS); //Begin quadrilateral coordinates

	//Trapezoid
	glVertex3f(-0.7f, -1.5f, -5.0f);
	glVertex3f(0.7f, -1.5f, -5.0f);
	glVertex3f(0.4f, -0.5f, -5.0f);
	glVertex3f(-0.4f, -0.5f, -5.0f);

	glEnd(); //End quadrilateral coordinates
*/
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
    facesGlobal = face;
    for(int i = 0; i < numFaces; i++){
        fscanf(file, "%i", &numVertices);
        for(int j = 0; j < numVertices; j++){
            fscanf(file, "%i", &vertice);
            facesGlobal[i].vertices.push_back(vertices[vertice]);
//            std::cout << vertice << std::endl;
        }
    }
}





int main(int argc, char* argv[]){

    //Iniciando o Glut
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Criando a janela indiscreta!
    glutInitWindowSize(500,500);
    glutCreateWindow("Lendo do arquivo");

    //habilita GL_DEPTH_TEST
    init();

    readFile("cubo.txt");
    glutDisplayFunc(draw);
    glutReshapeFunc(handleResize);

    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}

