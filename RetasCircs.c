// gcc atv_3.c -lm -lGL -lglut -lGLU -o atv_3 && ./atv_3
// uso de menu e submenus para teste de funções de desenho de retas e circunferências

#include <GL/glut.h> // inclui a biblioteca do GLUT
#include <math.h>
#include <stdio.h>

void myInit(void); // inicialização do OpenGL
void limpa(void); // desenho da cena gráfica

void create_menu();
void handle_menu(int op);
void handle_submenu1(int op);
void handle_submenu2(int op);
int point1_x, point1_y, point2_x, point2_y;
int points_selected = 0;

void DDA (int x1, int y1, int x2, int y2);
void bresenhamReta(int x1, int y1, int x2, int y2);
void bresenhamCirculo(int xc, int yc, int r);
void Carinha_feliz(int x, int y);
void putpixel(int x, int y);

int main(int argc, char** argv){
    glutInit(&argc, argv); // Inicializa o GLUT e processa qualquer parâmetro passado pela linha de comandos. Deve ser chamada antes de qualquer outra rotina GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Especifica como o vídeo será utilizado, no caso será alocado um buffer e o sistema de cor será RGB.
    
    glutInitWindowSize (640, 480); // Especifica as dimensões da janela em pixels.
    glutInitWindowPosition (350, 150); // Especifica a coordenada superior esquerda da janela. Define a localização da janela dentro da tela
    glutCreateWindow ("DDA"); // Cria a janela e devolve um identificador único para a janela. Até que o comando glutMainLoop seja chamado, a janela não será mostrada.
    
    
    myInit(); // Rotina que implementa as configurações iniciais do programa.
    //glutDisplayFunc(); // Chamada para a função de desenho. Toda vez que o GLUT determinar que a janela tem de ser desenhada, ele chamará a função aqui determinada.
    create_menu();

    glutMainLoop( ); // É o último comando que chamamos. Ele faz com que todas as janelas criadas sejam mostradas. Uma vez que entramos neste loop, só saímos quando o programa se encerra.
return 0; 
}

void myInit(void){
    glClearColor(1.0, 1.0, 1.0, 1.0); // Cor de fundo
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(4.0); // Define o tamanho do ponto: 4 por 4 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // janela com resolução de 640 por 480
    gluOrtho2D(-320.0, 320.0, 240.0, -240.0);
    limpa();
}

void limpa(void){
    glClear(GL_COLOR_BUFFER_BIT); // limpa a janela
    glFlush();
}


void create_menu(){
    GLint menu,submenu1,submenu2;
    submenu1 = glutCreateMenu(handle_submenu1);
    glutAddMenuEntry("azul",0);
    glutAddMenuEntry("verde",1);
    glutAddMenuEntry("vermelho",2);    
    glutAddMenuEntry("preto",3);

    submenu2 = glutCreateMenu(handle_submenu2);
    glutAddMenuEntry("apagar tela",0);
    glutAddMenuEntry("Teste DDA",1);
    glutAddMenuEntry("Teste Bresenham Retas",2);
    glutAddMenuEntry("Teste Bresenham Circunferencias",3);
    glutAddMenuEntry("=)",4);

    menu = glutCreateMenu(handle_menu);
    glutAddSubMenu("cor",submenu1);
    glutAddSubMenu("ferramentas",submenu2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void handle_menu(int op){
    
}

void handle_submenu1(int op){
    switch(op){
        case 0:
            glColor3f(0.0, 0.0, 1.0);
            break;
        case 1:
            glColor3f(0.0, 1.0, 0.0);
            break;
        case 2:
            glColor3f(1.0, 0.0, 0.0);
            break;
        case 3:
            glColor3f(0.0, 0.0, 0.0);
            break;
    }
    glutPostRedisplay();
}

void handle_submenu2(int op){
    switch(op){
        case 0:
            limpa();
            break;
        case 1:
            DDA(0, 0, 96, 96);
            DDA(0, 0, 96, -96);
            DDA(0, 0, -96, 96);
            DDA(0, 0, -96, -96);
            DDA(-96, 96, 96, 96);
            DDA(-96, -96, 96, -96);
            DDA(-96, 96, -96, -96);
            DDA(96, 96, 96, -96);
            break;
        case 2:
            bresenhamReta(100, 100, 200, 200);
            bresenhamReta(100, -100, 200,-200);
            bresenhamReta(-100, 100, -200, 200);
            bresenhamReta(-100, -100, -200, -200);
            bresenhamReta(-100, 100, -100, -100);
            bresenhamReta(100, 100, 100, -100);
            bresenhamReta(-100, 100, 100, 100);
            bresenhamReta(-100, -100, 100, -100);
            bresenhamReta(200,200,200,-200);
            bresenhamReta(-200,200,-200,-200);
            bresenhamReta(-200,200,200,200);
            bresenhamReta(-200,-200,200,-200);
            break;
        case 3:
            bresenhamCirculo(0, 0, 50);
            bresenhamCirculo(0, 0, 200);
            break;
        case 4:
            Carinha_feliz(230,230);
            Carinha_feliz(-260,230);
            Carinha_feliz(230,150);
            Carinha_feliz(-260,150);
            Carinha_feliz(230,70);
            Carinha_feliz(-260,70);
            Carinha_feliz(230,-10);
            Carinha_feliz(-260,-10);
            Carinha_feliz(230,-90);
            Carinha_feliz(-260,-90);
            Carinha_feliz(230,-170);
            Carinha_feliz(-260,-170);
            break;
    }
    glutPostRedisplay();
}

int Round(int num){
    return (num >= 0) ? (int)(num + 0.5) : (int)(num - 0.5);
}

void putpixel(int x, int y){
    glBegin(GL_POINTS);
    glVertex2i(x, -y);
    glEnd();
    glFlush();
}

void DDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;

    // Verifica se a inclinação da linha é menor ou igual a 45 graus
    if (abs(dx) >= abs(dy)) {
        steps = abs(dx);
    } else {
        steps = abs(dy);
    }

    float xinc = dx / (float) steps;
    float yinc = dy / (float) steps;
    float x = x1;
    float y = y1;

    for (int i = 0; i < steps; i++) {
        putpixel(Round(x), Round(y));
        x += xinc;
        y += yinc;
    }
}

void bresenhamReta(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (x1 != x2 || y1 != y2) {
        putpixel(x1, y1);
        int err2 = 2 * err;
        
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void bresenhamCirculo(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        putpixel(xc + x, yc + y);
        putpixel(xc - x, yc + y);
        putpixel(xc + x, yc - y);
        putpixel(xc - x, yc - y);
        putpixel(xc + y, yc + x);
        putpixel(xc - y, yc + x);
        putpixel(xc + y, yc - x);
        putpixel(xc - y, yc - x);

        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void Sorriso(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        putpixel(xc + x, yc - y);
        putpixel(xc - x, yc - y);
        putpixel(xc + y, yc - x);
        putpixel(xc - y, yc - x);

        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void Carinha_feliz(int x, int y) {
    bresenhamReta(x, y, x, y-30);
    bresenhamReta(x+30, y, x+30, y-30);
    Sorriso(x+15, y-35, 25);
}
