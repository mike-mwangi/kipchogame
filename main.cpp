#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <iostream>
#include <valarray>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <random>
#include <list>

using namespace std;
// cloud manipulation
float c1xp = 0.0, c1yp = 0.0, c1zp = 0.0;
float c2xp = 0.0, c2yp = 0.0, c2zp = 0.0;
float p1xp = 0.0, p1yp = 0.0, p1zp = 0.0;
float p1sxp = 0.0, p1syp = 0.0, p1szp = 0.0;
float x = 1.0;
float rxp = 0.0, ryp = 0.0, rzp = 0.0;
float r = 0.0;
float width = -940, width2 = 600, width3 = 2000;
//end of cloud manipulation
// jump manip
int long previousTime = 0;


/*float ver[5][3] =
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
*/

//Game Speed
int FPS = 50;
//Game Track
int start = 0;
int gameOverFlag = 0;


//Track Score
int score = 0;


//For Card Left / RIGHT
int upDownMovement = 0;

//For Display TEXT
const int font1 = (uintptr_t)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (uintptr_t)GLUT_BITMAP_HELVETICA_18;
const int font3 = (uintptr_t)GLUT_BITMAP_8_BY_13;
//cloud variables
float cdxp1 = 0.0;
float cdxp2 = 0.0;
float cdxp3 = 0.0;

struct coin {
public:
    float x;
    float y;
};
struct pit {
public:
    float x;
    float y;
};
struct Obstacle {
    float x;
};
vector<coin> coins;
pit ObstaclePit;
Obstacle obstacle;

void initRandoms() {
    for (int i = 0; i <= 3; i++) {
        random_device rand_dev;
        mt19937 generator(rand_dev());
        uniform_real_distribution<double> distrPositionX(110.0, 900.0);
        uniform_real_distribution<double> distrPositionY(180.0, 500.0);
        coin tempCoin;
        tempCoin.x = distrPositionX(generator);
        tempCoin.y = distrPositionY(generator);
        coins.push_back(tempCoin);
    }
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_real_distribution<double> distrPositionX(100, 900);
    ObstaclePit.x = distrPositionX(generator);
    obstacle.x = distrPositionX(generator);
    if (abs(ObstaclePit.x - obstacle.x)<100) {
        obstacle.x += 100;
    }

}
void updateCoins(int value) {
    for (auto & coin : coins) {
        coin.x = coin.x -1.0;
      
    }
    ObstaclePit.x = ObstaclePit.x - 1;
    obstacle.x -= 1;
    glutTimerFunc(10000, updateCoins, 0);
}
void reDrawCoin(int value) {
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_real_distribution<double> distrPositionX(20,70);
    uniform_real_distribution<double> distrPositionY(180.0, 500.0);
    coin tempCoin;
    tempCoin.x = 900.0+ distrPositionX(generator);
    tempCoin.y = distrPositionY(generator);
    coins[value] = tempCoin;
    

}
void reDrawObstaclePit() {
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_real_distribution<double> distrPositionX(100, 600);
    ObstaclePit.x =900+ distrPositionX(generator);

}
void reDrawObstacle() {
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_real_distribution<double> distrPositionX(100, 600);
    obstacle.x = 900 + distrPositionX(generator);

};
void checkCoinPositions() {
    //coin current = coins.at(currentCoin);
    int i = 0;
    for (auto& current: coins) {
        if (current.x <= 10) {
            reDrawCoin(i);
           
        }
        i++;
    }
    if (ObstaclePit.x <= 10) {
        reDrawObstaclePit();
    }
    if (obstacle.x <= 10) {
        reDrawObstacle();
    }
}
void checkIfPlayerDied() {
    printf(" obstacle pit %f", ObstaclePit.x);
    if (upDownMovement==0 && ObstaclePit.x <103 && ObstaclePit.x>10) {
        std::cout << "fell into a ditch";
       gameOverFlag = 1;
        start = 0;

    }
    if (upDownMovement == 0 && obstacle.x < 103 && obstacle.x>10) {
        std::cout << "hit by a wall";
       // gv = 1;
    }
}





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
//score displayer
void displayScore() {


    //Print Score
    char buffer[50];
    sprintf_s(buffer, "SCORE: %d", score);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(20, 70, (void*)font3, buffer);

    //Coins count
    char buffer1[50];
    sprintf_s(buffer1, "COINS: %d", FPS);
    glColor3f(0, 1.0, 0);
    renderBitmapString(20, 55, (void*)font3, buffer1);
    //Level Print
   

}

