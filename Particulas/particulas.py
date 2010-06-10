from sys         import argv
from OpenGL.GL   import *
from OpenGL.GLUT import *
from OpenGL.GLU  import *

class Particula:
    def __init__(self, _posicao, _velocidade, _forca, _massa):
        self.velocidade = _velocidade
        self.forca      = _forca
        self.posicao    = _posicao
        self.massa      = _massa
        
        
class ParSys:
    def __init__(self, arquivo):
        self.particulas = []
        self.carregarArquivo(arquivo)
        
    def carregarArquivo(self, _arquivo):
        valoresPosicao  = []
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
    
    def displayParticulas(self):
        glBegin(GL_POINTS)
        for particula in self.particulas:
            glVertex3f(particula.posicao[0], particula.posicao[1], particula.posicao[2])
        glEnd()
        glutSwapBuffers()

class Interface:
    def __init__(self):
        self.particulas = ParSys("dadosParticulas.txt")

    def init(self):
        glClearColor(0.0, 0.0, 0.0, 1.0)
        glMatrixMode(GL_PROJECTION)
        glEnable(GL_DEPTH_TEST) 
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        glOrtho(-100.0,   
                 100.0,  
                -100.0, 
                 100.0,
                 1.0,    #znear
                 200.0)  #zfar
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        gluLookAt(150, 150, 150, 0, 0, 0, 0, 50, 0);


    def display(self):
        glClear(GL_COLOR_BUFFER_BIT)
        glColor3f(1.0, 1.0, 1.0)

        self.particulas.displayParticulas()

        glutSwapBuffers()
                    
    def main(self):
        glutInit(argv)
        
        #Para resolver problema de falha de segmentacao - criar uma janela gambiarra
        glutCreateWindow("Gambiarra")
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
        glutInitWindowSize(500, 500)
        glutCreateWindow("Malhas 3D")
        self.init()
        glutDisplayFunc(self.display)
        
        glutMainLoop()


if __name__ == "__main__":
    interface = Interface()
    interface.main()
