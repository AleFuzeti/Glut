// gcc atv_4.c -lGL -lglut -lGLU -o atv_4 && ./atv_4

#include <GL/glut.h>

GLfloat casaPosX = 0.0, casaPosY = 0.0;
GLfloat casaScaleX = 1.0, casaScaleY = 1.0;
GLfloat casaAngle = 0.0;

void myInit(void);
void myDisplay(void);
void handleKeypress(unsigned char key, int x, int y);
void handleSpecialKeypress(int key, int x, int y);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Casa Voadora?");
    myInit();
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(handleSpecialKeypress);
    glutMainLoop();
    return 0;
}

void myInit(void) {
    glClearColor(0.8, 0.6, 1.0, 0.0);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void myDisplay(void) { // casa que ja usei no outro programa
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(casaPosX, casaPosY, 0.0);  // Translada a casa
    glScalef(casaScaleX, casaScaleY, 1.0);  // Escala a casa
    glTranslatef(315.0, 240.0, 0.0);             // Translada para o centro da janela
    glRotatef(casaAngle, 0.0, 0.0, 1.0);        // Rotaciona a casa
    glTranslatef(-315.0, -240.0, 0.0);          // Translada de volta para a posição original
    
    // Dessa forma a casa é rotacionadano próprio eixo

    // Desenho da casa
    glColor3f(0.4, 0.0, 0.4);
    glBegin(GL_QUADS); // chaminé
    glVertex2i(250, 410);
    glVertex2i(275, 410);
    glVertex2i(275, 310);
    glVertex2i(250, 310);
    glEnd();
    glColor3f(0.6, 0.1, 0.6);
    glBegin(GL_TRIANGLES); // telhado
    glVertex2i(230, 310);
    glVertex2i(315, 395);
    glVertex2i(400, 310);
    glEnd();
    glColor3f(0.5, 0.0, 0.5);
    glBegin(GL_QUADS);  // casa
    glVertex2i(230, 310);
    glVertex2i(400, 310);
    glVertex2i(400, 170);
    glVertex2i(230, 170);
    glEnd();
    glColor3f(0.8, 0.4, 0.8);
    glBegin(GL_QUADS); // porta
    glVertex2i(275, 170);
    glVertex2i(320, 170);
    glVertex2i(320, 260);
    glVertex2i(275, 260);
    glEnd();
    glBegin(GL_QUADS); // janela
    glVertex2i(335, 225);
    glVertex2i(385, 225);
    glVertex2i(385, 275);
    glVertex2i(335, 275);
    glEnd();

    glPopMatrix();

    // Escreve no fundo
    glColor3f(0, 0, 0); // Cor do texto
    glRasterPos2i(10, 10); // Posição do texto
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '='); 
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ')'); 
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' '); 
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' '); 
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E'); 
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's'); 
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c'); 
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' '); 
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'f'); 
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e'); 
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c'); 
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'h'); 
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a'); 
    glFlush();
}

void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            casaScaleX += 0.1;
            casaScaleY += 0.1;
            break;
        case 'W':
            casaScaleX += 0.1;
            casaScaleY += 0.1;
            break;
        case 's':
            casaScaleX -= 0.1;
            casaScaleY -= 0.1;
            break;
        case 'S':
            casaScaleX -= 0.1;
            casaScaleY -= 0.1;
            break;
        case 'a':
            casaAngle += 10.0;
            break;
        case 'A':
            casaAngle += 10.0;
            break;
        case 'd':
            casaAngle -= 10.0;
            break;
        case 'D':
            casaAngle -= 10.0;
            break;
        case 27: // ESC
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void handleSpecialKeypress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            casaPosX -= 10.0;
            break;
        case GLUT_KEY_RIGHT:
            casaPosX += 10.0;
            break;
        case GLUT_KEY_UP:
            casaPosY += 10.0;
            break;
        case GLUT_KEY_DOWN:
            casaPosY -= 10.0;
            break;
    }
    glutPostRedisplay();
}
