#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Code for DDA (Digital Differential Analysis)

#define WIDTH 1366
#define HEIGHT 768

// The line function is the one that actually draws the line onto the screen
void Line(int x1, int y1, int x2, int y2, int r, int g, int b);

void LineDrawer();

int main(int argc, char **argv) {
  // Mandatory function
  glutInit(&argc, argv);

  // Single means only one window
  glutInitDisplayMode(GLUT_SINGLE);

  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Bresenham Line");

  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
  glDepthMask(GL_TRUE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glFlush();
  usleep(100000);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // glClear(GL_COLOR_BUFFER_BIT);
  // Clear the screen with black color
  // glClearColor(0, 0, 0, 1);
  glFlush();

  glMatrixMode(GL_PROJECTION);
  // Sets the angle from which you are viewing, if this is
  // same as window size Means 2d (I think)
  gluOrtho2D(0, WIDTH, 0, HEIGHT);

  // Sets the callback for main loop
  glutDisplayFunc(LineDrawer);

  // Start the main rendering and drawing process
  glutMainLoop();

  return 0;
}

// Equivalent of setPixel from <graphics.h> from TurboC
void setPixel(GLint x, GLint y, int r, int g, int b) {
  glColor3f(r, g, b);
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

// This functions assumes that both points are within the bounds of the drawable
// window
void line(int x0, int y0, int x1, int y1, int r, int g, int b) {
  double x = x0, y = y0;
  double m = (y1 - y) / (x1 - x);

  while (x <= x1) {
    setPixel(round(x), round(y), 255, 255, 255);
    x++;
    y = y + m;
  }
}

void Line1() {
  srand(time(0));
  line(0, 0, 100, 300, 255, 255, 255);
  glFlush();
};

void LineDrawer() {
  glClear(GL_COLOR_BUFFER_BIT);
  // usleep(100);
  glFlush();
  Line1();
  glFinish();
}
