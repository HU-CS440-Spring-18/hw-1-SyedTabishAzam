
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
	cout<<"Enter P's x (px): ";
	int px=2;
	cin>>px;

	cout<<endl<<"Enter P's y (py): ";
	int py=2;
	cin>>py;

	cout<<endl<<"Enter Q's x (qx): ";
	int qx=4;
	cin>>qx;

	cout<<endl<<"Enter Q's y (qy): ";
	int qy=4;
	cin>>qy;

	cout<<endl<<"Enter A's x (ax): ";
	int ax=8;
	cin>>ax;

	cout<<endl<<"Enter A's y (ay): ";
	int ay=8;
	cin>>ay;

	cout<<endl<<"Enter B's x (bx): ";
	int bx=12;
	cin>>bx;

	cout<<endl<<"Enter B's y (by): ";
	int by=12;
	cin>>by;

	cout<<endl<<"Enter X's x (x): ";
	int x=3;
	cin>>x;

	cout<<endl<<"Enter X's y (y): ";
	int y=3;
	cin>>y;

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
