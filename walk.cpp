#include <stdlib.h>
#include <GL/glut.h>

GLuint objects;

void display(void) {
    static GLfloat lightpos[] = {3.0, 4.0, 5.0, 1.0};
    static double ex = 0.0, ez = 0.0;
    static double r = 0.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotated(4, 0.0, 1.0, 0.0);
    glTranslated(ex, 0.0, ez);

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glCallList(objects);
    glFlush();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == '\033' || key == 'q') exit(0);
}

void scene(void) {
    static GLfloat red[] = {0.8, 0.2, 0.2, 1.0};
    static GLfloat green[] = {0.2, 0.2, 0.8, 1.0};
    static GLfloat blue[] = {0.8, 0.2, 0.2, 1.0};
    static GLfloat yellow[] = {0.8, 0.8, 0.2, 1.0};
    static GLfloat ground[][4] = {
        {0.6, 0.6, 0.6, 1.0},
        {0.3, 0.3, 0.3, 1.0}
    };
    objects = glGenLists(1);
    glNewList(objects, GL_COMPILE);
    
    glPushMatrix();
    glTranslated(0.0, 0.0, -3.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 0, 3.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-3.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    glutSolidCube(1.0);
    glPopMatrix();

    glBegin(GL_QUADS);
    glNormal3d(0.0, 1.0, 0.0);
    for (int j = -5; j < 5; j++) {
        for (int i = -5; i < 5; i++) {
            glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
            glVertex3d((GLdouble)i, -0.5, (GLdouble)j);
            glVertex3d((GLdouble)i, -0.5, (GLdouble)(j + 1));
            glVertex3d((GLdouble)(i + 1), -0.5, (GLdouble)(j + 1));
            glVertex3d((GLdouble)(i + 1), -0.5, (GLdouble)j);
        }
    }
    glEnd();
    glEndList();
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    scene();
    init();
    glutMainLoop();
    return 0;
}
