#include <GL/glut.h>
#include <stdio.h>

// The line function is the one that actually draws the line onto the screen
void Line(int x1, int y1, int x2, int y2, int r, int g, int b);

void LineDrawer();

int main(int argc, char **argv) {
  // Mandatory function
  glutInit(&argc, argv);

  // Single means only one window
  glutInitDisplayMode(GLUT_SINGLE);

  glutInitWindowSize(1366, 768);
  glutCreateWindow("Bresenham Line");

  // Clear the screen with black color
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // Sets the angle from which you are viewing, if this is
  // same as window size Means 2d (I think)
  gluOrtho2D(0.0, 1366.0, 0.0, 768.0);

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
  glVertex2f(x, y);
  // glVertex2f(x + 1, y + 1);
  // glVertex2f(x - 1, y - 1);
  // glVertex2f(x + 1, y - 1);
  // glVertex2f(x - 1, y + 1);
  glEnd();
}

// Bresenham's Algorithm actual implementation
void Line(int x0, int y0, int xn, int yn, int r, int g, int b) {
  int x, y;
  int dx, dy;
  int pk;
  int k;
  // Set starting pixel
  setPixel(x0, y0, r, g, b);

  // Calculate total change in x and y
  dx = xn - x0, dy = yn - y0;

  // Initial error in slope
  pk = 2 * dy - dx;

  // Starting values
  x = x0, y = y0;

  // Maximum number of pixels is dx
  for (k = 0; k < dx - 1; k++) {
    if (pk < 0) {
      // if error is less than 0.5 then do nothing
      pk = pk + 2 * dy;
    } else {
      // if error has become more than 0.5 then increment y
      pk = pk + 2 * dy - 2 * dx;
      y++;
    }

    // Increment x in either case
    x++;

    // Set the current value of x, y
    setPixel(x, y, r, g, b);
  }
}

void Line1() { Line(50, 50, 233, 212, 255, 255, 255); };

void LineDrawer() {
  glClear(GL_COLOR_BUFFER_BIT);
  Line1();
  glFinish();
}
