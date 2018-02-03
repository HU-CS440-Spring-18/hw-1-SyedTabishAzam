#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "second.cpp"

void display() {
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT);
   
   glBegin(GL_TRIANGLES);
      glColor3f(0.0, 0.0, 1.0);
      glVertex2f(-1, -1);
      glColor3f(0.0, 1.0, 0.0);
      glVertex2f(1, -1);
glColor3f(1.0, 0.0, 0.0);
	glVertex2f( 0, 1);
   glEnd();
 
   glFlush();
}
 
int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutCreateWindow("OpenGL Setup Test");
   glutInitWindowSize(320, 320);
   glutInitWindowPosition(50, 50);
   glutDisplayFunc(display);

   
   glutMainLoop();
   return 0;
}
