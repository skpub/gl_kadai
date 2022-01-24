#include <vector>
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include "object_loader.hpp"
#include "material_loader.hpp"
#include <png++/png.hpp>

using std::cout;
using std::endl;

object obj;
material_box mtlbox;

GLdouble vertex[][3] = {
    {0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {1.0, 1.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 0.0, 1.0},
    {1.0, 1.0, 1.0},
    {0.0, 1.0, 1.0},
};

int face[][4]= {
    {0, 1, 2, 3},
    {1, 5, 6, 2},
    {5, 4, 7, 6},
    {4, 0, 3, 7},
    {4, 5, 1, 0},
    {3, 2, 6, 7},
};

GLdouble normal[][3] = {
    {0.0, 0.0, -1.0},
    {1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {-1.0, 0.0, 0.0},
    {0.0, -1.0, 1.0},
    {0.0, 1.0, 0.0},
};

GLdouble color[][3] = {
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 1.0, 0.0},
    {1.0, 0.0, 1.0},
    {0.0, 1.0, 1.0},
};

int edge[][2] = {
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 0},
    {4, 5},
    {5, 6},
    {6, 7},
    {7, 4},
    {0, 4},
    {1, 5},
    {2, 6},
    {3, 7},
};

void idle(void) {
    glutPostRedisplay();
}

void display(void)
{
    int i;
    int j;
    static int r = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(40.0, 16.0, 40.0, 0.0, 17.0, 0.0, 0.0, 1.0, 0.0);

    glRotated((double)r, 0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLES);
    for (int j = 0; j < obj.polygon.size(); j++) {
    // for (int j = 0; j < 100; j++) {
        glNormal3dv(obj.normal[obj.normal_num[j].x].data());
        glVertex3dv(obj.vertex[obj.polygon[j].x].data());
        glVertex3dv(obj.vertex[obj.polygon[j].y].data());
        glVertex3dv(obj.vertex[obj.polygon[j].z].data());
    } 

    glEnd();

    glutSwapBuffers();
    if (r++ >= 360) r = 0;

    if (r++ >= 360) r = 0;
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                glutIdleFunc(idle);
            }
            else {
                glutIdleFunc(0);
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                glutPostRedisplay();
            }
            break;
        default:
            break;
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key)
    {
    case 'q':
    case 'Q':
    case '\033':
        exit(0);
    default:
        break;
    }
}

void init(void) {
    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

int main(int argc,char *argv[])
{
    reader(&obj, "OBJ/Body_Circle.obj");
    material_reader(&mtlbox, "OBJ/TONG_KING_TOWER.mtl");

    cout << mtlbox.box["Material.001"].illum << endl;
    
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1920,1080);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}