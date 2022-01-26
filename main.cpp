#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;


float ver[5][3] =
{
    {-1.0,-1.0,1.0},//the base 0,0 0
    //{0.0,1.0,0.0},//the base 0,1
    {0.0,1.0,0.0},// top 1,1 1
    {1.0,-1.0,1.0},//t 2
      {-1.0,-1.0,-1.0},// 3 the base
   // {-1.0,1.0,-1.0},
   // {1.0,1.0,-1.0},
    {1.0,-1.0,-1.0},//4
};

GLfloat color[8][3] =
{
    {0.0,0.0,0.0},
    {1.0,0.0,0.0},
    {1.0,1.0,0.0},
    {0.0,1.0,0.0},
    {0.0,0.0,1.0},

};

void quad(int a, int b, int c, int d)
{
    glBegin(GL_QUADS);
    glColor3fv(color[a]);
    glVertex3fv(ver[a]);

    glColor3fv(color[b]);
    glVertex3fv(ver[b]);

    glColor3fv(color[c]);
    glVertex3fv(ver[c]);

    glColor3fv(color[d]);
    glVertex3fv(ver[d]);
    glEnd();
}

void colorcube()
{
    // quad(0, 3, 2, 1);
    quad(0, 2, 3, 4);
    //quad(2, 3, 7, 6);
    quad(0, 2, 1, 1);
    //quad(1, 2, 6, 5);
  //  quad(4, 5, 6, 7);
    quad(0, 3, 1, 1);

    quad(2, 3, 1, 1);
    quad(2, 4, 1, 1);
}

double rotate_y = 0;
double rotate_x = 0;
void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    glutPostRedisplay();
}

//Game Speed
int FPS = 50;
//Game Track
int start = 0;
int gv = 0;
int level = 0;

//Track Score
int score = 0;


//For Card Left / RIGHT
int lrIndex = 0;

//Car Coming
int lrIndex1 = 0;
int lrIndex2 = 0;
int lrIndex3 = 0;

//For Display TEXT
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;

char s[30];
void renderBitmapString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
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
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2d(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}
//sun
void Sun()
{
    glColor3ub(253, 184, 19);
    drawCircle(750.0f, 620.0f, 40.0f);
    glutPostRedisplay();
}

//3 clouds made from merging 4 circles for each cloud
void Cloud()
{
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glColor3ub(230, 234, 237);
    drawCircle(594.0f, 586.0f, 20.0f);
    drawCircle(572.0f, 595.0f, 28.0f);
    drawCircle(539.0f, 595.0f, 35.0f);
    drawCircle(513.0f, 575.0f, 20.0f);
    glPopMatrix();

    glPushMatrix();
    drawCircle(393.0f, 577.0f, 20.0f);
    drawCircle(370.0f, 585.0f, 28.0f);
    drawCircle(339.0f, 583.0f, 35.0f);
    drawCircle(311.0f, 565.0f, 20.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 0);
    drawCircle(193.0f, 607.0f, 20.0f);
    drawCircle(170.0f, 615.0f, 28.0f);
    drawCircle(139.0f, 613.0f, 35.0f);
    drawCircle(111.0f, 595.0f, 20.0f);
    glPopMatrix();

    glutPostRedisplay();
}



void GrassBelowRoad()
{
    glPushMatrix();
    glColor3ub(100, 171, 55);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(902.0, 0.0, 0.0);
    glVertex3f(902.0, 70.0, 0.0);
    glVertex3f(0.0, 70.0, 0.0);
    glEnd();
    glPopMatrix();
}



