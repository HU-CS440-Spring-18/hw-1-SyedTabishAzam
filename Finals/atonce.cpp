
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
const int SCREEN_W = 400;
const int SCREEN_H = 300;
int pointCount = 4;
int pointing = 0;
bool stateChange = false;
int iter = 0;
bool toggle = true;
string gtext = "Triangle mode";
vector<float> local;
vector<int> shape;


void drawPoint(vector<float> loc);
void drawText();


static void display(void)
{


    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);


    glMatrixMode(GL_PROJECTION);


     drawText();

    unsigned int index[iter];
    GLfloat vertices[iter*2] = {};

    bool skip = false;
    for(int it = 0;it<iter*2;it++)
    {
        vertices[it] = local.at(it);
        if(!skip)
        {

            index[it/2] = it/2;

        }
        skip = !skip;

    }
      glColor3f(1,1,1);
      int counter = 0;
        for(int s : shape)
        {
                glVertexPointer(2, GL_FLOAT, sizeof(0.0f)*2, vertices);
                glDrawElements(GL_POLYGON,s,GL_UNSIGNED_INT,&index[counter]);
                counter = counter + s;
        }
//
//        glBegin(GL_POLYGON);
//            for(int i=0;i<s;i++)
//            {
//
//
//                float locationX = local.at(i+counter).at(0);
//                float locationY = local.at(i+counter).at(1);
//
//                glVertex2f(locationX,locationY);
//
//
//            }
//        glEnd();
//        counter = counter + s;
//

  //  glColor3f(1,0,0);







    glutSwapBuffers();
}

void init(void)
{
    glPointSize(5);
    glClearColor (.0, 0.0, 0.0, 0.0);

    glMatrixMode (GL_PROJECTION);

}

//void drawPoint(vector<float> loc)
//{
//    float offSetx = loc.at(0);
//    float offSety = loc.at(1);
//    //cout<<"Adding to location: "<<offSetx<<" "<<offSety<<endl;
//    float radius = 0.02;
//    const float pi = 3.17;
//
//
//    glBegin(GL_POLYGON);
//        for(double i = 0; i < 2 * pi; i += pi / 6)
//            glVertex3f(cos(i) * radius + offSetx, sin(i) * radius + offSety, 0.0);
//    glEnd();
//
//}

void mouseCapture(int button, int state,int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        drawText();
        stateChange = false;
        float floatX = (x - float(SCREEN_W/2)) / float(SCREEN_W/2);
        float floatY = (-(y - float(SCREEN_H/2))) / float(SCREEN_H/2);
        local.push_back(floatX);
        local.push_back(floatY);

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
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("All at once - Question 3");
    glEnableClientState(GL_VERTEX_ARRAY);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(mouseCapture);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
