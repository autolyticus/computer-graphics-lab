#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);

  int stepx;
  if (x0 < x1)
    stepx = 1;
  else
    stepx = -1;

  int stepy;
  if (y0 < y1)
    stepy = 1;
  else
    stepy = -1;

  int err;
  // if slope is less than 1
  if (dx > dy) {
    err = dx / 2;
  } else
    err = -dy / 2;

  int e2;

  for (;;) {
    setPixel(x0, y0, r, g, b);
    if (x0 == x1 && y0 == y1)
      break;
    e2 = err;
    if (e2 > -dx) {
      err -= dy;
      x0 += stepx;
    }
    if (e2 < dy) {
      err += dx;
      y0 += stepy;
    }
  }
}

void Line1() {
  srand(time(0));
  while (1) {
    int randHeight = rand() % HEIGHT, randWidth = rand() % WIDTH;
    line(WIDTH / 2, HEIGHT / 2, randWidth, randHeight, rand() % 256,
         rand() % 256, rand() % 256);
    usleep(10000);
    glFlush();
  }
};

void LineDrawer() {
  glClear(GL_COLOR_BUFFER_BIT);
  Line1();
  glFinish();
}
