#include <iostream>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>
#include "Matrix.hpp"

const int windowWidth = 500.0;
const int windowHeight = 500.0;

struct Point2D {
    float x;
    float y;

    Point2D operator-(const Point2D& rhs) {
        Point2D result;

        result.x = x - rhs.x;
        result.y = y - rhs.y;

        return result;
    }

    float distanceFromPoint(const Point2D& rhs) {
        return std::sqrt(std::pow(x  - rhs.x, 2) + std::pow(y - rhs.y, 2));
    }
};

std::vector<Point2D> bezierPoints{ { 300, 400 }, { 325, 350 }, { 330, 200 }, { 300, 100 }, { 175, 200 }, { 150, 150 } };
Point2D* selectedPoint = nullptr;

std::vector<Point2D> thirdOrderBezierPoints {
        { 50, 50 },
        { 150, 350 },
        { 350, 350 },
        { 450, 50 }
};

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 1.0);	// Set display-window color to white.

    glMatrixMode (GL_PROJECTION);		// Set projection parameters.
    gluOrtho2D (0.0, windowWidth, 0.0, windowHeight);
}

void drawGMTBezier() {
    Matrix gMatrix{ 2, 4 };
    gMatrix.storage[0][0] = thirdOrderBezierPoints[0].x;
    gMatrix.storage[1][0] = thirdOrderBezierPoints[0].y;

    gMatrix.storage[0][1] = thirdOrderBezierPoints[1].x;
    gMatrix.storage[1][1] = thirdOrderBezierPoints[1].y;

    gMatrix.storage[0][2] = thirdOrderBezierPoints[2].x;
    gMatrix.storage[1][2] = thirdOrderBezierPoints[2].y;

    gMatrix.storage[0][3] = thirdOrderBezierPoints[3].x;
    gMatrix.storage[1][3] = thirdOrderBezierPoints[3].y;

    Matrix mMatrix{ 4, 4 };

    mMatrix.storage[0][0] = -1;
    mMatrix.storage[0][1] = 3;
    mMatrix.storage[0][2] = -3;
    mMatrix.storage[0][3] = 1;

    mMatrix.storage[1][0] = 3;
    mMatrix.storage[1][1] = -6;
    mMatrix.storage[1][2] = 3;
    mMatrix.storage[1][3] = 0;

    mMatrix.storage[2][0] = -3;
    mMatrix.storage[2][1] = 3;
    mMatrix.storage[2][2] = 0;
    mMatrix.storage[2][3] = 0;

    mMatrix.storage[3][0] = 1;
    mMatrix.storage[3][1] = 0;
    mMatrix.storage[3][2] = 0;
    mMatrix.storage[3][3] = 0;

    Matrix gmMatrix = gMatrix * mMatrix;

    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(5.0);

    glBegin(GL_LINE_STRIP);

    glColor3f(0.0, 1.0, 0.0);

    for (float t = 0.0; t <= 1.0; t += 0.01) {
        Matrix tMatrix{ 4, 1 };
        tMatrix.storage[0][0] = (float) std::pow(t, 3);
        tMatrix.storage[1][0] = (float) std::pow(t, 2);
        tMatrix.storage[2][0] = t;
        tMatrix.storage[3][0] = 1;

        Matrix pointMatrix = gmMatrix * tMatrix;
        glVertex2f(pointMatrix.storage[0][0], pointMatrix.storage[1][0]);
    }

    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for (auto& p: thirdOrderBezierPoints) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (auto& p: thirdOrderBezierPoints) {
        glVertex2f(p.x, p.y);
    }
    glEnd();

    glutSwapBuffers();
}

