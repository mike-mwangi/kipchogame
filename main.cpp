#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <cmath>
#include <stdio.h>
#include <list>
#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include "VectG.h"



using namespace std;

// Object structs- data structures for storing characteristics
// 1 : Wall, 2: Double Wall, 3 : Bouncing Ball
struct Wall
{
    VectG position;
    VectG color;
    VectG size;
};

struct DoubleWall
{
    int gap;
    int type; // 1 : Vertical, 2 : Horizontal
    VectG position1;
    VectG position2;
    VectG color;
    VectG size1;
    VectG size2;
};

struct BouncingBall
{
    VectG position;
    VectG color;
    VectG radius;
    float velocity;
    float velocityx;
};

// Non collision object - decoration - non collision object could be our rewards
struct NonCollision
{
    int type; // 1: cube, 2: pyramid, 3: sphere
    VectG rotation;
    float rotVelX;
    float rotVelY;
    float rotVelZ;
    VectG position;
    VectG color;
    VectG size;
};

// Game state flag
unsigned int gameState = 3;

// Time factor ????
const float timeFactor = 2000;
float frame = 0.0;

// Plane constants
const float PLANE_LENGTH = 900.0f;
const float PLANE_WIDTH = 10.0f;
float PLANE_YPOS = -2.0f;

// Player variables - we could put this in a struct and change it overtime - instead of box we introduce our character
const float BOX_SIZE = 1.5f;
float playerAngleY = 0.0f;
float playerAngleX = 0.0f;
VectG playerPos = VectG(0.0f, 10.0f, -20.0f);
VectG playerPrevPos = VectG(0.0f, 10.0f, -20.0f);
VectG playerVel = VectG(0.0f, 0.0f, 0.0f);
float playerColor = 114.0f;
unsigned int playerScore = 0;
unsigned int playerHighScore = 0;
float scoreFactor = 5.0f;
bool collidedFlag = false;

// Player action flags
bool jumpFlag = false;
bool jumpRotFlag = false;
 
// Object list and variables ques is where are the wallsizex and y used and how do they change
list<Wall> walls;
float wallSizeX[] = {2.0f, 6.0f};
float wallSizeY[] = {1.0f, 20.0f};
float lastObjectPos = 0.0f;

list<DoubleWall> doubleWalls;
float doubSizeX[] = {1.0f, 4.0f};
float doubSizeY[] = {10.0f, 20.0f};
float lastObjectPosDW = 0.0f;

list<BouncingBall> bouncingBalls;
float lastObjectBall = 0.0f;
float radius[] = {1.0f, 2.0f};
float lastObjectPosBall;

float objectVel;
float objectAlpha = 1.0f;

// Non-collision object
list<NonCollision> decorations;
float decorSizeX[] = {1.0f, 5.0f};
float decorPosY[] = {-5.0, 15.0};
float decorPosZ[] = {-5.0, -5.0};
float lastObjectPosNC;
float rotation = 1.0f;



// window size - CHANGE THIS IF YOU ARE ON MAC (Recommended setting: 2 * current window screen) 1280 960
int windowWidth = 640 * 2;
int windowHeight = 480 * 2;

// Camera position
VectG cameraPos = VectG(0, 2, 0);

// Camera speed
double camSpeed = 0.5;

// Keypress array
bool pressedKeys[127] = {false};

// All functions
void drawScene();
void initScene();
void update(int);
void handleResize(int, int);
void handleKeypress(unsigned char, int, int);
void handleKeyReleased(unsigned char, int, int);
void initRendering();
void idle();
void renderBitmapString(float, float, float, void *, char *); // display text
void drawString3D(const char *, float, float);

// Main function
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);

    glutCreateWindow(argv[0]);
    initRendering();

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(handleKeyReleased);
    glutReshapeFunc(handleResize);
    glutIdleFunc(idle);

    // Load high score if exists ** score.txt
    string line;
    ifstream scoreFile("score.txt");
    if (scoreFile.is_open())
    {
   	 getline(scoreFile, line);
   	 playerHighScore = stoi(line);
   	 scoreFile.close();
    }
    else
    {
   	 // Save score
   	 ofstream scoreFile;
   	 scoreFile.open("score.txt");
   	 scoreFile << 0;
   	 scoreFile.close();
    }

    glutTimerFunc(10, update, 0);
    glutMainLoop();
    return 0;
}

