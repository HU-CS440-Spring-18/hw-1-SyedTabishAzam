
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


/* Program entry point */
void map_point(int px,int py, int qx, int qy, int ax,int ay,int bx ,int by, int x, int y,int &_x,int &_y);
int main(int argc, char *argv[])
{
    int x=3;
    int y=3;
    cout<<"x and y before: "<<x<<","<<y<<endl;
    map_point(2,2,4,4,8,8,12,12,x,y,x,y);
    cout<<"x and y after:  "<<x<<","<<y<<endl;


    return 1;
}

void map_point(int px,int py, int qx, int qy, int ax,int ay,int bx ,int by, int x, int y,int &_x,int &_y)
{

    int xnew;
    int step1 = (x - px) * ((bx - ax) / (qx - px));
    xnew = step1 + ax;

    int ynew;
    int step2 = (y - py) * ((by - ay) / (qy - py));
    ynew = step2 + ay;

    _x = xnew;
    _y = ynew;
}
