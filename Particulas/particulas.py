from sys         import argv
from OpenGL.GL   import *
from OpenGL.GLUT import *
from OpenGL.GLU  import *

class Particula:
    def __init__(self, _posicao, _velocidade, _forca, _massa):
        self.velocidade     = _velocidade
        self.forca          = _forca
        self.posicao        = _posicao
        self.massa          = _massa
        self.gravidade      = [0, -9.8, 0]
        self.estadoAnterior = []

    def guardarEstadoAnterior(self):
        #cria lista [velocidade, forca, posicao]
        self.estadoAnterior.append(self.velocidade) 
        self.estadoAnterior.append(self.forca) 
        self.estadoAnterior.append(self.posicao) 
        
    def voltarAoEstadoAnterior(self):
        self.velocidade = self.estadoAnterior[0]
        self.forca      = self.estadoAnterior[1]
        self.posicao    = self.estadoAnterior[2]

class ParSys:
    def __init__(self, arquivo, _largura, _altura, _znear, _zfar):
        self.particulas = []
        self.largura    = _largura
        self.altura     = _altura
        self.znear      = _znear
        self.zfar       = _zfar
        self.carregarArquivo(arquivo)
        
    def carregarArquivo(self, _arquivo):
        valoresPosicao    = []
        valoresVelocidade = []
        valoresForca      = []
        self.arquivo = open(_arquivo,"r").readlines()
        lendoParticula = False
        for linha in self.arquivo:
            linha = linha.split()
            if len(linha) > 0:
                if linha[0] == 'dt':
                    self.deslocamento = float(linha[1])
                if linha[0] == 'g':
                    self.gravidade = float(linha[1])
                if linha[0] == 'particula':
                    lendoParticula = True
                if linha[0] == 'posicao' and lendoParticula == True:
                    if len(linha) >1:
                        valoresPosicao = linha[1].split(',')
                        valoresPosicao[0] = float(valoresPosicao[0])
                        valoresPosicao[1] = float(valoresPosicao[1])
                        valoresPosicao[2] = float(valoresPosicao[2])
                        
                if linha[0] == 'velocidade' and lendoParticula == True:
                    if len(linha) > 1:
                        valoresVelocidade = linha[1].split(',')
                        valoresVelocidade[0] = float(valoresVelocidade[0])
                        valoresVelocidade[1] = float(valoresVelocidade[1])
                        valoresVelocidade[2] = float(valoresVelocidade[2])
                            
                if linha[0] == 'forca' and lendoParticula == True:
                    if len(linha) > 1:
                        valoresForca = linha[1].split(',')
                        valoresForca[0] = float(valoresForca[0])
                        valoresForca[1] = float(valoresForca[1])
                        valoresForca[2] = float(valoresForca[2])
                         
                if linha[0] == 'massa' and lendoParticula == True:
                    massa = []
                    if len(linha) > 1:
                        massa = linha[1].split()
                        massa = float(massa[0])
                    self.particulas.append(Particula(valoresPosicao, valoresVelocidade, valoresForca, massa ) )
                    lendoParticula = False
    
    def calcularForca(self, particula):
        for i in range(3):
            particula.forca[i] += particula.massa * particula.gravidade[i] 

    def calcularVelocidade(self, particula):
        for i in range(3):
            particula.velocidade[i] += self.deslocamento * (particula.forca[i] / particula.massa)

    def calcularPosicao(self, particula):
        for i in range(3):
            particula.posicao[i] += self.deslocamento * particula.velocidade[i]
        print (particula.posicao[1])
        self.verificarColisaoInferior(particula)

    #verificar se posicao ultrapassa limite inferior
    #se sim, a particula deve retornar ao estado anterior
    def verificarColisaoInferior(self, particula):
        #calcular vetor (vetorV) entre a posicao da particula e o chao
        vetorV = []
        pontoInferior = [-self.largura/2, -self.altura/2, self.znear]
        for i in range(3):
            vetorV.append(particula.posicao[i] - pontoInferior[i])
        altura = vetorV[1]
        #o y no chao estah em 180.00 ... nao sei porque
        if(altura < 70):
            print "passou do chao ... corrigir isso!"

    def animar(self):
        for particula in self.particulas:
            particula.guardarEstadoAnterior()
            self.calcularForca(particula)
            self.calcularVelocidade(particula)
            self.calcularPosicao(particula)
        
        self.displayParticulas()

    def displayParticulas(self):
        glPointSize(3.0)
        glColor3f(1.0, 0., 0.0)
        glBegin(GL_POINTS)
        for particula in self.particulas:
            glVertex3f(particula.posicao[0], particula.posicao[1], particula.posicao[2])
        glEnd()
        glutSwapBuffers()

class Interface:
    def __init__(self):
        self.w = 500
        self.h = 500
        self.znear = 0.0
        self.zfar  = 600.0
        self.particulas = ParSys("dadosParticulas.txt", self.w, self.h, self.znear, self.zfar)

    def reshape(self, _w, _h):
        self.w = _w
        self.h = _h

    def init(self):
        glClearColor(0.0, 0.0, 0.0, 1.0)
        glMatrixMode(GL_PROJECTION)
        glEnable(GL_DEPTH_TEST) 
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluPerspective(70,  1.0, self.znear, self.zfar)
#        glOrtho(-300.0,   
#                 300.0,  
#                -300.0, 
#                 300.0,
#                 1.0,    #znear
#                 600.0)  #zfar
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        gluLookAt(0, 0, -50, 0, 0, 0, 0, 1, 0);


    def display(self):
        glClear(GL_COLOR_BUFFER_BIT)
        glColor3f(1.0, 1.0, 1.0)
        
        glBegin(GL_POINTS)
        glVertex3f(0, 0, 0)
        glEnd()
        #Chao
        glBegin(GL_POLYGON)
        glVertex3f(-self.w/2,-self.h/2, self.znear)
        glVertex3f(self.w/2,-self.h/2, self.znear)
        glVertex3f(self.w/2,-self.h/2, self.zfar)
        glVertex3f(-self.w/2,-self.h/2, self.zfar)
        glEnd()

        #parede esquerda
        glBegin(GL_POLYGON)
        glVertex3f(self.w/2,-self.h/2, self.znear)
        glVertex3f(self.w/2,self.h/2, self.znear)
        glVertex3f(self.w/2,self.h/2, self.zfar)
        glVertex3f(self.w/2,-self.h/2, self.zfar)
        glEnd()
    
        #self.particulas.displayParticulas()
        self.particulas.animar()

        glutSwapBuffers()
                    
    def update(self, value):
        glutPostRedisplay();
        glutTimerFunc(25, self.update, 0);


    def main(self):
        glutInit(argv)
        
        #Para resolver problema de falha de segmentacao - criar uma janela gambiarra
        glutCreateWindow("Gambiarra")
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
        glutInitWindowSize(self.w, self.h)
        glutCreateWindow("Malhas 3D")
        self.init()
        glutDisplayFunc(self.display)
        glutReshapeFunc(self.reshape)
        glutTimerFunc(25, self.update, 0);
        
        glutMainLoop()


if __name__ == "__main__":
    interface = Interface()
    interface.main()
