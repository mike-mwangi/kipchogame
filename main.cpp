#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include <iostream>
using namespace std;

//Initialization
void myInit (void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.5f, 1.0f, 0.5f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 902.0, 0.0, 684.0);
}

//Sky
void Sky()
{
    glPushMatrix(); //Pushes the current matrix onto a stack
    glColor3ub(135, 206, 250); //Takes unsigned byte parameters with a range from 0 to 255
    glBegin(GL_QUADS);
    glVertex2i(0,684); //2i to mean it takes 2 values that are integers
    glVertex2i(902,684);
    glVertex2i(902,0);
    glVertex2i(0,0);
    glEnd();
    glPopMatrix(); //Reset the transformations so that they don't affect other objects.

    glutPostRedisplay(); //Sets a flag so that on the next iteration of the mainloop, your registered display() function is called
}

//Used to draw any circle needed
void drawCircle(GLfloat x, GLfloat y, GLfloat radius)
{
    int i;
    int triangleAmount = 50; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * 3.1416;

    //glColor3ub(23,60,43);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x, y); // center of circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2d(
                x + (radius * cos(i *  twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

//Sun
void Sun()
{
    glColor3ub(253, 184, 19);
    drawCircle(750.0f,620.0f,40.0f);
    glutPostRedisplay();
}

//3 clouds made from merging 4 circles for each cloud
void Cloud()
{
    glPushMatrix();
    glTranslatef(0,0,0);
    glColor3ub(230, 234, 237);
    drawCircle(594.0f,586.0f,20.0f);
    drawCircle(572.0f,595.0f,28.0f);
    drawCircle(539.0f,595.0f,35.0f);
    drawCircle(513.0f,575.0f,20.0f);
    glPopMatrix();

    glPushMatrix();
    drawCircle(393.0f,577.0f,20.0f);
    drawCircle(370.0f,585.0f,28.0f);
    drawCircle(339.0f,583.0f,35.0f);
    drawCircle(311.0f,565.0f,20.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,0);
    drawCircle(193.0f,607.0f,20.0f);
    drawCircle(170.0f,615.0f,28.0f);
    drawCircle(139.0f,613.0f,35.0f);
    drawCircle(111.0f,595.0f,20.0f);
    glPopMatrix();

    glutPostRedisplay();
}

//Road in which the character moves on
void Road()
{
    glPushMatrix();
    glColor3ub(0,0,0);
    glBegin(GL_QUADS);
    glVertex2i(0,180);
    glVertex2i(902,180);
    glVertex2i(902,0);
    glVertex2i(0,0);
    glEnd();
    glPopMatrix();


}

void GrassBelowRoad()
{
    glPushMatrix();
    glColor3ub(100, 171, 55);
    glBegin(GL_QUADS);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(902.0,0.0,0.0);
    glVertex3f(902.0,70.0,0.0);
    glVertex3f(0.0,70.0,0.0);
    glEnd();
    glPopMatrix();
}

void GrassAboveRoad()
{
    glPushMatrix();
    glColor3ub(100,171,55);
    //glColor3ub(100,171,55);
    glBegin(GL_QUADS);
    glVertex3f(0.0,180.0,0.0);
    glVertex3f(902.0,180.0,0.0);
    glVertex3f(902.0,254.0,0.0);
    glVertex3f(0.0,254.0,0.0);
    glEnd();
    glPopMatrix();
}


void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    Sky();
    Sun();
    Cloud();
    Road();
//    GrassAboveRoad();
//    GrassBelowRoad();

    glFlush ();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (902,684);
    glutInitWindowPosition (250, 30);
    glutCreateWindow ("Kipchogame");
    glutDisplayFunc(myDisplay);
//    glutKeyboardFunc(keyboard);
//    glutMouseFunc(mouse);
    myInit ();
    glutMainLoop();
}
