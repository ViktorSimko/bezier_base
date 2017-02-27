#include <iostream>
#include <GLUT/GLUT.h>
#include <vector>
#include <cmath>

const int windowWidth = 1000.0;
const int windowHeight = 1000.0;

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

std::vector<Point2D> bezierPoints{ { 600, 800 }, { 650, 700 }, { 660, 400 }, { 600, 200 }, { 350, 400 }, { 300, 300 } };
Point2D* selectedPoint = nullptr;

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 1.0);	// Set display-window color to white.

    glMatrixMode (GL_PROJECTION);		// Set projection parameters.
    gluOrtho2D (0.0, windowWidth, 0.0, windowHeight);
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
            if (downPoint.distanceFromPoint(bezierPoints[0]) < 10) {
                selectedPoint = &bezierPoints[0];
            } else if (downPoint.distanceFromPoint(bezierPoints[1]) < 10) {
                selectedPoint = &bezierPoints[1];
            } else if (downPoint.distanceFromPoint(bezierPoints[2]) < 10) {
                selectedPoint = &bezierPoints[2];
            } else if (downPoint.distanceFromPoint(bezierPoints[3]) < 10) {
                selectedPoint = &bezierPoints[3];
            } else if (downPoint.distanceFromPoint(bezierPoints[4]) < 10) {
                selectedPoint = &bezierPoints[4];
            } else if (downPoint.distanceFromPoint(bezierPoints[5]) < 10) {
                selectedPoint = &bezierPoints[5];
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
    glutDisplayFunc(display);       // Send graphics to display window.
    glutMouseFunc(mouseHandler);
    glutMotionFunc(motionHandler);
    glutMainLoop ();                    // Display everything and wait.
    return 0;
}