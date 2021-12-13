#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <Windows.h>


void init(){
	//glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 50, 0, 50, 0, 10);
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
}

void kipchogame() {
	//Kipchogame Text
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(20, 43);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'K');
	glRasterPos2i(21, 43);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
	glRasterPos2i(22, 43);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
	glRasterPos2i(23, 43);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
	glRasterPos2i(24, 43);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'H');
	glRasterPos2i(25, 43);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	glRasterPos2i(26, 43);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
	glRasterPos2i(27, 43);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
	glRasterPos2i(28, 43);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'M');
	glRasterPos2i(29, 43);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');

	 //Loading Text
	glRasterPos2i(21, 2);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
	glRasterPos2i(22, 2);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	glRasterPos2i(23, 2);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
	glRasterPos2i(24, 2);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'D');
	glRasterPos2i(25, 2);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
	glRasterPos2i(26, 2);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
	glRasterPos2i(27, 2);
	glColor3f(0.0, 0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');

	
	//glColor3f(0.0, 1.0, 0.0);
	//glColor3f(0.0, 0.0, 0.0);
	glLineWidth(30);
	glBegin(GL_LINE);
		glVertex2i(10, 18);
		glVertex2i(10, 18);
		glEnd();
		glFlush();

		//loading animation
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(640, 480);
	//glutInitWindowSize(200, 200);
	glutCreateWindow("FLASH SCREEN");
	glutInitWindowPosition(	0, 0);
	//glutInitWindowPosition(10, 10);
	init();
	glutDisplayFunc(kipchogame);
	glutMainLoop();
	return 0;
}


