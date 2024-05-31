// gcc casa.c -lGL -lglut -lGLU -o casa && ./casa
#include <GL/glut.h> // inclui a biblioteca do GLUT

void myInit(void); // inicialização do OpenGL
void myDisplay(void); // desenho da cena gráfica

int main(int argc, char** argv){
    glutInit(&argc, argv); // Inicializa o GLUT e processa qualquer parâmetro passado pela linha de comandos. Deve ser chamada antes de qualquer outra rotina GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Especifica como o vídeo será utilizado, no caso será alocado um buffer e o sistema de cor será RGB.
    glutInitWindowSize (640, 480); // Especifica as dimensões da janela em pixels.
    glutInitWindowPosition (100, 100); // Especifica a coordenada superior esquerda da janela. Define a localização da janela dentro da tela
    glutCreateWindow ("Casa"); // Cria a janela e devolve um identificador único para a janela. Até que o comando glutMainLoop seja chamado, a janela não será mostrada.
    myInit(); // Rotina que implementa as configurações iniciais do programa.
    glutDisplayFunc(myDisplay); // Chamada para a função de desenho. Toda vez que o GLUT determinar que a janela tem de ser desenhada, ele chamará a função aqui determinada.
    glutMainLoop( ); // É o último comando que chamamos. Ele faz com que todas as janelas criadas sejam mostradas. Uma vez que entramos neste loop, só saímos quando o programa se encerra.
return 0; }

void myInit(void){
    glClearColor(0.8, 0.6, 1.0, 0.0); // Cor de fundo
    glPointSize(4.0); // Define o tamanho do ponto: 4 por 4 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // janela com resolução de 640 por 480
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT); // limpa a janela
    glColor3f(0.4, 0.0, 0.4);
    glBegin(GL_QUADS); // chaminé
    glVertex2i(250, 410); // desenha 4 pontos
    glVertex2i(275, 410);
    glVertex2i(275, 310);
    glVertex2i(250, 310);
    glEnd();
    glColor3f(0.6, 0.1, 0.6);
    glBegin(GL_TRIANGLES); // telhado
    glVertex2i(230, 310); // desenha 3 pontos
    glVertex2i(315, 395);
    glVertex2i(400, 310);
    glEnd();
    glColor3f(0.5, 0.0, 0.5);
    glBegin(GL_QUADS);  // casa
    glVertex2i(230, 310); // desenha 4 pontos
    glVertex2i(400, 310);
    glVertex2i(400, 170);
    glVertex2i(230, 170);
    glEnd();
    glColor3f(0.8, 0.4, 0.8);
    glBegin(GL_QUADS); // porta
    glVertex2i(275, 170); // desenha 4 pontos
    glVertex2i(320, 170);
    glVertex2i(320, 260);
    glVertex2i(275, 260);
    glEnd();
    glBegin(GL_QUADS); // janela
    glVertex2i(335, 225); // desenha 4 pontos
    glVertex2i(385, 225);
    glVertex2i(385, 275);
    glVertex2i(335, 275);
    glEnd();
    


    glFlush(); // Garante a execução de todas as rotinas de desenho. Sempre usar!
}