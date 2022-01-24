#include "object_loader.hpp"

using std::cin;
using std::cout;
using std::endl;

// void object_init(object *obj) {
//     obj->vertex = {};
//     obj->texture = {};
//     obj->normal = {};

//     obj->polygon = {};
//     obj->texture_num = {};
//     obj->normal_num = {};
// }

void reader(object *obj, std::string filename) {
    std::ifstream ifs(filename);
    std::string line;
    while (getline(ifs, line)) {
        if (line[0] == '#') continue;

        if (line.substr(0,6) == "usemtl") {
            obj->mtl = line.substr(7);
        } else if (line.substr(0,2) == "v ") {
            std::array<GLdouble,3> tmp;
            std::stringstream(line.substr(2)) >> tmp[0] >> tmp[1] >> tmp[2];
            obj->vertex.emplace_back(tmp);
        } else if (line.substr(0,6) == "biasV ") {
            std::stringstream(line.substr(6)) >> obj->biasV;
        } else if (line.substr(0,7) == "biasVT ") {
            std::stringstream(line.substr(7)) >> obj->biasVT;
        } else if (line.substr(0,7) == "biasVN ") {
            std::stringstream(line.substr(7)) >> obj->biasVN;
        } else if (line.substr(0,3) == "vt ") {
            std::array<GLdouble,2> tmp;
            std::stringstream(line.substr(3)) >> tmp[0] >> tmp[1];
            obj->texture.emplace_back(tmp);
        } else if (line.substr(0,3) == "vn ") {
            std::array<GLdouble,3> tmp;
            std::stringstream(line.substr(3)) >> tmp[0] >> tmp[1] >> tmp[2];
            obj->normal.emplace_back(tmp);
        } else if (line.substr(0,2) == "f ") {
            std::string x, y, z;
            std::stringstream(line.substr(2)) >> x >> y >> z;
            char slash;
            index_mgl pol, tex, nor;
            std::stringstream(x) >> pol.x >> slash >> tex.x >> slash >> nor.x;
            std::stringstream(y) >> pol.y >> slash >> tex.y >> slash >> nor.y;
            std::stringstream(z) >> pol.z >> slash >> tex.z >> slash >> nor.z;
            pol.x -= obj->biasV;    pol.y -= obj->biasV;    pol.z -= obj->biasV;
            tex.x -= obj->biasVT;   tex.y -= obj->biasVT;   tex.z -= obj->biasVT;
            nor.x -= obj->biasVN;   nor.y -= obj->biasVN;   nor.z -= obj->biasVN;
            obj->polygon.emplace_back(pol);
            obj->texture_num.emplace_back(tex);
            obj->normal_num.emplace_back(nor);
        }
    }
}