void startGame() {
    //Sky
    glPushMatrix(); //Pushes the current matrix onto a stack
    glColor3ub(135, 206, 250); //Takes unsigned byte parameters with a range from 0 to 255
    glBegin(GL_QUADS);
    glVertex2i(0, 684); //2i to mean it takes 2 values that are integers
    glVertex2i(902, 684);
    glVertex2i(902, 0);
    glVertex2i(0, 0);
   
    //Obstacle1
    Sun();
    
    
    
    //Print Score
    char buffer[50];
    sprintf_s(buffer, "SCORE: %d", score);
    glColor3ub(0,0,0);
    renderBitmapString(0, 95, (void*)font3, buffer);
    //Coins count
    char buffer1[50];
    sprintf_s(buffer1, "COINS: %d", FPS);
    glColor3ub(0,0,0);
    renderBitmapString(90, 95, (void*)font3, buffer1);
    //Level Print
    if (score % 50 == 0) {
        int last = score / 50;
        if (last != level) {
            level = score / 50;
            FPS = FPS + 2;

        }
    }
    char level_buffer[50];
    sprintf_s(level_buffer, "LEVEL: %d", level);
    glColor3ub(0,0,0);
    renderBitmapString(90,90, (void*)font3, level_buffer);

    

}

void flashScreen() {

    //Flash screen - Sky
    glPushMatrix();
    glColor3ub(135, 206, 250);
    glBegin(GL_QUADS);
    glVertex2i(0, 684); //2i to mean it takes 2 values that are integers
    glVertex2i(902, 684);
    glVertex2i(902, 0);
    glVertex2i(0, 0);
    glEnd();


    //Instructions on controls
    glColor3ub(100, 171, 55);
    glBegin(GL_POLYGON);
    glVertex2f(28, 50);
    glVertex2f(78, 50);
    glVertex2f(78, 30);
    glVertex2f(28, 30);
    glEnd();


    //Text display in the flash screen after hitting an obstacle
    if (gv == 1) {
        glColor3f(1.000, 0.000, 0.000);
        renderBitmapString(35, 70, (void*)font1, "GAME OVER!");
        glColor3f(1.000, 0.000, 0.000);
        char buffer2[50];
        sprintf_s(buffer2, "Score: %d", score);
        renderBitmapString(33, 66, (void*)font1, buffer2);
    }

    //Title
    glColor3ub(0, 0, 0);
    renderBitmapString(45, 55, (void*)font1, "KIPCHOGAME");

    //controls
    glColor3ub(0, 0, 0);
    renderBitmapString(30, 47, (void*)font2, "Press SPACE to START");
    renderBitmapString(30, 44, (void*)font2, "Press ESC to Exit");

    
    glColor3ub(255, 255, 255);
    renderBitmapString(30, 41, (void*)font3, "Press UP to increase Speed");
    renderBitmapString(30, 38, (void*)font3, "Press DOWN to decrease Speed");
    renderBitmapString(30, 35, (void*)font3, "Press RIGHT to turn Right");
    renderBitmapString(30, 32, (void*)font3, "Press LEFT to turn Left");

}



void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (start == 1) {
        glClearColor(0.000, 0.392, 0.000, 1);
        startGame();
    }

    else {
        flashScreen();

    }
    glFlush();
    glutSwapBuffers();
}



void spe_key(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_DOWN:
        if (FPS > (50 + (level * 2)))
            FPS = FPS - 2;
        break;
    case GLUT_KEY_UP:
        FPS = FPS + 2;
        break;

    case GLUT_KEY_LEFT:
        if (lrIndex >= 0) {
            lrIndex = lrIndex - (FPS / 10);
            if (lrIndex < 0) {
                lrIndex = -1;
            }
        }
        break;


    case GLUT_KEY_RIGHT:
        if (lrIndex <= 44) {
            lrIndex = lrIndex + (FPS / 10);
            if (lrIndex > 44) {
                lrIndex = 45;
            }
        }
        break;

    default:
        break;
    }

}

void processKeys(unsigned char key, int x, int y) {

    switch (key)
    {
    case ' ':
        if (start == 0) {
            start = 1;
            gv = 0;
            FPS = 50;
            lrIndex = 0;
            lrIndex1 = 0;
            lrIndex2 = 0;
            lrIndex3 = 0;
            score = 0;
            level = 0;
        }
        break;

    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
}



int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(902, 684);
    glutInitWindowPosition(250, 30);
    glutCreateWindow("KIPCHOGAME");

    glutDisplayFunc(display);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(processKeys);

    glOrtho(0, 100, 0, 100, -1, 1);
    glClearColor(0.184, 0.310, 0.310, 1);

    glutTimerFunc(1000, timer, 0);
    glutMainLoop();

    return 0;
}
