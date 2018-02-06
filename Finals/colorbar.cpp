#include <stdlib.h>
#include <iostream>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


using namespace std;
const int SCREEN_W = 740;
const int SCREEN_H = 160;
void initPoints(bool);





typedef struct Point
{
    float x;                  //  x position of the point
    float y;                  //  y position of the point
    float r;                  //  red color component of the point
    float g;                  //  green color component of the point
    float b;                  //  blue color component of the point

} Point;


Point pointsInLine[SCREEN_W];
void renderScene(void) {


    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    bool bw = true;
    initPoints(bw);

    glBegin(GL_POINTS);
    for(int j=0;j<SCREEN_H;j++)
    {
        float k = j;
        for (int i = 0; i < SCREEN_W; i++)
        {

            glColor3f  (pointsInLine[i].r, pointsInLine[i].g, pointsInLine[i].b);
            glVertex2f (pointsInLine[i].x, pointsInLine[i].y-(k/(SCREEN_H/2)));
        }
    }
    glEnd();




	glutSwapBuffers();
}

void initPoints(bool bw)
{
    Point v0;
    Point v1;
    Point v2;

	v0.x = -1;
	v0.y = 1;

	v1.x = 0;
	v1.y = 1;

	v2.x = 1;
	v2.y = 1;

	if(bw)
    {

        v0.r = 0;
        v0.g = 0;
        v0.b = 0;

        v1.r = 0.5;
        v1.g = 0.5;
        v1.b = 0.5;

        v2.r = 1.0;
        v2.g = 1.0;
        v2.b = 1.0;

    }
    else
    {
        v0.r = 1;
        v0.g = 0;
        v0.b = 0;

        v1.r = 0;
        v1.g = 1;
        v1.b = 0;

        v2.r = 0;
        v2.g = 0;
        v2.b = 1;
    }

    for (int i = 0; i < SCREEN_W/2; i++)
    {
        float u = float(i)/float((SCREEN_W/2));

        pointsInLine[i].x = v0.x * (1.0 - u) + v1.x * u;
        pointsInLine[i].y = v0.y * (1.0 - u) + v1.y * u;
        pointsInLine[i].r = v0.r * (1.0 - u) + v1.r * u;
        pointsInLine[i].g = v0.g * (1.0 - u) + v1.g * u;
        pointsInLine[i].b = v0.b * (1.0 - u) + v1.b * u;

    }

    for (int p = SCREEN_W/2; p < SCREEN_W-1; p++)
    {
        int range = (SCREEN_W-1) - (SCREEN_W/2);
        float u = (float(p)- float(SCREEN_W/2))/float(range);
        pointsInLine[p].x = v1.x * (1.0 - u) + v2.x * u;
        pointsInLine[p].y = v1.y * (1.0 - u) + v2.y * u;
        pointsInLine[p].r = v1.r * (1.0 - u) + v2.r * u;
        pointsInLine[p].g = v1.g * (1.0 - u) + v2.g * u;
        pointsInLine[p].b = v1.b * (1.0 - u) + v2.b * u;

    }
}


void keyboardInput(unsigned char key, int x, int y) {
    cout<<int(key)<<endl;
	if (key == 'q' || key=='Q')
		exit(0);

}

void doIdle()
{
    glutPostRedisplay();
}

int main(int argc, char **argv) {

	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(SCREEN_W,SCREEN_H);
	glutCreateWindow("Color Interpolation - Question 6");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyboardInput);
    glutIdleFunc(doIdle);


	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
