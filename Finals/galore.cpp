
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
const int SCREEN_W = 320;
const int SCREEN_H = 320;
int pointCount = 4;
int pointing = 0;
bool stateChange = false;
int iter = 0;
bool toggle = true;
string gtext = "Triangle mode";
vector<vector<float>> local;
vector<int> shape;


void drawPoint(vector<float> loc);
void drawText();


static void display(void)
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    drawText();

    for(vector<float> n : local) {
        drawPoint(n);
    }



    glColor3f(1,1,1);
    int counter = 0;
    for(int s : shape) {

        glBegin(GL_POLYGON);
            for(int i=0;i<s;i++)
            {


                float locationX = local.at(i+counter).at(0);
                float locationY = local.at(i+counter).at(1);

                glVertex2f(locationX,locationY);


            }
        glEnd();
        counter = counter + s;

    }

    glutSwapBuffers();
}

void drawPoint(vector<float> loc)
{
    float offSetx = loc.at(0);
    float offSety = loc.at(1);
    //cout<<"Adding to location: "<<offSetx<<" "<<offSety<<endl;
    float radius = 0.02;
    const float pi = 3.17;


    glBegin(GL_POLYGON);
        for(double i = 0; i < 2 * pi; i += pi / 6)
            glVertex3f(cos(i) * radius + offSetx, sin(i) * radius + offSety, 0.0);
    glEnd();

}

void mouseCapture(int button, int state,int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        drawText();
        stateChange = false;
        float floatX = (x - float(SCREEN_W/2)) / float(SCREEN_W/2);
        float floatY = (-(y - float(SCREEN_H/2))) / float(SCREEN_H/2);
        vector<float> click = {floatX,floatY};
        local.push_back(click);

        iter = iter + 1;
        pointing = pointing + 1;
        if(toggle && (pointing % 3)==0)
        {
            cout<<"Push triangle"<<endl;
            shape.push_back(3);
            pointing = 0;
        }
        else if(!toggle && (pointing % 4)==0)
        {
            cout<<"Push Quad"<<endl;
            shape.push_back(4);
            pointing = 0;
        }



    }
    if(toggle==true)
    {

        gtext = "Triangle mode";
    }
    else
    {
        gtext = "Quadrilateral mode";

    }
}

static void key(unsigned char key, int x, int y)
{
    if(key=='q' || key=='Q')
    {
        exit(0);
    }
    else if(key=='t' || key=='T')
    {

        if((!toggle) && pointing==3)
        {
            gtext="Cant toggle at this point - Add another point";
        }
        else
        {
            toggle = !toggle;
            if(toggle==true)
            {

                gtext = "Triangle mode";
            }
            else
            {
                gtext = "Quadrilateral mode";

            }
        }
        drawText();



    }
    else if(key == 'r' || key=='R')
    {
        local.clear();
        shape.clear();
        iter = 0;
        pointing = 0;
        gtext = "Screen Cleared";
        drawText();
    }


}

void drawText()
{


    glColor3f(1,1,1);
    glRasterPos2f(-0.9, 0.8);
    for(int i =0;i<gtext.size();i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, gtext[i]);
    }
}

static void idle(void)
{
    glutPostRedisplay();
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(SCREEN_W,SCREEN_H);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Interaction - Question 2");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(mouseCapture);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
