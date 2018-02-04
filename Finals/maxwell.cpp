#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif // platform

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

void keyboardEvent(unsigned char key,int x,int y)
{
    if(key=='q' || key=='Q')
        exit(0);
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutCreateWindow("Color Interpolation - Question 5");
   glutInitWindowSize(320, 320);
   glutInitWindowPosition(50, 50);
   glutDisplayFunc(display);

   glutKeyboardFunc(keyboardEvent);

   glutMainLoop();
   return 0;
}
