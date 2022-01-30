#include <string>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
// #include <png++/png.hpp>

struct index_mgl {
    int x; int y; int z;
};

struct object {
    std::string mtl;
    std::vector<std::array<GLdouble,3>> vertex;
    std::vector<std::array<GLdouble,2>> texture;
    std::vector<std::array<GLdouble,3>> normal;

    std::vector<index_mgl> polygon;
    std::vector<index_mgl> texture_num;
    std::vector<index_mgl> normal_num;

    int biasV;
    int biasVT;
    int biasVN;
};

void reader(object*, std::string);
// void object_init(object*);
