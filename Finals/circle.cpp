#include <stdlib.h>
#include <iostream>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define PI 3.14159265

const int SCREEN_W = 320;
const int SCREEN_H = 320;
const int MAX_POLY = 4;
int recLevel = 1;
int startingY = 0;
using namespace std;

void liner(float[],float[]);
void producePoly(float polyFace);


void renderScene(void) {

	// Clear Color and Depth Buffers

    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    for(int rec=0;rec<recLevel;rec++)
    {
        int level2 = rec / MAX_POLY;
        int xPos = rec % MAX_POLY;
        glViewport( (GLsizei) (SCREEN_W)*xPos, (GLsizei) SCREEN_H*(startingY-level2-1), (GLsizei) SCREEN_W, (GLsizei) 320 );
        producePoly(rec+1);
    }


	glutSwapBuffers();
}

void producePoly(float polyFace)
{
     int points = (polyFace*4);

    float angle = 0;
    float divisors = 360 / points;


    for(int i=0;i<points;i++)
    {
        //cout<<"angle is: "<<angle<<endl;
        float x1 = cos(angle * PI / 180.0 );
       // cout<<"x1 is: "<<x1<<endl;
        float y1 = sin(angle * PI / 180.0 );
        //cout<<"y1 is: "<<y1<<endl;

        angle = angle + divisors;

       // cout<<"angle is: "<<angle<<endl;
        float x2 = cos(angle * PI / 180.0 );
       // cout<<"x2 is: "<<x2<<endl;
        float y2 = sin(angle * PI / 180.0 );
       // cout<<"y2 is: "<<y2<<endl;
        float v1[] = {x1,y1};
        float v2[] = {x2,y2};
        liner(v1,v2);
    }

}




void liner(float p1[],float p2[])
{
  //  cout<<"Drawing line from: "<<p1[0]<<","<<p1[1]<<" To "<<p2[0]<<","<<p2[1]<<endl;
    glBegin(GL_LINES);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex2fv(p1);
        glVertex2fv(p2);
    glEnd();

}


void keyboardInput(unsigned char key, int x, int y) {
    cout<<int(key)<<endl;
	if (key == 'q' || key=='Q')
		exit(0);

}


int main(int argc, char **argv) {

	// init GLUT and create window

	recLevel = 6;
	startingY = int(recLevel/(MAX_POLY+1));
	startingY++;

	int stretchFactor = 1;
    if(recLevel<MAX_POLY)
    {
        stretchFactor = recLevel;
    }
    else
    {
        stretchFactor = MAX_POLY;
    }


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(SCREEN_W*stretchFactor,SCREEN_H*startingY);
	glutCreateWindow("Smooth Surface - Question 7");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyboardInput);



	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
