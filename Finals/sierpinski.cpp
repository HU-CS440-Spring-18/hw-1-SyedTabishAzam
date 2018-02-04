#include <stdlib.h>
#include <iostream>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

void liner(float[],float[]);
void produceTriangle(float p0[],float p1[],float p2[],int n);
float getMid(float v1,float v2);
int rLevel = 1;

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

    int recursionLevel = rLevel;

    float p0[]={-1,-1};
    float p1[]={1,-1};
    float p2[]={0,1};

	produceTriangle(p0,p1,p2,recursionLevel);

	glutSwapBuffers();
}
float getMid(float v1,float v2)
{

    float res=(v1+v2) / 2;
    return res;
}


void produceTriangle(float p0[],float p1[],float p2[],int n)
{


    liner(p0,p1);
    liner(p1,p2);
    liner(p2,p0);


    if(n>0)
    {
        float v1x = getMid(p0[0],p1[0]);
        float v1y = getMid(p0[1],p1[1]);


        float v2x = getMid(p0[0],p2[0]);
        float v2y = getMid(p0[1],p2[1]);

        float v3x = getMid(p1[0],p2[0]);
        float v3y = getMid(p1[1],p2[1]);

        float mid0and1[] = {v1x,v1y};
        float mid0and2[] = {v2x,v2y};
        float mid1and2[] = {v3x,v3y};

        produceTriangle(p0,mid0and1,mid0and2,n-1);
        produceTriangle(p1,mid1and2,mid0and1,n-1);
        produceTriangle(p2,mid0and2,mid1and2,n-1);

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
	cout<<"Enter recursion level for Sierpinski triangle: "<<endl;
	rLevel = 1;
	cin>>rLevel;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Sierpinski - Question 8");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyboardInput);



	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
