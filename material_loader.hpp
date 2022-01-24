#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <unordered_map>

struct material {
    double Ns;
    std::array<double, 3> Ka;
    std::array<double, 3> Kd;
    std::array<double, 3> Ks;
    std::array<double, 3> Ke;
    double Ni;
    double d; 
    int illum;
    std::string map_Kd;
};

struct material_box {
    std::unordered_map<std::string, material> box;
};

void clear_material(material*);
void material_reader(material_box*, std::string);