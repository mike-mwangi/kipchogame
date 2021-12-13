#include <gl/glut.h>
#include<math.h>

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
void eyeright()
{
    //function for the right eye
    glPushMatrix();
    glTranslatef(.17, 1.1, .75);     //Specify the coordinates for the right eye
    glRotatef(-45, 0, 0, 1);
    glScalef(.9, .7, .7);            //Specify the size of the right eye
    glColor3f(1.0, 1.0, 1.0);       //Specify the color of the eye
    gluSphere(gluNewQuadric(), .3, 100, 100);
    glPopMatrix();
}
void eyeleft()
{
    glPushMatrix();
    glTranslatef(-.17, 1.1, .75);     //Specify the position for the left eye
    glRotatef(45, 0, 0, 1);
    glScalef(.9, .7, .7);
    glColor3f(1.0, 1.0, 1.0);
    gluSphere(gluNewQuadric(), .3, 100, 100);
    glPopMatrix();
}

void legleft()
{
    glPushMatrix();
    glTranslatef(.3, -.5, 0);     //Specify the position for the left leg
    glRotatef(-90.0, 1, 0, 0);
    glScalef(.8, .8, .8);
    gluCylinder(gluNewQuadric(), .5, .5, .5, 30, 6);
    glPopMatrix();
}

void legright()
{
    glPushMatrix();
    glTranslatef(-.3, -.5, 0);     //Specify the position for the right leg
    glRotatef(-90.0, 1, 0, 0);
    glScalef(.8, .8, .8);
    gluCylinder(gluNewQuadric(), .5, .5, .5, 30, 6);
    glPopMatrix();
}

void armleft()
{
    glPushMatrix();
    glTranslatef(-.82, 0, .1);     //Specify the position for the left arm
    glRotatef(90, 0, 1, 0);
    glRotatef(-50, 1, 0, 0);
    gluCylinder(gluNewQuadric(), .15, .15, .48, 30, 6);
    glPopMatrix();
}

void armright()
{
    glPushMatrix();
    glTranslatef(.82, 0, .1);      //Specify the position for the right arm
    glRotatef(90, 0, 1, 0);
    glRotatef(-130, 1, 0, 0);
    gluCylinder(gluNewQuadric(), .15, .15, .48, 30, 6);
    glPopMatrix();
}

void handleft()
{
    glPushMatrix();
    glTranslatef(.82, 0, .1);     //Specify the position for the left hand
    glScalef(.4, .3, .3);
    gluSphere(gluNewQuadric(), .4, 100, 100);
    glPopMatrix();
}
void handright()
{
    glPushMatrix();
    glTranslatef(-.82, 0, .1);    //Specify the position for the right hand
    glScalef(.4, .3, .3);
    gluSphere(gluNewQuadric(), .4, 100, 100);
    glPopMatrix();
}

void mouth()
{
    glPushMatrix();
    glTranslatef(0, .78, .74);
    glScalef(.4, .4, .1);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(gluNewQuadric(), .4, 100, 100);
    glPopMatrix();
}

void teeth()
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-.08, .72, .76);
    glTranslatef(.055, 0, .005);
    glutSolidCube(.035);
    glTranslatef(.055, 0, 0);
    glutSolidCube(.035);
    glPopMatrix();
}
void eyebrowleft()
{
    glPushMatrix();
    glTranslatef(-.3, 1.5, .97);;
    glRotatef(90, 0, 1, 0);
    glRotatef(45, 1, 0, 0);
    glColor3f(0.0, 0.0, 0.0);
    gluCylinder(gluNewQuadric(), .05, .01, .3, 4, 6);
    glPopMatrix();
}

void eyebrowright()
{
    glPushMatrix();
    glTranslatef(.3, 1.5, .97);
    glRotatef(270, 0, 1, 0);
    glRotatef(45, 1, 0, 0);
    gluCylinder(gluNewQuadric(), .05, .01, .3, 4, 6);
    glPopMatrix();
}

void neckring()
{
    glPushMatrix();
    glTranslatef(0, .5, 0);
    glScalef(.59, .59, .59);
    glRotatef(90.0, 1, 0, 0);
    glutSolidTorus(.1, 1.0, 20, 20);
    glPopMatrix();
}


void head()
{
    glPushMatrix();
    glTranslatef(0, 1.2, 0);
    glScalef(.9, .9, .9);
    glColor3f(1.0, 0.8, 0.6);
    gluSphere(gluNewQuadric(), 1, 100, 100);
    glPopMatrix();
}

void maintopball()
{
    glPushMatrix();
    glTranslatef(0, 2.2, 0);
    glScalef(.9, .9, .9);
    gluSphere(gluNewQuadric(), .18, 100, 100);
    glPopMatrix();
}

void hatring()
{
    glPushMatrix();
    glTranslatef(0, 1.4, 0);
    glScalef(.84, .84, .84);
    glRotatef(90.0, 1, 0, 0);
    glutSolidTorus(.1, 1.0, 20, 20);
    glPopMatrix();
}

void footleft()
{
    glPushMatrix();
    glTranslatef(-.3, -.5, 0);
    glScalef(1.5, .3, 1.5);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(gluNewQuadric(), .3, 100, 100);
    glPopMatrix();
}

