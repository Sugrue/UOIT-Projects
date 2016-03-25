#include <stdlib.h>
#include "GL/glut.h"
#include <iostream>
#include "Sprite.h"
#include "Grid.h";

void render(void);
 
int main(int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(100, 100);
        glutInitWindowSize(640, 480);
        glutCreateWindow("Simple GLUT Application");
 
        glutDisplayFunc(render);       
 
        glutMainLoop();
}

void render(void) {
		vector<char[0]> test;
		test[0][0] = ' ', ' ', '#';
		Grid testMap;

		testMap.setGridX(1);
		testMap.setGridY(3);
		testMap.setMap(test);
		testMap.Draw();
		
		


        /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
        glBegin(GL_TRIANGLES);
                glColor3f(1, 0, 0);
                glVertex2f(-0.5, -0.5);
                glColor3f(0, 1, 0);
                glVertex2f(0.5, -0.5);
                glColor3f(0, 0, 1);
                glVertex2f(0.0, 0.5);
        glEnd();*/
 
        glutSwapBuffers();
}


//#include <stdlib.h>
//#include <ctime>
//#include "PacmanGame.h"
//
//// ########################################################################################################################
//// ########################################################################################################################
//// ########################################################################################################################
//
//// global info
//#define WINDOW_SCREEN_WIDTH 640
//#define WINDOW_SCREEN_HEIGHT 432
//#define WINDOW_WIDTH 800
//#define WINDOW_HEIGHT 432
//
//// global sprite info
//#define FRAMES_PER_SECOND 15
//#define FRAME_DELAY_SPRITE 1000/FRAMES_PER_SECOND
//
//GridGame *theGame;	// the game object
//
//// ########################################################################################################################
//// this is the openGL callback display global function - delegates drawing to the game
//// ########################################################################################################################
//
//void DisplayCallbackFunction(void)
//{
//	theGame->draw();
//}
//
//
//// ########################################################################################################################
//// this is called many times per second (this enables you to animate things, no drawing, just changing the state)
//// then it calls for a redisplay and to be called back again in FRAME_DELAY_SPRITE milliseconds
//// ########################################################################################################################
//
//void TimerCallbackFunction(int value)
//{
//	theGame->update();		
//
//	glutPostRedisplay();
//	glutTimerFunc(FRAME_DELAY_SPRITE,TimerCallbackFunction,0);
//}
//
//// ########################################################################################################################
//// this is called whenever the window is resized - and sets up the projection matrix properly, currently set up for an orthographic view (2D only)
//// ########################################################################################################################
//
//void WindowReshapeCallbackFunction(int w,int h)
//{
//	float asp = (float)w/(float)h;
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0,WINDOW_SCREEN_WIDTH,0,WINDOW_SCREEN_HEIGHT);
//	
//	theGame->setNewWindowSize(w,h);
//	theGame->setScreenSize(WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT);
//	theGame->updateScreenRatio();
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//// ########################################################################################################################
//// initialize the DevIL library properly
//// ########################################################################################################################
//
//void initImageLibrary()
//{
//	glEnable(GL_TEXTURE_2D);
//	ilInit();
//	iluInit();
//	ilutRenderer(ILUT_OPENGL);
//}
//
//// ########################################################################################################################
//// ########################################################################################################################
//// ########################################################################################################################
//
//int main(int argc, char **argv)
//{
//	srand(time(0));
//
//	// initialize the window and OpenGL
//	glutInit(&argc,argv);
//	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
//	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
//	glutCreateWindow("MY GAME");
//
//	// register callback functions
//	glutDisplayFunc(DisplayCallbackFunction);
//	glutKeyboardFunc(KeyboardCallbackFunction);
//	glutKeyboardUpFunc(KeyboardUpCallbackFunction);
//	glutReshapeFunc(WindowReshapeCallbackFunction);
//	glutMouseFunc(MouseClickCallbackFunction);
//	glutMotionFunc(MouseMotionCallbackFunction);
//	glutTimerFunc(1,TimerCallbackFunction,0);
//	
//	// initialize the image library engine
//	initImageLibrary();
//
//	// init the game
//	theGame = new PacmanGame();
//	theGame -> setNewWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
//	theGame -> initializeGame();
//
//	// start the event handler
//	glutMainLoop();
//	return 0;
//}
//
//// ########################################################################################################################
//// ########################################################################################################################
//// ########################################################################################################################
