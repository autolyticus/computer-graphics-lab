#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 1366
#define HEIGHT 768

int r = 255, g = 255, b = 255;

void Drawer();

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
  glutDisplayFunc(Drawer);

  // Start the main rendering and drawing process
  glutMainLoop();

  return 0;
}

// Equivalent of setPixel from <graphics.h> from TurboC
void setPixel(GLint x, GLint y, int r, int g, int b) {
  glColor3f(r, g, b);
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  // Uncomment this to get 3 pixel width
  // glVertex2i(x + 1, y);
  // glVertex2i(x + 1, y + 1);
  // glVertex2i(x - 1, y - 1);
  // glVertex2i(x + 1, y - 1);
  // glVertex2i(x - 1, y + 1);
  // glVertex2i(x, y + 1);
  // glVertex2i(x, y - 1);
  // glVertex2i(x - 1, y);
  glEnd();
  // usleep(10000);
  // glFlush();
}

void symSetPixel(int x0, int y0, int x, int y) {
  setPixel(x0 + x, y0 + y, 255, 255, 255);
  setPixel(x0 - x, y0 + y, 255, 255, 255);
  setPixel(x0 + x, y0 - y, 255, 255, 255);
  setPixel(x0 - x, y0 - y, 255, 255, 255);
  setPixel(x0 - y, y0 - x, 255, 255, 255);
  setPixel(x0 + y, y0 - x, 255, 255, 255);
  setPixel(x0 - y, y0 + x, 255, 255, 255);
  setPixel(x0 + y, y0 + x, 255, 255, 255);
}

void circle(int x0, int y0, int r0, int r, int g, int b) {
  int x = r0 - 1, y = 0;
  int dx = 1;
  int dy = 1;
  int err = dx - (2 * r0);

  while (x >= y) {
    symSetPixel(x0, y0, x, y);
    glFlush();
    usleep(1000);

    if (err <= 0) {
      y++;
      err += dy;
      dy += 2;
    }
    if (err > 0) {
      x--;
      dx += 2;
      err += dx - (2 * r0);
    }
  }
}

void Circle1() {
  srand(time(0));
  while (1) {
    // All Circles are located and random height and width, and they touch the x
    // axis
    int randHeight = rand() % HEIGHT, randWidth = rand() % WIDTH;
    circle(randWidth, randHeight, randHeight, rand() % 256, rand() % 256,
           rand() % 256);
    usleep(10000);
    glFlush();
  }
};

void Drawer() {
  glClear(GL_COLOR_BUFFER_BIT);
  Circle1();
  glFinish();
}
