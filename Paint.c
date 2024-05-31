// gcc paint.c -lGL -lglut -lGLU -o paint && ./paint
#include <GL/glut.h> // inclui a biblioteca do GLUT

void myInit(void); // inicialização do OpenGL
void limpa(void); // desenho da cena gráfica

void handle_KeyboardFunc(GLubyte key, GLint x, GLint y);
void handle_motion(int x, int y);
void create_menu();
void handle_menu(int op);
void handle_submenu1(int op);
void handle_submenu2(int op);
void handle_submenu3(int op);
void handle_submenu4(int op);


int main(int argc, char** argv){
    glutInit(&argc, argv); // Inicializa o GLUT e processa qualquer parâmetro passado pela linha de comandos. Deve ser chamada antes de qualquer outra rotina GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Especifica como o vídeo será utilizado, no caso será alocado um buffer e o sistema de cor será RGB.
    
    glutInitWindowSize (640, 480); // Especifica as dimensões da janela em pixels.
    glutInitWindowPosition (100, 100); // Especifica a coordenada superior esquerda da janela. Define a localização da janela dentro da tela
    glutCreateWindow ("Paint"); // Cria a janela e devolve um identificador único para a janela. Até que o comando glutMainLoop seja chamado, a janela não será mostrada.
    
    
    myInit(); // Rotina que implementa as configurações iniciais do programa.
    //glutDisplayFunc(); // Chamada para a função de desenho. Toda vez que o GLUT determinar que a janela tem de ser desenhada, ele chamará a função aqui determinada.
    glutMotionFunc(handle_motion);
    glutKeyboardFunc(handle_KeyboardFunc);
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
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    limpa();
}
void limpa(void){
    glClear(GL_COLOR_BUFFER_BIT); // limpa a janela
    glFlush();
}

void handle_KeyboardFunc(GLubyte key, GLint x, GLint y){
    if (key == 'q' || key == 'Q'){
        exit(0);
    }
    if (key == 'd' || key == 'D'){
        limpa();
    }
}

void handle_motion(int x, int y){
    glBegin(GL_POINTS);
    glVertex2i(x, 480-y);
    glEnd();
    glFlush();
}

void create_menu(){
    GLint menu,submenu1,submenu2,submenu3;
    submenu1 = glutCreateMenu(handle_submenu1);
    glutAddMenuEntry("fino",0);
    glutAddMenuEntry("medio",1);
    glutAddMenuEntry("grosso",2);
    glutAddMenuEntry("muito grosso",3);
    glutAddMenuEntry("ABSURDAMENTE GROSSO",4);

    submenu2 = glutCreateMenu(handle_submenu2);
    glutAddMenuEntry("azul",0);
    glutAddMenuEntry("verde",1);
    glutAddMenuEntry("vermelho",2);    
    glutAddMenuEntry("preto",3);

    submenu3 = glutCreateMenu(handle_submenu3);
    glutAddMenuEntry("borracha",0);
    glutAddMenuEntry("apagar tela",1);

    menu = glutCreateMenu(handle_menu);
    glutAddSubMenu("espessura",submenu1);
    glutAddSubMenu("cor",submenu2);
    glutAddSubMenu("ferramentas",submenu3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void handle_menu(int op){
    
}

void handle_submenu1(int op){
    switch(op){
        case 0:
            glPointSize(1.0);
            break;
        case 1:
            glPointSize(4.0);
            break;
        case 2:
            glPointSize(8.0);
            break;
        case 3: 
            glPointSize(14.0);
            break;
        case 4:
            glPointSize(30.0);
            break;
    }
    glutPostRedisplay();
}

void handle_submenu2(int op){
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

void handle_submenu3(int op){
    switch(op){
        case 0:
            glColor3f(1.0, 1.0, 1.0);
            break;
        case 1:
            limpa();
            break;
    }
    glutPostRedisplay();
}