//Sun
void Sun()
{
    glColor3ub(253, 184, 19);
    drawCircle(750.0f, 620.0f, 40.0f);
    glutPostRedisplay();
}

//Road
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




//Clouds
void Cloud()
{

    glPushMatrix();
    glTranslatef(c1xp + 10, 0, 0);
    glColor3ub(230, 234, 237);
    drawCircle(594.0f, 586.0f, 20.0f);
    drawCircle(572.0f, 595.0f, 28.0f);
    drawCircle(539.0f, 595.0f, 35.0f);
    drawCircle(513.0f, 575.0f, 20.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(c1xp + 10, 0, 0);
    drawCircle(393.0f, 577.0f, 20.0f);
    drawCircle(370.0f, 585.0f, 28.0f);
    drawCircle(339.0f, 583.0f, 35.0f);
    drawCircle(311.0f, 565.0f, 20.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(c1xp + 10, 0, 0);
    drawCircle(193.0f, 607.0f, 20.0f);
    drawCircle(170.0f, 615.0f, 28.0f);
    drawCircle(139.0f, 613.0f, 35.0f);
    drawCircle(111.0f, 595.0f, 20.0f);
    glPopMatrix();

    glutPostRedisplay();


}

//Rain
void Rain()
{
    glPushMatrix();
    glTranslatef(c1xp + 1000, 180, 0);
    cout << "Rain speed: " << c1xp * 1 << endl;
    glColor3ub(103, 155, 176);
    for (int j = 0; j < 20 * 160; j += 20)
    {
        for (int i = 0; i < 20 * 160; i += 20)
        {
            glBegin(GL_LINES);
            glVertex2f(0 + i + j, 0 + i);
            glVertex2f(-5.5 + i + j, 10 + i);
            glEnd();

            glBegin(GL_LINES);
            glVertex2f(0 + i - j, 0 + i);
            glVertex2f(-5.5 + i - j, 10 + i);
            glEnd();
        }
    }
    glPopMatrix();
}

//Make the clouds and rain move
//Increases in speed as game continues
void CloudAndRainMove(int value)
{
    width += 1.0;
    width2 -= 1.0;
    //width3-=0.01;

    if (width < 10093)
    {
        cdxp1 += 0.09;
        cdxp2 += 0.1;
        cdxp3 += 0.0001; //CloudsT variable

        c1xp += 0.07;
        if (width > 10091)
        {
            width = -940;
            c1xp = 0.0;
        }
        if (width == 1295)
        {
            cdxp1 = 0.0;
        }
      //  cout << "Width: " << width << endl;
    }
    if (width2 > -1614)
    {
        c2xp -= 0.5;
        p1xp -= 0.001;
        p1yp += 0.6;
        if (width2 == -1613)
        {
            width2 = 600;
            c2xp = 0;

            p1xp = 0;
            p1yp = 0;
            p1sxp = 0;
            p1syp = 0;
            x = 1.0;
            glutPostRedisplay();
        }
        if (width2 < 1200)
        {
            p1sxp += 0.001;
            p1syp += 0.001;
            glutPostRedisplay();
        }
      //  cout << "Width2: " << p1xp << endl;
    }

    glutTimerFunc(0, CloudAndRainMove, 25);

}

//Flash screen
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
    if (gameOverFlag == 1) {
        glColor3f(1.000, 0.000, 0.000);
        renderBitmapString(35, 70, (void*)font1, "GAME OVER!");
        glColor3f(1.000, 0.000, 0.000);
        char buffer2[50];
        //sprintf_s(buffer2, "Score: %d", score);
        renderBitmapString(33, 66, (void*)font1, buffer2);
    }

    //Title
    glColor3ub(0, 0, 0);
    renderBitmapString(450, 300, (void*)font1, "KIPCHOGAME");

    //controls
    glColor3ub(0, 0, 0);
    renderBitmapString(30, 47, (void*)font2, "Press SPACE to START");
    renderBitmapString(30, 44, (void*)font2, "Press ESC to Exit");


    glColor3ub(255, 255, 255);
    renderBitmapString(30, 41, (void*)font3, "Press UP to increase Speed");
    renderBitmapString(30, 38, (void*)font3, "Press DOwN to decrease Speed");
    renderBitmapString(30, 35, (void*)font3, "Press RIGHT to turn Right");
    renderBitmapString(30, 32, (void*)font3, "Press LEFT to turn Left");

}




//Keystrokes to trigger certain processes. Eg: Use 'r' to turn rain and off.
// 'e' to exit application
// 'space' to start
void processKeys(unsigned char key, int x, int y) {

    switch (key)
    {
    case ' ':
        if (start == 0) {
            start = 1;
            gameOverFlag = 0;
            FPS = 50;
            upDownMovement = 0;
    
            score = 0;
            
        }
        break;

    case 'r':
        if (r == 0)
        {
            r = 1;
        }
        else
        {
            r = 0;
        }
        break;

    case 'e':
        exit(1);
        break;

    case 27:
        exit(0);
        break;

    default:
        break;
    }
}
void DrawfullCircle(float cx, float cy, float r, int num_segments) {

    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++) {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}
void Character() {
    //hair

    glTranslatef(10, 0, 0);
    glColor3ub(255, 140, 0);
    DrawfullCircle(19.0f, upDownMovement + 295.0f, 5.0f, 10);
    DrawfullCircle(17.0f, upDownMovement + 318.0f, 7.0f, 10);
    DrawfullCircle(15.0f, upDownMovement + 315.0f, 6.0f, 10);
    DrawfullCircle(14.0f, upDownMovement + 310.0f, 5.0f, 10);
    DrawfullCircle(23.0f, upDownMovement + 305.0f, 6.0f, 10);
    DrawfullCircle(20.0f, upDownMovement + 300.0f, 5.0f, 10);
    DrawfullCircle(23.0f, upDownMovement + 310.0f, 8.0f, 10);
    DrawfullCircle(20.0f, upDownMovement + 312.0f, 7.0f, 10);
    //head
    glColor3f(0.9, 0.7, 0.6);
    glBegin(GL_POLYGON);
    glVertex2f(50, upDownMovement + 255);
    glVertex2f(20, upDownMovement + 310);
    glVertex2f(120, upDownMovement + 280);
    glEnd();
    //eyes
    glColor3f(1.0, 1.0, 1.0);
    DrawfullCircle(75, upDownMovement + 290, 15, 20);
    glColor3f(0.0, 0.0, 0.0);
    DrawfullCircle(83, upDownMovement + 292, 6, 20);
    
    //shirt stripes
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(10, upDownMovement + 260);
    glVertex2f(105, upDownMovement + 260);
    glVertex2f(105, upDownMovement + 255);
    glVertex2f(10, upDownMovement + 255);
    glEnd();

    glColor3f(0.0f, 0.08f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(10, upDownMovement + 255);
    glVertex2f(105, upDownMovement + 255);
    glVertex2f(105, upDownMovement + 250);
    glVertex2f(10, upDownMovement + 250);
    glEnd();
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(10, upDownMovement + 250);
    glVertex2f(105, upDownMovement + 250);
    glVertex2f(105, upDownMovement + 245);
    glVertex2f(10, upDownMovement + 245);
    glEnd();
    glColor3f(0.0f, 0.08f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(10, upDownMovement + 245);
    glVertex2f(105, upDownMovement + 245);
    glVertex2f(105, upDownMovement + 240);
    glVertex2f(10, upDownMovement + 240);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(10, upDownMovement + 240);
    glVertex2f(105, upDownMovement + 240);
    glVertex2f(105, upDownMovement + 235);
    glVertex2f(10, upDownMovement + 235);
    glEnd();

    glColor3f(0.0f, 0.08f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(10, upDownMovement + 235);
    glVertex2f(105, upDownMovement + 235);
    glVertex2f(105, upDownMovement + 230);
    glVertex2f(10, upDownMovement + 230);
    glEnd();

    // left short
    glColor3f(0.07, 0.4, 0.7);
    glPushMatrix();
    /* if (fortyFive) {
         glRotatef(45.0, 0,0, 1);

     }
     else {
         glRotatef(-45.0, 0, 0, 1);
     }
     */
    glBegin(GL_POLYGON);
    glVertex2f(35, upDownMovement + 230);
    glVertex2f(50, upDownMovement + 230);
    glVertex2f(50, upDownMovement + 210);
    glVertex2f(35, upDownMovement + 210);
    glEnd();
    glPopMatrix();
    glColor3f(0.07, 0.4, 0.7);
    //right short
    glBegin(GL_POLYGON);
    glVertex2f(70, upDownMovement + 230);
    glVertex2f(85, upDownMovement + 230);
    glVertex2f(85, upDownMovement + 210);
    glVertex2f(70, upDownMovement + 210);
    glEnd();
    //left leg
    glColor3f(0.9, 0.7, 0.6);
    glBegin(GL_POLYGON);
    glVertex2f(35, upDownMovement + 210);
    glVertex2f(50, upDownMovement + 210);
    glVertex2f(50, upDownMovement + 190);
    glVertex2f(35, upDownMovement + 190);
    glEnd();
    //right leg

    glColor3f(0.9, 0.7, 0.6);

    glBegin(GL_POLYGON);
    glVertex2f(70, upDownMovement + 210);
    glVertex2f(85, upDownMovement + 210);
    glVertex2f(85, upDownMovement + 190);
    glVertex2f(70, upDownMovement + 190);
    glEnd();
    glColor3f(1, 1, 1);
    // left shoe
    glBegin(GL_POLYGON);
    glVertex2f(35, upDownMovement + 180);
    glVertex2f(50, upDownMovement + 180);
    glVertex2f(50, upDownMovement + 190);
    glVertex2f(35, upDownMovement + 190);
    glEnd();

    glColor3f(1, 1, 1);

    glBegin(GL_POLYGON);
    glVertex2f(70, upDownMovement + 180);
    glVertex2f(85, upDownMovement + 180);
    glVertex2f(85, upDownMovement + 190);
    glVertex2f(70, upDownMovement + 190);
    glEnd();
}
void obstaclePit() {


    glColor3ub(135, 206, 250);
    glBegin(GL_POLYGON);
    glVertex2f(ObstaclePit.x-90, 180);
    glVertex2f(ObstaclePit.x, 180);
    glVertex2f(ObstaclePit.x, 90);
    glVertex2f(ObstaclePit.x-90, 90);
    glEnd();

   /* for (auto const& obstaclePit : ) {
        glColor3ub(255, 255, 255);
        drawCircle(coin.x, coin.y, 18.0f);
        glColor3ub(253, 184, 19);
        drawCircle(coin.x, coin.y, 15.0f);
    }
    */
}

void obstacleDome() {
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(obstacle.x, 180);
    glVertex2f(obstacle.x+100, 180);
    glVertex2f(obstacle.x + 100, 260);
    glVertex2f(obstacle.x, 260);
    glEnd();

    //drawCircle(obstacle.x + 50, 250, 50);
}

void Coin() {
    //Outer circle
   /**/

    for (auto const& coin : coins) {
        glColor3ub(255, 255, 255);
        drawCircle(coin.x, coin.y, 18.0f);
        glColor3ub(253, 184, 19);
        drawCircle(coin.x, coin.y, 15.0f);
        }
   /*
   glColor3ub(255, 255, 255);
   drawCircle(500.0f, 200.0f, 18.0f);
    drawCircle(600.0f, 400.0f, 18.0f);
    drawCircle(860.0f, 200.0f, 18.0f);

    glColor3ub(253, 184, 19);
    drawCircle(500.0f, 200.0f, 15.0f);
    drawCircle(600.0f, 400.0f, 15.0f);
    drawCircle(860.0f, 200.0f, 15.0f);
    */
    glutPostRedisplay();
}

//Where the objects are displayed from
void display() {
    // jump logic
    int dif = glutGet(GLUT_ELAPSED_TIME) - previousTime;
    if (dif >= 1500) {
        upDownMovement = 0;
      //  std::cout << "changed";
    }

    glClear(GL_COLOR_BUFFER_BIT);


    if (start == 1) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluOrtho2D(0.0, 902.0, 0.0, 684.0);
        

        CloudAndRainMove(0);
        updateCoins(0);
        
        //draw 2D image        startGame();
        Sky();
        Sun();
        Road();
        Cloud();
        Character();
        obstaclePit();
        obstacleDome();
        Coin();
       checkCoinPositions();
       checkIfPlayerDied();
       displayScore();


        if (r == 1)
        {
            Rain();
        }

    }
    else {
        
        flashScreen();

    }
    glFlush();
    glutSwapBuffers();
}


void spe_key(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        FPS = FPS + 2;
        if (upDownMovement == 0) {
            upDownMovement += 50;
            previousTime = glutGet(GLUT_ELAPSED_TIME);
        }
        if (upDownMovement == 50 && previousTime != glutGet(GLUT_ELAPSED_TIME));
        {
            upDownMovement += 50;
        }
        break;
        /*
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
        */

    default:
        break;
    }

}
void randomPositioning() {
    for (auto & coin : coins){
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_real_distribution<float> distrPositionX(110, 900);
    uniform_real_distribution<double> distrPositionY(500, 180);

    coin.x= distrPositionX(generator);
    coin.y = distrPositionY(generator);
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

    initRandoms();

    glutDisplayFunc(display);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(processKeys);

    gluOrtho2D(0.0, 902.0, 0.0, 684.0);
    glClearColor(0.184, 0.310, 0.310, 1);

    glutTimerFunc(1000, timer, 0);
    glutMainLoop();

    return 0;
}

