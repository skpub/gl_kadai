#include <vector>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <GL/glut.h>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <cstring>
#include "object_loader.hpp"
#include "material_loader.hpp"
#include <png++/png.hpp>

#define HEIGHT  1024
#define WIDTH   1024

using std::cout;
using std::endl;

std::vector<object> obj_s;
material_box mtlbox;
// std::vector<png::image<png::rgb_pixel>> image;
GLuint _texname[100];
// std::vector<std::vector<GLubyte>> imgraw_s;

struct img_2_10 {
    GLubyte img[HEIGHT][WIDTH][3];
};

std::unordered_map<std::string, int> img_index_box;
std::vector<GLubyte[HEIGHT][WIDTH][3]> img_box(10);

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
    gluLookAt(20.0, 29.0, 70.0, 0.0, 22.0, 0.0, 0.0, 1.0, 0.0);
    glRotated((double)r, 0.0, 1.0, 0.0);

    glFlush();
    glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, _texname[0]);
    for (object obj: obj_s) {
        if (mtlbox.box[obj.mtl].map_Kd != "") {
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGB,
                WIDTH, HEIGHT, 0,
                GL_RGB, GL_UNSIGNED_BYTE, img_box[img_index_box[mtlbox.box[obj.mtl].map_Kd]]
            );
        }
        glBegin(GL_TRIANGLES);
        for (int j = 0; j < obj.polygon.size(); j++) {
            glNormal3dv(obj.normal[obj.normal_num[j].x].data());
            glTexCoord2dv(obj.texture[obj.texture_num[j].x].data()),
            glVertex3dv(obj.vertex[obj.polygon[j].x].data());

            glNormal3dv(obj.normal[obj.normal_num[j].y].data());
            glTexCoord2dv(obj.texture[obj.texture_num[j].y].data()),
            glVertex3dv(obj.vertex[obj.polygon[j].y].data());

            glNormal3dv(obj.normal[obj.normal_num[j].z].data());
            glTexCoord2dv(obj.texture[obj.texture_num[j].z].data()),
            glVertex3dv(obj.vertex[obj.polygon[j].z].data());
        } 
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);

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
    glClearColor(0.0,0.0,0.0,0.0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);

    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  

    static int tex_img_counter = 0;
    for (auto mtl: mtlbox.box) {
        if (mtl.second.map_Kd != "") {
            png::image<png::rgb_pixel> tmp_source("OBJ/" + mtl.second.map_Kd);
            GLubyte tmp_img[HEIGHT][WIDTH][3];
            // for (int i = 0; i < HEIGHT; i++) {
            //     for (int j = 0; j < WIDTH; j++) {
            //         tmp_img[i][j][0] = tmp_source[i][j].red;
            //         tmp_img[i][j][1] = tmp_source[i][j].green;
            //         tmp_img[i][j][2] = tmp_source[i][j].blue;
            //     }
            // }
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    img_box[tex_img_counter][i][j][0] = tmp_source[i][j].red;
                    img_box[tex_img_counter][i][j][1] = tmp_source[i][j].green;
                    img_box[tex_img_counter][i][j][2] = tmp_source[i][j].blue;
                }
            }
            img_index_box[mtl.second.map_Kd] = tex_img_counter;
            // std::memcpy(img_box[tex_img_counter], tmp_img, sizeof(tmp_img));
            tex_img_counter++;
        }
    }
}

int main(int argc,char *argv[])
{
    for (auto i: std::filesystem::directory_iterator("OBJ")) {
        if (i.path().filename().extension() == ".obj") {
            object tmp;
            reader(&tmp, "OBJ/" + i.path().filename().generic_string());
            // cout << i.path().filename().generic_string() << endl;
            obj_s.emplace_back(std::move(tmp));
        }
    }
    material_reader(&mtlbox, "OBJ/TONG_KING_TOWER2.mtl");
    // for (auto i: mtlbox.box) {
    //     cout << "*--*" << i.first << "*--*" << endl;
    //     cout << i.second.map_Kd << endl;
    //     cout << "Ka: " << i.second.Ka[0] << i.second.Ka[1] << i.second.Ka[2] << endl;
    // }

    glutInitWindowPosition(960,540);
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

// GLdouble vertex[][3] = {
//     {0.0, 0.0, 0.0},
//     {1.0, 0.0, 0.0},
//     {1.0, 1.0, 0.0},
//     {0.0, 1.0, 0.0},
//     {0.0, 0.0, 1.0},
//     {1.0, 0.0, 1.0},
//     {1.0, 1.0, 1.0},
//     {0.0, 1.0, 1.0},
// };

// int face[][4]= {
//     {0, 1, 2, 3},
//     {1, 5, 6, 2},
//     {5, 4, 7, 6},
//     {4, 0, 3, 7},
//     {4, 5, 1, 0},
//     {3, 2, 6, 7},
// };

// GLdouble normal[][3] = {
//     {0.0, 0.0, -1.0},
//     {1.0, 0.0, 0.0},
//     {0.0, 0.0, 1.0},
//     {-1.0, 0.0, 0.0},
//     {0.0, -1.0, 1.0},
//     {0.0, 1.0, 0.0},
// };

// GLdouble color[][3] = {
//     {1.0, 0.0, 0.0},
//     {0.0, 1.0, 0.0},
//     {0.0, 0.0, 1.0},
//     {1.0, 1.0, 0.0},
//     {1.0, 0.0, 1.0},
//     {0.0, 1.0, 1.0},
// };

// int edge[][2] = {
//     {0, 1},
//     {1, 2},
//     {2, 3},
//     {3, 0},
//     {4, 5},
//     {5, 6},
//     {6, 7},
//     {7, 4},
//     {0, 4},
//     {1, 5},
//     {2, 6},
//     {3, 7},
// };