// gcc atv_5.c -lGL -lglut -lGLU -o atv_5 && ./atv_5

#include <GL/glut.h>
#include <stdio.h>


void myInit(void);
void myDisplay(void);
void idleFunc();

GLfloat k = -50.0f;
GLfloat k_step = 1.0f;
GLfloat z = 1.0f;
GLfloat z_step = 0.1f;


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Transformacoes 2D");
    
    myInit();
    
    glutDisplayFunc(myDisplay);
    glutIdleFunc(idleFunc);

    glutMainLoop();
}


void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    //glColor3f(0.0f, 0.0f, 0.0f);
    //glPointSize(4.0);
    //glLineWidth(2.0);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //gluOrtho2D(0, 2.0, 0, 2.0); // esq / dir / baixo / cima
    //glPushMatrix();
}


void desenhaTriangulo(){
    glBegin(GL_TRIANGLES);
        glVertex2i(0, 50);
        glVertex2i(50, -50);
        glVertex2i(-50, -50);
    glEnd();
}

void desenhaTogepi() {
    glBegin(GL_POLYGON);
        glVertex2i(0, 50);
        glVertex2i(50, -50);
        glVertex2i(-50, -50);
    glEnd();

}

void desenhaMoldura(){
    glBegin(GL_LINE_LOOP);
        glVertex2f(-100, 100);
        glVertex2f(100, 100);
        glVertex2f(100, -100);
        glVertex2f(-100, -100);
    glEnd();
}

void idleFunc(){
    if(k > 50 || k < -50)
        k_step = -k_step;
    
    k += k_step;
    
    if(z > 5 || z < 0.1)
       z_step = -z_step;
    
    z += z_step;
    
    glutPostRedisplay();
       
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //desenha o fundo (limpa a janela)
    
    glMatrixMode(GL_PROJECTION);
    
    //1a janela glOrtho2D(xw_min, xw_max, yw_min, yw_max) = (-100, 100, -100, 10) | sist. de coordenadas do mundo (-oo,oo,-oo,oo) | sist. de coordenadas da janela (0,400, 0,600)
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glViewport(0, 300, 300, 300);
    glColor3f(1.0f, 0.0f, 0.0f);
    desenhaTriangulo();
   
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glViewport(300, 300, 300, 300);
    glTranslatef(k, 0, 0);
    glColor3f(0.0f, 1.0f, 0.0f);
    desenhaTriangulo();

    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glViewport(0, 0, 300, 300);
    glTranslatef(0, k, 0);
    glColor3f(0.0f, 0.0f, 1.0f);
    desenhaTriangulo();

    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glViewport(300, 0, 300, 300);
    glScalef(1,z, 0);
    glColor3f(1.0f, 0.0f, 1.0f);
    desenhaTriangulo();

    glLoadIdentity();
    gluOrtho2D(-200,200,-200,200);
    glViewport(0, 0, 600, 600);
    // GL_MODELVIEW utilizada para aplicar transformações geométricas às coorden dos objetos
    glMatrixMode(GL_MODELVIEW);


    glLoadIdentity ();

    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(-100,-100,0);
    desenhaMoldura();

    glLoadIdentity ();
    glTranslatef(100,-100,0);
    desenhaMoldura();

    glLoadIdentity ();
    glTranslatef(-100,100,0);
    desenhaMoldura();

    glLoadIdentity ();
    glTranslatef(100,100,0);
    desenhaMoldura ();

    glLoadIdentity();
    
    glutSwapBuffers();
    //glFlush();
}