// Initialize scene
// this is where all objects are initialized - and random values are assigned - it is only called at start ,restart stages
void initScene()
{
    // init player position and attributes
    playerAngleY = 0.0f;
    playerAngleX = 0.0f;
    playerPos = VectG(0.0f, 10.0f, -20.0f);
    playerPrevPos = VectG(0.0f, 10.0f, -20.0f);
    playerVel = VectG(0.0f, 0.0f, 0.0f);
    playerColor = 114.0f;
    playerScore = 0;
    frame = 0;
    objectVel = 0.5f;

    PLANE_YPOS = -2.0f;

    // clear object lists
    walls.clear();
    doubleWalls.clear();
    bouncingBalls.clear();
    decorations.clear();

    // Initial wall position
    float posZ = -40.0f;

    // wall init
    for (int i = 0; i < 5; i++)
    {
   	 // temporary wall variable
   	 Wall tempWall;

   	 // Random number generator
   	 random_device rand_dev;
   	 mt19937 generator(rand_dev());
   	 uniform_int_distribution<int> distrColor(0, 255);
   	 uniform_real_distribution<double> distrPositionX(-5.0, 5.0);
   	 uniform_real_distribution<double> distrSizeX(wallSizeX[0], wallSizeX[1]);
   	 uniform_real_distribution<double> distrSizeY(wallSizeY[0], wallSizeY[1]);

   	 // Position z why is the z falue for the walls reduced by 65
   	 posZ -= 65.0f;

   	 // Generate color, position, size
   	 tempWall.color = VectG(double(distrColor(generator) / 255.0f), double(distrColor(generator) / 255.0f), double(distrColor(generator) / 255.0f));
   	 //tempWall.color = VectG(double(255.0f), double(255.0f), double(255.0f));
   	 tempWall.position = VectG(distrPositionX(generator), 0.0f, posZ);
   	 tempWall.size = VectG(distrSizeX(generator), distrSizeY(generator), 1.0f);

   	 // Insert into list
   	 walls.push_back(tempWall);
    }

    // Initial double wall position
    float doublePosZ = -100.0f;

    // Double wall init
    for (int i = 0; i < 5; i++)
    {
   	 // temporary wall variable
   	 DoubleWall tempWall;

   	 // Random number generator
   	 random_device rand_dev;
   	 mt19937 generator(rand_dev());
   	 uniform_int_distribution<int> distrColor(0, 255);
   	 uniform_int_distribution<int> distrType(1, 2);
   	 uniform_real_distribution<double> distrPositionX(-5.0, 5.0);
   	 uniform_real_distribution<double> distrGap(2.2, 5.0);
   	 uniform_real_distribution<double> distrSizeX(doubSizeX[0], doubSizeX[1]);
   	 uniform_real_distribution<double> distrSizeY(doubSizeY[0], doubSizeY[1]);

   	 // Generate size and type
   	 tempWall.gap = distrGap(generator);
   	 tempWall.type = distrType(generator);
   	 double sizeX = distrSizeX(generator);
   	 double sizeY = distrSizeY(generator);
   	 double size2 = (PLANE_WIDTH - sizeX - tempWall.gap);
   	 printf("Generated size : %f", PLANE_WIDTH - sizeX);

   	 // Position z
   	 doublePosZ -= 110.0f;

   	 // Generate color, position, gap

   	 tempWall.color = VectG(double(distrColor(generator) /255.0f), double(distrColor(generator) / 255.0f), double(distrColor(generator) / 255.0f));
   	 if (tempWall.type == 1)
   	 {
   		 tempWall.position1 = VectG(-5.0 + sizeX / 2, 0.0f, doublePosZ);
   		 tempWall.position2 = VectG(-5.0 + sizeX + tempWall.gap + size2 / 2, 0.0f, doublePosZ);
   		 tempWall.size1 = VectG(sizeX, sizeY, 0.2f);
   		 tempWall.size2 = VectG(size2, sizeY, 0.2f);
   	 }
   	 else
   	 {
   		 // loosen the difficulty
   		 tempWall.gap += 1.0;
   		 tempWall.position1 = VectG(0.0f, PLANE_YPOS + sizeX / 2.0, doublePosZ);
   		 tempWall.position2 = VectG(0.0f, PLANE_YPOS + sizeX + tempWall.gap + size2 / 2, doublePosZ);
   		 tempWall.size1 = VectG(sizeY, sizeX, 0.2f);
   		 tempWall.size2 = VectG(sizeY, size2, 0.2f);
   	 }

   	 // Insert into list
   	 doubleWalls.push_back(tempWall);
    }

    // Initial ball position
    float ballPosZ = -150.0f;

    for (int i = 0; i < 10; i++)
    {
   	 // temporary ball variable
   	 BouncingBall tempBall;

   	 // Random number generator
   	 // we are initialize a generator function and a distribution function , whenever we want to genereate a new value we call the distribution function and provide the generator function as an argument
   	 random_device rand_dev;
   	 mt19937 generator(rand_dev());
   	 uniform_int_distribution<int> distrColor(0, 255);
   	 uniform_real_distribution<double> distrPositionX(-5.0, 5.0);
   	 uniform_real_distribution<double> distrVelX(-0.005, 0.005);
   	 uniform_real_distribution<double> distrRadius(radius[0], radius[1]);

   	 float ballRadius = distrRadius(generator);

   	 // Position z
   	 ballPosZ -= 85.0f;
   	 tempBall.velocityx = distrVelX(generator);

   	 // Generate color, position, size
   	 tempBall.color = VectG(double(distrColor(generator) / 255.0f), double(distrColor(generator) / 255.0f), double(distrColor(generator) / 255.0f));
   	 tempBall.position = VectG(distrPositionX(generator), 6.0f, ballPosZ);
   	 tempBall.radius = VectG(ballRadius, ballRadius, ballRadius);
   	 tempBall.velocity = 0.0f;

   	 // Insert into list
   	 bouncingBalls.push_back(tempBall);
    }

    // Decorations
    float decorPosZ = -20.0f;

    for (int i = 0; i < 20; i++)
    {
   	 // temporary ball variable
   	 NonCollision tempObject;


   	 // Random number generator
   	 random_device rand_dev;
   	 mt19937 generator(rand_dev());
   	 uniform_int_distribution<int> distrColor(125, 255);
   	 // type alien shape or the weird sphere - trees and a bush
   	 uniform_int_distribution<int> distrType(1, 3);
   	 //
   	 uniform_int_distribution<int> distrLR(1, 2);
   	 uniform_real_distribution<double> distrRotation(-2.0, 2.0);
   	 uniform_real_distribution<double> distrPositionX(-2.0, 2.0);
   	 uniform_real_distribution<double> distrPositionY(decorPosY[0], decorPosY[1]);
   	 uniform_real_distribution<double> distrPositionZ(decorPosZ, decorPosZ);
   	 uniform_real_distribution<double> distrSize(decorSizeX[0], decorSizeX[1]);

   	 float size = distrSize(generator);
   	 int LR = distrLR(generator);

   	 // Position z
   	 decorPosZ -= 50.0f;

   	 // Generate color, position, size
   	 tempObject.rotation = VectG();
   	 tempObject.rotVelX = distrRotation(generator);
   	 tempObject.rotVelY = distrRotation(generator);
   	 tempObject.rotVelZ = distrRotation(generator);
   	 tempObject.type = distrType(generator);
   	 tempObject.color = VectG(double(distrColor(generator) / 255.0f), double(distrColor(generator) / 255.0f), double(distrColor(generator) / 255.0f));
   	 //this if statement makes sure the object are on the far right and left sides of the screen
   	 if (LR == 1)
   	 {
   		 tempObject.position = VectG(distrPositionX(generator) + 30, distrPositionY(generator), decorPosZ + distrPositionZ(generator));
   	 }
   	 else
   	 {
   		 tempObject.position = VectG(distrPositionX(generator) - 30, distrPositionY(generator), decorPosZ + distrPositionZ(generator));
   	 }
   	 tempObject.size = VectG(size, size, size);

   	 // Insert into list
   	 decorations.push_back(tempObject);
    }

    
    
    


    // update last position
    Wall lastWall = walls.back();
    lastObjectPos = lastWall.position[2];
    DoubleWall lastDWall = doubleWalls.back();
    lastObjectPosDW = lastDWall.position1[2];
    BouncingBall lastBall = bouncingBalls.back();
    lastObjectPosBall = lastBall.position[2];
    NonCollision lastNC = decorations.back();
    lastObjectPosNC = lastNC.position[2];
}