void drawWeightedGMTBezier() {
    Matrix gMatrix{ 3, 4 };
    gMatrix.storage[0][0] = thirdOrderBezierPoints[0].x;
    gMatrix.storage[1][0] = thirdOrderBezierPoints[0].y;
    gMatrix.storage[2][0] = 0.9;

    gMatrix.storage[0][1] = thirdOrderBezierPoints[1].x;
    gMatrix.storage[1][1] = thirdOrderBezierPoints[1].y;
    gMatrix.storage[2][1] = 0.3;

    gMatrix.storage[0][2] = thirdOrderBezierPoints[2].x;
    gMatrix.storage[1][2] = thirdOrderBezierPoints[2].y;
    gMatrix.storage[2][2] = 0.3;

    gMatrix.storage[0][3] = thirdOrderBezierPoints[3].x;
    gMatrix.storage[1][3] = thirdOrderBezierPoints[3].y;
    gMatrix.storage[2][3] = 0.7;

    Matrix mMatrix{ 4, 4 };

    mMatrix.storage[0][0] = -1;
    mMatrix.storage[0][1] = 3;
    mMatrix.storage[0][2] = -3;
    mMatrix.storage[0][3] = 1;

    mMatrix.storage[1][0] = 3;
    mMatrix.storage[1][1] = -6;
    mMatrix.storage[1][2] = 3;
    mMatrix.storage[1][3] = 0;

    mMatrix.storage[2][0] = -3;
    mMatrix.storage[2][1] = 3;
    mMatrix.storage[2][2] = 0;
    mMatrix.storage[2][3] = 0;

    mMatrix.storage[3][0] = 1;
    mMatrix.storage[3][1] = 0;
    mMatrix.storage[3][2] = 0;
    mMatrix.storage[3][3] = 0;

    Matrix gmMatrix = gMatrix * mMatrix;

    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(5.0);

    glBegin(GL_LINE_STRIP);

    glColor3f(0.0, 1.0, 0.0);

    for (float t = 0.0; t <= 1.0; t += 0.01) {
        Matrix tMatrix{ 4, 1 };
        tMatrix.storage[0][0] = (float) std::pow(t, 3);
        tMatrix.storage[1][0] = (float) std::pow(t, 2);
        tMatrix.storage[2][0] = t;
        tMatrix.storage[3][0] = 1;

        Matrix pointMatrix = gmMatrix * tMatrix;
        glVertex2f(pointMatrix.storage[0][0] / gmMatrix.storage[2][0], pointMatrix.storage[1][0] / gMatrix.storage[2][0]);
    }

    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for (auto& p: thirdOrderBezierPoints) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (auto& p: thirdOrderBezierPoints) {
        glVertex2f(p.x, p.y);
    }
    glEnd();

    glutSwapBuffers();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(5.0);

    glBegin(GL_LINE_STRIP);

    glColor3f(0.0, 1.0, 0.0);
    int n = (int) bezierPoints.size();

    for (float t = 0.0; t <= 1.0; t += 0.01) {
        std::vector< std::vector<Point2D> > lineSegments;
        lineSegments.push_back(bezierPoints);
        for (int i = 0; i < n - 1; i++) {
            lineSegments.push_back(std::vector<Point2D>{});
            for (int j = 0; j < lineSegments[i].size() - 1; j++) {
                float x = lineSegments[i][j].x + (lineSegments[i][j + 1].x - lineSegments[i][j].x) * t;
                float y = lineSegments[i][j].y + (lineSegments[i][j + 1].y - lineSegments[i][j].y) * t;

                lineSegments[i + 1].push_back({ x, y });
            }
        }
        Point2D pointToDraw = lineSegments.back()[0];
        glVertex2f(pointToDraw.x, pointToDraw.y);
    }

    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for (auto& p: bezierPoints) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (auto& p: bezierPoints) {
        glVertex2f(p.x, p.y);
    }
    glEnd();

    glutSwapBuffers();
}

void mouseHandler(int button, int state, int x, int y) {
    if (button == GLUT_LEFT) {
        if (state == GLUT_DOWN) {

            Point2D downPoint{ (float)x, (float)windowHeight - y };

            for (Point2D &p: thirdOrderBezierPoints) {
                if (p.distanceFromPoint(downPoint) < 10.0) {
                    selectedPoint = &p;
                }
            }

        } else if (state == GLUT_UP && selectedPoint != nullptr) {
            selectedPoint = nullptr;
        }
    }
}

void motionHandler(int x, int y) {
    if (selectedPoint != nullptr) {
        selectedPoint->x = x;
        selectedPoint->y = windowHeight - y;
        glutPostRedisplay();
    }
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   // Set display mode.
    glutInitWindowPosition(50, 100);   // Set top-left display-window position.
    glutInitWindowSize(windowWidth, windowHeight);      // Set display-window width and height.
    glutCreateWindow("An Example OpenGL Program"); // Create display window.

    init();                            // Execute initialization procedure.
    glutDisplayFunc(drawGMTBezier);       // Send graphics to display window.
    glutMouseFunc(mouseHandler);
    glutMotionFunc(motionHandler);
    glutMainLoop ();                    // Display everything and wait.
    return 0;
}