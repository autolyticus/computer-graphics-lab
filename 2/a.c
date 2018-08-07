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
  // glVertex2f(x + 1, y + 1);
  // glVertex2f(x - 1, y - 1);
  // glVertex2f(x + 1, y - 1);
  // glVertex2f(x - 1, y + 1);
  glEnd();
  // usleep(10000);
  // glFlush();
}

void symSetPixel(int x0, int y0, int x, int y) {
  setPixel(x0 + x, y0 + y, 255, 255, 255);
  // glFlush();
  setPixel(x0 - x, y0 + y, 255, 255, 255);
  // glFlush();
  setPixel(x0 + x, y0 - y, 255, 255, 255);
  // glFlush();
  setPixel(x0 - x, y0 - y, 255, 255, 255);
  // glFlush();
  setPixel(x0 - y, y0 - x, 255, 255, 255);
  // glFlush();
  setPixel(x0 + y, y0 - x, 255, 255, 255);
  // glFlush();
  setPixel(x0 - y, y0 + x, 255, 255, 255);
  // glFlush();
  setPixel(x0 + y, y0 + x, 255, 255, 255);
  // glFlush();
}

void circle(int x0, int y0, int r0, int r, int g, int b) {
  int x = r0 - 1, y = 0;
  int dx = 1;
  int dy = 1;
  int err = dx - (2 * r0);

  while (x >= y) {
    symSetPixel(x0, y0, x, y);
    glFlush();
    usleep(10000);

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

// void circle(int x0, int y0, int r0, int r, int g, int b) {
//   int x = 0, y = r0;
//   int d = 3 - 2 * r;
//   while (y >= x) {
//     symSetPixel(x0, y0, x, y);
//     x++;

//     if (d > 0) {
//       y--;
//       d = d + 4 * (x - y) + 10;
//     } else
//       d = d + 4 * x + 6;
//     symSetPixel(x0, y0, x, y);
//   }
// }

void Circle1() {
  srand(time(0));
  // glfwGetMousePos(&xpos, &ypos);
  while (1) {
    // for (int i = 0; i < 1000; i++) {
    int randHeight = rand() % HEIGHT, randWidth = rand() % WIDTH;
    circle(WIDTH / 2, HEIGHT / 2, randHeight, rand() % 256, rand() % 256,
           rand() % 256);
    usleep(10000);
    glFlush();
    // glClear(GL_COLOR_BUFFER_BIT);
  }
};

void Drawer() {
  glClear(GL_COLOR_BUFFER_BIT);
  // usleep(100);
  // glFlush();
  Circle1();
  glFinish();
}