// Draw scene
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // -----------------------
    // CAMERA
    // -----------------------
    // Reset perspective : the view angle - should lower it to ground level
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(30.0, (double)windowWidth / (double)windowHeight, 1.0, 200.0);

    // Set camera position
    gluLookAt(playerPos[0], cameraPos[1] + playerPos[1], cameraPos[2], 0.0 + playerPos[0], 0.0 + cameraPos[1] + playerPos[1], -20.0 + cameraPos[2], 0.0, 1.0, 0.0);
    //printf("\nCamera position : %.1f %.1f %.1f", cameraPos[0], cameraPos[1], cameraPos[2]);

    // --------------------
    // LIGHTING AND MODELS
    // ----------------------
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    // Put ambient light - phong model
    float ambInt = 0.3f;
    GLfloat ambientLight[] = {ambInt, ambInt, ambInt, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    // Put light source
    float ligInt = 0.7;
    VectG ligPos = VectG(0, 10, 0);
    GLfloat lightColor[] = {ligInt, ligInt, ligInt, 1.0f};
    GLfloat lightPos[] = {ligPos[0], ligPos[1], ligPos[2], 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glPopMatrix();

    // Player cube
    glPushMatrix();
    // Translation
    glTranslatef(playerPos[0], playerPos[1], playerPos[2]);
    glRotatef(playerAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(playerAngleX, -1.0f, 0.0f, 0.0f);

    // this is most likely where our character will be drawn
    glColor3f(236.0 / 255.0, playerColor / 255.0, 99.0 / 255.0);
    glutSolidCube(BOX_SIZE);
    glPopMatrix();

    if (gameState == 1 || gameState == 2)
    {
        // Draw infinite plane
        glPushMatrix();
        glLoadIdentity();
        glBegin(GL_QUADS);
        glColor3f(254.0 / 255.0, 190.0 / 255.0, 126.0 / 255.0);
        glNormal3f(0.0, 1.0f, 0.0f);
        glVertex3f(-PLANE_WIDTH / 2, PLANE_YPOS, -PLANE_LENGTH);
        glVertex3f(PLANE_WIDTH / 2, PLANE_YPOS, -PLANE_LENGTH);
        glVertex3f(PLANE_WIDTH / 2, PLANE_YPOS, 0);
        glVertex3f(-PLANE_WIDTH / 2, PLANE_YPOS, 0);
        glEnd();
        glPopMatrix();

        // Draw objects
        for (auto const &wall : walls)
        {
            glPushMatrix();
            glLoadIdentity();
            //printf(" wall %f %f %f ",wall.position[0], 1.0f, wall.position[2]);
            glTranslatef(wall.position[0], wall.position[1], wall.position[2]);

            glColor4f(wall.color[0], wall.color[1], wall.color[2], objectAlpha);
            glutSolidCube(BOX_SIZE);
            glEnd();
            glPopMatrix();
        }

        for (auto const &wall : doubleWalls)
        {
            // 1st wall
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(wall.position1[0], wall.position1[1], wall.position1[2]);
            glColor4f(wall.color[0], wall.color[1], wall.color[2], objectAlpha);
            glutSolidCone(1.0f, 1.0f, 40, 40);
            glEnd();
            glPopMatrix();

            // 2nd wall
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(wall.position2[0], wall.position2[1], wall.position2[2]);
            glColor4f(wall.color[0], wall.color[1], wall.color[2], objectAlpha);
            glutSolidCone(1.0f, 1.0f, 40, 40);
            glEnd();
            glPopMatrix();
        }

        for (auto const &ball : bouncingBalls)
        {
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(ball.position[0], ball.position[1], ball.position[2]);
            glScalef(1.0f, 1.0f, 1.0f);
            glColor4f(ball.color[0], ball.color[1], ball.color[2], objectAlpha);
            glutSolidSphere(ball.radius[0], 40, 40);
            glEnd();
            glPopMatrix();
        }

        // Decorations
        for (auto const &decoration : decorations)
        {
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(decoration.position[0], decoration.position[1], decoration.position[2]);
            glRotatef(decoration.rotation[0], 1.0f, 0.0f, 0.0f);
            glRotatef(decoration.rotation[1], 0.0f, 1.0f, 0.0f);
            glRotatef(decoration.rotation[2], 0.0f, 0.0f, 1.0f);
            glColor4f(decoration.color[0], decoration.color[1], decoration.color[2], objectAlpha);
            if (decoration.type == 1)
            {
                glScalef(decoration.size[0], decoration.size[1], decoration.size[2]);
                glutSolidCube(1.0f);
            }
            else if (decoration.type == 2)
            {
                glScalef(decoration.size[0], decoration.size[1], decoration.size[2]);
                glutSolidCone(1.0f, 1.0f, 40, 40);
            }
            else
            {
                glScalef(1.0f, 1.0f, 1.0f);
                glutSolidSphere(decoration.size[0], 40, 40);
            }
            glEnd();
            glPopMatrix();
        }
    }

    // Get string
    if (gameState == 1)
    {
        // Draw score string
        glMatrixMode(GL_PROJECTION);

        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, windowWidth, 0, windowHeight);
        // invert axis
        glScalef(1, -1, 1);
        // move origin
        glTranslatef(0, -windowHeight, 0);

        glMatrixMode(GL_MODELVIEW);
        string scoreString = "Score : " + to_string(playerScore);
        char *cScoreString = new char[scoreString.length() + 1];
        strcpy(cScoreString, scoreString.c_str());
        renderBitmapString(30.0f, 30.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, cScoreString);

        scoreString = "High Score : " + to_string(playerHighScore);
        char *cHScoreString = new char[scoreString.length() + 1];
        strcpy(cHScoreString, scoreString.c_str());
        renderBitmapString(30.0f, 60.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, cHScoreString);
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    }
    else if (gameState == 2)
    {
        glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(-2.0 + cameraPos[0] + playerPos[0], cameraPos[1] + playerPos[1] + 1.0, -10.0);
        drawString3D("GAME OVER!", 5.0, 5.0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.7 + cameraPos[0] + playerPos[0], cameraPos[1] + playerPos[1], -10.0);
        string scoreString = "Score : " + to_string(playerScore);
        char *cScoreString = new char[scoreString.length() + 1];
        strcpy(cScoreString, scoreString.c_str());
        drawString3D(cScoreString, 5.0, 5.0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-2.9 + cameraPos[0] + playerPos[0], cameraPos[1] + playerPos[1] - 1.0, -10.0);
        drawString3D("Press 'r' to restart", 5.0, 5.0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-2.9 + cameraPos[0] + playerPos[0], cameraPos[1] + playerPos[1] - 1.8, -10.0);
        drawString3D("Press 'ESC' to quit", 5.0, 5.0);
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(-1.0 + cameraPos[0] + playerPos[0], cameraPos[1] + playerPos[1] + 1.0, -10.0);
        drawString3D("Cubed!", 5.0, 5.0);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(-2.9 + cameraPos[0] + playerPos[0], cameraPos[1] + playerPos[1] - 1.0, -10.0);
        drawString3D("Press 's' to start!", 5.0, 5.0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-2.7 + cameraPos[0] + playerPos[0], cameraPos[1] + playerPos[1] - 2.0, -10.0);
        string scoreString = "High Score : " + to_string(playerHighScore);
        char *cScoreString = new char[scoreString.length() + 1];
        strcpy(cScoreString, scoreString.c_str());
        drawString3D(cScoreString, 5.0, 5.0);
        glPopMatrix();
    }

    glutSwapBuffers();
}

// Update scene - game logic goes here
void update(int value)
{
    // Check whether the game is running or not
    if (gameState == 1)
    {
        // Plane movement - EXTRA
        float extraFactor = sin(frame) * 0.01;
        PLANE_YPOS += extraFactor;

        // gravity acceleration
        float gravity = -9.8 / timeFactor;

        //----------------------
        // Player Rotations
        //----------------------
        // Y rotation
        /*playerAngleY += 0.5f;
        if (playerAngleY > 360) {
        playerAngleY -= 360;
        }*/

        // jumping X rotation
        if (jumpFlag && jumpRotFlag)
        {
            playerAngleX += 5.0f;
        }
        if (playerAngleX >= 180)
        {
            playerAngleX = 0;
            jumpRotFlag = false;
        }

        //----------------------
        // Player Actions
        //----------------------
        float playerMoveVel = 0.1f;

        // Jump
        if (pressedKeys[int(' ')] == true && jumpFlag == false)
        {
            jumpFlag = true;
            jumpRotFlag = true;
            playerVel[1] += 0.2f;
        }

        // Move left or right
        if (pressedKeys[int('a')] == true)
            playerPos[0] -= playerMoveVel;
        if (pressedKeys[int('d')] == true)
            playerPos[0] += playerMoveVel;

        //--------------------
        // Player Logic
        //--------------------
        // player gravity
        playerPos[1] += playerVel[1];

        // check player collision with objects
        for (auto const &wall : walls)
        {
            if ((playerPos[0] - BOX_SIZE / 2 <= wall.position[0] + wall.size[0] / 2 && playerPos[0] + BOX_SIZE / 2 >= wall.position[0] - wall.size[0] / 2) &&
                (playerPos[1] - BOX_SIZE / 2 <= wall.position[1] + wall.size[1] / 2 && playerPos[1] + BOX_SIZE / 2 >= wall.position[1] - wall.size[1] / 2) &&
                (playerPos[2] - BOX_SIZE / 2 <= wall.position[2] + wall.size[2] / 2 && playerPos[2] + BOX_SIZE / 2 >= wall.position[2] - wall.size[2] / 2))
            {
                playerColor = 0.0f;
                collidedFlag = false;
                printf("\ncollided with wall!");
            }
            else if (!collidedFlag)
            {
                playerColor = 114.0f;
            }
        }

        for (auto const &wall : doubleWalls)
        {
            if (((playerPos[0] - BOX_SIZE / 2 <= wall.position1[0] + wall.size1[0] / 2 && playerPos[0] + BOX_SIZE / 2 >= wall.position1[0] - wall.size1[0] / 2) &&
                 (playerPos[1] - BOX_SIZE / 2 <= wall.position1[1] + wall.size1[1] / 2 && playerPos[1] + BOX_SIZE / 2 >= wall.position1[1] - wall.size1[1] / 2) &&
                 (playerPos[2] - BOX_SIZE / 2 <= wall.position1[2] + wall.size1[2] / 2 && playerPos[2] + BOX_SIZE / 2 >= wall.position1[2] - wall.size1[2] / 2)) ||
                ((playerPos[0] - BOX_SIZE / 2 <= wall.position2[0] + wall.size2[0] / 2 && playerPos[0] + BOX_SIZE / 2 >= wall.position2[0] - wall.size2[0] / 2) &&
                 (playerPos[1] - BOX_SIZE / 2 <= wall.position2[1] + wall.size2[1] / 2 && playerPos[1] + BOX_SIZE / 2 >= wall.position2[1] - wall.size2[1] / 2) &&
                 (playerPos[2] - BOX_SIZE / 2 <= wall.position2[2] + wall.size2[2] / 2 && playerPos[2] + BOX_SIZE / 2 >= wall.position2[2] - wall.size2[2] / 2)))
            {
                playerColor = 0.0f;
                collidedFlag = false;
                printf("\ncollided with double wall!");
            }
            else if (!collidedFlag)
            {
                playerColor = 114.0f;
            }
        }

        for (auto const &ball : bouncingBalls)
        {
            // Get closest point to ball by clamping
            VectG closestPoint = VectG(
                fmin(playerPos[0] + BOX_SIZE / 2, fmax(ball.position[0], playerPos[0] - BOX_SIZE / 2)),
                fmin(playerPos[1] + BOX_SIZE / 2, fmax(ball.position[1], playerPos[1] - BOX_SIZE / 2)),
                fmin(playerPos[2] + BOX_SIZE / 2, fmax(ball.position[2], playerPos[2] - BOX_SIZE / 2)));

            VectG difference = closestPoint - ball.position;
            double distance = difference.length();

            if (distance < ball.radius[0])
            {
                playerColor = 255.0f;
                collidedFlag = false;
                printf("\ncollided with bouncing ball!");
            }
            else if (!collidedFlag)
            {
                playerColor = 114.0f;
            }
        }

        if (collidedFlag)
        {
            gameState = 2;
        }

        collidedFlag = false;

        // check player collision with plane
        if (playerPos[1] - BOX_SIZE / 2 <= PLANE_YPOS &&
            playerPrevPos[1] - BOX_SIZE / 2 > PLANE_YPOS)
        {
            // Check whether cube is inside the game area or not
            if (playerPos[0] + BOX_SIZE / 2 > -PLANE_WIDTH / 2 &&
                playerPos[0] - BOX_SIZE / 2 < PLANE_WIDTH / 2)
            {
                jumpFlag = false;
                playerVel[1] = 0.0f;
                playerPos[1] = PLANE_YPOS + BOX_SIZE / 2;
                //printf("\nplayer pos = %0.2f", playerPos[0] + 0.84f);
            }
        }
        else
            playerVel[1] += gravity;

        // If player is falling down
        if (playerPos[1] < -10.0)
        {
            gameState = 2;
        }

        //--------------------
        // Object Movement
        //---------------------
        lastObjectPos += objectVel;
        lastObjectPosDW += objectVel;
        lastObjectPosBall += objectVel;
        lastObjectPosNC += objectVel;

        // Wall movement
        for (auto &wall : walls)
        {
            wall.position[2] += objectVel;
            wall.position[0] += extraFactor;

            // Reorder objects
            if (wall.position[2] - 2.0f > playerPos[2] + BOX_SIZE / 2)
            {
                wall.position[2] = lastObjectPos - 65.0f;
                lastObjectPos = wall.position[2];

                // Random number generator
                random_device rand_dev;
                mt19937 generator(rand_dev());
                uniform_int_distribution<int> distrColor(0, 255);
                uniform_real_distribution<double> distrPositionX(-5.0, 5.0);
                uniform_real_distribution<double> distrSizeX(wallSizeX[0], wallSizeX[1]);
                uniform_real_distribution<double> distrSizeY(wallSizeY[0], wallSizeY[1]);

                // Generate color, position, size
                wall.color[0] = double(distrColor(generator) / 255.0f);
                wall.color[1] = double(distrColor(generator) / 255.0f);
                wall.color[2] = double(distrColor(generator) / 255.0f);
                wall.position[0] = distrPositionX(generator);
                wall.position[1] = 0.0f;
                wall.size[0] = distrSizeX(generator);
                wall.size[1] = distrSizeY(generator);
                wall.size[2] = 0.1f;
            }
        }

        // Double walls movement
        for (auto &wall : doubleWalls)
        {
            wall.position1[2] += objectVel;
            wall.position2[2] += objectVel;

            // make vertical walls follow the floor
            if (wall.type == 2)
            {
                wall.position1[1] += extraFactor;
                wall.position2[1] += extraFactor;
            }

            // Reorder objects
            if (wall.position1[2] - 2.0f > playerPos[2] + BOX_SIZE / 2)
            {
                wall.position1[2] = lastObjectPosDW - 110.0f;
                wall.position2[2] = lastObjectPosDW - 110.0f;
                lastObjectPosDW = wall.position1[2];

                // Random number generator
                random_device rand_dev;
                mt19937 generator(rand_dev());
                uniform_int_distribution<int> distrColor(0, 255);
                uniform_int_distribution<int> distrType(1, 2);
                uniform_real_distribution<double> distrPositionX(-5.0, 5.0);
                uniform_real_distribution<double> distrGap(2.2, 5.0);
                uniform_real_distribution<double> distrSizeX(doubSizeX[0], doubSizeX[1]);
                uniform_real_distribution<double> distrSizeY(doubSizeY[0], doubSizeY[1]);


                // Generate size and type
                wall.gap = distrGap(generator);
                wall.type = distrType(generator);
                double sizeX = distrSizeX(generator);
                double sizeY = distrSizeY(generator);
                double size2 = (PLANE_WIDTH - sizeX - wall.gap);


                // Generate color, position, gap
                if (wall.type == 1)
                {
                    wall.color = VectG(double(distrColor(generator) / 255.0f), double(distrColor(generator) / 255.0f), double(distrColor(generator) / 255.0f));
                    wall.position1 = VectG(-5.0 + sizeX / 2, 0.0f, wall.position1[2]);
                    wall.position2 = VectG(-5.0 + sizeX + wall.gap + size2 / 2, 0.0f, wall.position2[2]);
                    wall.size1 = VectG(sizeX, sizeY, 0.1f);
                    wall.size2 = VectG(size2, sizeY, 0.1f);
                }
                else
                {
                    wall.gap += 1.0;
                    wall.color = VectG(double(distrColor(generator) / 255.0f), double(distrColor(generator) / 255.0f), double(distrColor(generator) / 255.0f));
                    wall.position1 = VectG(0.0f, PLANE_YPOS + sizeX / 2, wall.position1[2]);
                    wall.position2 = VectG(0.0f, PLANE_YPOS + sizeX + wall.gap + size2 / 2, wall.position2[2]);
                    wall.size1 = VectG(sizeY, sizeX, 0.1f);
                    wall.size2 = VectG(sizeY, size2, 0.1f);
                }
            }
        }


