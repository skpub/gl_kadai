#include "material_loader.hpp"

void material_reader(material_box *mt, std::string filename) {
    std::ifstream ifs(filename);
    std::string line;
    std::string current_mtl_name;
    material    current_mtl;

    while (getline(ifs, line)) {
        if (line.substr(0,7) == "newmtl ") {
            current_mtl_name = line.substr(7);
            break;
        }
    }

    while (getline(ifs, line)) {
        if (line[0] == '#') continue;
        if (line.substr(0,7) == "newmtl ") {
            current_mtl_name = line.substr(7);
        } else if (line.substr(0,3) == "Ns ") {
            std::stringstream(line.substr(3)) >> current_mtl.Ns;
        } else if (line.substr(0,3) == "Ka ") {
            std::stringstream(line.substr(3))
                >> current_mtl.Ka[0] >> current_mtl.Ka[1] >> current_mtl.Ka[2];
        } else if (line.substr(0,3) == "Kd ") {
            std::stringstream(line.substr(3))
                >> current_mtl.Kd[0] >> current_mtl.Kd[1] >> current_mtl.Kd[2];
        } else if (line.substr(0,3) == "Ks ") {
            std::stringstream(line.substr(3))
                >> current_mtl.Ks[0] >> current_mtl.Ks[1] >> current_mtl.Ks[2];
        } else if (line.substr(0,3) == "Ke ") {
            std::stringstream(line.substr(3))
                >> current_mtl.Ke[0] >> current_mtl.Ke[1] >> current_mtl.Ke[2];
        } else if (line.substr(0,2) == "d ") {
            std::stringstream(line.substr(2)) >> current_mtl.d;
        } else if (line.substr(0,3) == "Ni ") {
            std::stringstream(line.substr(3)) >> current_mtl.Ni;
        } else if (line.substr(0,6) == "illum ") {
            std::stringstream(line.substr(6)) >> current_mtl.illum;
        } else if (line.substr(0,7) == "map_Kd ") {
            std::stringstream(line.substr(7)) >> current_mtl.map_Kd;
        } else if (line == "") {
            mt->box[current_mtl_name] = current_mtl;
            clear_material(&current_mtl);
        }
    }
    // std::cout << current_mtl_name << std::endl;
    mt->box[current_mtl_name] = current_mtl;
    clear_material(&current_mtl);
}

void clear_material(material* mt) {
    mt->d = NULL;
    mt->illum = NULL;
    mt->Ka = {};
    mt->Kd = {};
    mt->Ke = {};
    mt->Ks = {};
    mt->map_Kd = "";
    mt->Ni = NULL;
    mt->Ns = NULL;
}