void footright()
{
    glPushMatrix();
    glTranslatef(.3, -.5, 0);
    glScalef(1.5, .3, 1.5);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(gluNewQuadric(), .3, 100, 100);
    glPopMatrix();
}

void bellyCoatbottom()
{
    glPushMatrix();
    glTranslatef(0, -.2, 0);
    glScalef(1, .7, 1);
    glRotatef(90.0, 1, 0, 0);
    gluDisk(gluNewQuadric(), 0, .8, 30, 30);
    glPopMatrix();
}

void BellyCoat()
{
    glPushMatrix();
    glTranslatef(0, .5, 0);
    glScalef(1, .7, 1);
    glRotatef(90.0, 1, 0, 0);
    gluCylinder(gluNewQuadric(), .6, .8, 1, 100, 100);
    glPopMatrix();
}

void pupilleft()
{
    glPushMatrix();
    glTranslatef(-.17, 1.1, .88);
    glScalef(.9, .9, .9);
    gluSphere(gluNewQuadric(), .1, 100, 100);
    glPopMatrix();
}

void pupilright()
{
    glPushMatrix();
    glTranslatef(.17, 1.1, .88);
    glScalef(.9, .9, .9);
    gluSphere(gluNewQuadric(), .1, 100, 100);
    glPopMatrix();
}

void topbutton()
{
    glPushMatrix();
    glTranslatef(-.1, .4, .85);
    glScalef(1.9, 1.9, 1.9);
    gluSphere(gluNewQuadric(), .04, 100, 100);
    glPopMatrix();
}
void middlebutton()
{
    glPushMatrix();
    glTranslatef(-.1, .15, .98);
    glScalef(1.9, 1.9, 1.9);
    gluSphere(gluNewQuadric(), .04, 100, 100);
    glPopMatrix();
}
void bottombutton()
{
    glPushMatrix();
    glTranslatef(-.1, -.1, .92);
    glScalef(1.9, 1.9, 1.9);
    glColor3f(0.0, 0.0, 0.0);
    gluSphere(gluNewQuadric(), .04, 100, 100);
    glPopMatrix();
}

//Sky
void Sky()
{
    glPushMatrix(); //Pushes the current matrix onto a stack
    glColor3ub(135, 206, 250); //Takes unsigned byte parameters with a range from 0 to 255
    glBegin(GL_QUADS);
    glVertex2i(0, 684); //2i to mean it takes 2 values that are integers
    glVertex2i(902, 684);
    glVertex2i(902, 0);
    glVertex2i(0, 0);
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
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2d(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

//Sun
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

//Road in which the character moves on
void Road()
{
    glPushMatrix();
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(0, 180);
    glVertex2i(902, 180);
    glVertex2i(902, 0);
    glVertex2i(0, 0);
    glEnd();
    glPopMatrix();


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

void GrassAboveRoad()
{
    glPushMatrix();
    glColor3ub(100, 171, 55);
    //glColor3ub(100,171,55);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 180.0, 0.0);
    glVertex3f(902.0, 180.0, 0.0);
    glVertex3f(902.0, 254.0, 0.0);
    glVertex3f(0.0, 254.0, 0.0);
    glEnd();
    glPopMatrix();
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 902.0, 0.0, 684.0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //draw 2D image
    Sky();
    Sun();
    Cloud();
    Road();
    GrassAboveRoad();
    GrassBelowRoad();

    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(60, w / h, 1.0, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //draw 3D objects
    eyeright();
    eyeleft();
    eyebrowleft();
    eyebrowright();
    glColor3f(1.0, 1.0, 1.0);
    neckring();
    glColor3ub(50, 40, 60);
    legright();
    legleft();
    glColor3ub(0, 0, 128);
    armleft();
    armright();
    BellyCoat();
    bellyCoatbottom();
    glColor3ub(255, 222, 173);
    handleft();
    handright();
    mouth();
    teeth();
    glColor3ub(255, 222, 173);
    head();
    glColor3ub(234, 221, 202);
    footleft();
    footright();
    topbutton();
    middlebutton();
    bottombutton();
    pupilleft();
    pupilright();
    glutSwapBuffers();
    /*
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Sky();
    Sun();
    Cloud();
    Road();
    GrassAboveRoad();
    GrassBelowRoad();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(60, w / h, 1.0, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    eyeright();
    eyeleft();
    eyebrowleft();
    eyebrowright();
    glColor3f(0.0, 1.0, 0.0);
    neckring();
    glColor3ub(50, 40, 60);
    legright();
    legleft();
    glColor3ub(255, 90, 0);
    armleft();
    armright();
    BellyCoat();
    bellyCoatbottom();
    glColor3ub(0, 185, 0);
    handleft();
    handright();
    mouth();
    teeth();
    glColor3ub(255, 222, 173);
    head();
    glColor3f(0.0, 0.0, 0.0);
    footleft();
    footright();
    topbutton();
    middlebutton();
    bottombutton();
    pupilleft();
    pupilright();

    glutSwapBuffers();
    */
}

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.5f, 1.0f, 0.5f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 902.0, 0.0, 684.0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(902, 684);
    glutInitWindowPosition(250, 30);
    glutCreateWindow("GLUT");
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glEnable(GL_DEPTH_TEST);
    myInit();
    glutMainLoop();
    return 0;
}