#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
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
int reset = 700;
int startingY = 0;
bool toggle = true;
float offSetx = 0;
float offSety = 0;
bool gameover = false;
int score = 0;
using namespace std;

void liner(float[],float[]);
void producePoly(float polyFace);
void produceDot(void);
void drawText(int);
bool getBoundingBox(int x,int y);
bool record = true;



void keyboardInput(unsigned char key, int x, int y) {
    cout<<int(key)<<endl;
	if (key == 'q' || key=='Q')
		exit(0);

}

void timerCallback(int timer)
{
    //glutPostRedisplay();
    record = true;
    float randX = rand() / float(RAND_MAX);
    int addOrSubX = (-1) + (2*(rand() % 2));

    float randY = rand() / float(RAND_MAX);
    int addOrSubY = (-1) + (2*(rand() % 2));

    offSetx = addOrSubX * randX;
    offSety = addOrSubY * randY;
    toggle = !toggle;

    glutTimerFunc(700, timerCallback, 1);
    glutPostRedisplay();

}

void mouseCapture(int button, int state,int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !gameover )
    {
        bool captured = getBoundingBox(x,y);
        if(captured && toggle && record)
        {
            cout<<"Yes !"<<endl;
            score++;
            //reset = 1500;
            record = false;


        }
        else if(toggle && !record)
        {

            cout<<"Already scored !"<<endl;
        }
        else
        {
            score = score - 1;
            if(score==-3)
                gameover = true;
        }

    }
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !toggle)
    {

    }
}
bool getBoundingBox(int x,int y)
{
    float floatX = (x - float(SCREEN_W/2)) / float(SCREEN_W/2);
    float floatY = (-(y - float(SCREEN_H/2))) / float(SCREEN_H/2);

    if(floatX<offSetx-0.1)
        return false;
    if(floatX>offSetx+0.1)
        return false;
    if(floatY<offSety-0.1)
        return false;
    if(floatY>offSety+0.1)
        return false;

    return true;

}
void produceDot(void) {

	// Clear Color and Depth Buffers
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    if(!gameover)
    {

        if(toggle)
        {



            float radius = 0.05;
            const float pi = 3.17;
            glBegin(GL_POLYGON);
                for(double i = 0; i < 2 * pi; i += pi / 6)
                    glVertex3f(cos(i) * radius + offSetx, sin(i) * radius + offSety, 0.0);
            glEnd();



        }
        else
        {
            glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        drawText(0);
    }
    else
    {
        drawText(1);
    }
    glutSwapBuffers();
}

void drawText(int go)
{
    if(go==0)
    {

        string text = "Score is: ";
        stringstream ss;
        ss<<score;
        text = text + ss.str();
        glRasterPos2f(-0.9, 0.8);
        for(int i =0;i<text.size();i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
        }
    }
    else
    {
        string text = "Game Over";
        glColor3f(1,0,0);
        glRasterPos2f(-0.35, 0);
        for(int i =0;i<text.size();i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        }
    }
}

int main(int argc, char **argv) {

	// init GLUT and create window
	srand(std::time(0));


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(SCREEN_W,SCREEN_H);
	glutCreateWindow("Catch me - Question 4");

	// register callbacks
    glutDisplayFunc(produceDot);
	timerCallback(1);
	glutMouseFunc(mouseCapture);
	glutKeyboardFunc(keyboardInput);



	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
