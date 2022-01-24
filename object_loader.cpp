#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;

struct point {
    double x; double y; double z;
};

struct index {
    int x; int y; int z;
};

struct object {
    std::string mtl;
    std::vector<point> vertex;
    std::vector<std::pair<double, double>> texture;
    std::vector<point> normal;

    std::vector<index> polygon;
    std::vector<index> texture_num;
    std::vector<index> normal_num;

    void reader(std::ifstream&);
};

void object::reader(std::ifstream &ifs) {
    object obj;
    std::string line;
    while (getline(ifs, line)) {
        if (line[0] == '#') continue;

        if (line.substr(0,6) == "usemtl") {
            obj.mtl = line.substr(7);
        } else if (line.substr(0,2) == "v ") {
            point tmp;
            std::stringstream(line.substr(2)) >> tmp.x >> tmp.y >> tmp.z;
            obj.vertex.emplace_back(tmp);
        } else if (line.substr(0,3) == "vt ") {
            std::pair<double, double> tmp;
            std::stringstream(line.substr(3)) >> tmp.first >> tmp.second;
            obj.texture.emplace_back(tmp);
        } else if (line.substr(0,3) == "vn ") {
            point tmp;
            std::stringstream(line.substr(3)) >> tmp.x >> tmp.y >> tmp.z;
            obj.normal.emplace_back(tmp);
        } else if (line.substr(0,2) == "f ") {
            std::string x, y, z;
            std::stringstream(line.substr(2)) >> x >> y >> z;
            char slash;
            index pol, tex, nor;
            std::stringstream(x) >> pol.x >> slash >> tex.x >> slash >> nor.x;
            std::stringstream(y) >> pol.y >> slash >> tex.y >> slash >> nor.y;
            std::stringstream(z) >> pol.z >> slash >> tex.z >> slash >> nor.z;
        }
    }
}

int main(void) {
    object obj;
    std::ifstream ifs("OBJ/Body_Circle.obj");
    obj.reader(ifs);

}