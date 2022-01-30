#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <filesystem>
#include <GL/glut.h>

inline void mkdir() {
    if (! std::filesystem::exists("OBJ"))
        std::filesystem::create_directory("OBJ");
    std::string cpath = std::filesystem::current_path();
    std::filesystem::current_path(cpath + "/OBJ");
}

void splitter(std::ifstream& ifs, std::string source_dir) {
    std::cout << source_dir << std::endl;
    mkdir();
//-------------------
    std::string         object;
    std::string         line = "";
    // std::stringstream   ss("");
    std::ofstream       ofs;
    bool                first_object = true;

    int biasV   = 1;
    int biasVT  = 1;
    int biasVN  = 1;
    while (getline(ifs, line)) {
        // BIAS
        if (line.substr(0,2) == "v ") biasV++;
        if (line.substr(0,3) == "vt ") biasVT++;
        if (line.substr(0,3) == "vn ") biasVN++;
        // -- BIAS
        if (line[0] == '#') continue;
        if (line.substr(0,6) == "mtllib") {
            std::ifstream mtl(source_dir + "/" + line.substr(7));
            std::string tmp;
            std::ofstream mtldest(line.substr(7));
            while (getline(mtl, tmp)) {
                mtldest << tmp << std::endl;
            }
            mtldest.close();
        }
        if (line[0] == 'o') {
            if (first_object) {
                object = line.substr(2);
                ofs.open(object + ".obj");
                ofs << "biasV " << biasV << std::endl;
                ofs << "biasVT " << biasVT << std::endl;
                ofs << "biasVN " << biasVN << std::endl;
                first_object = ! first_object;
            } else {
                ofs.close();
                // ----------- Initialize for next object.
                object = line.substr(2);
                ofs.open(object + ".obj");
                ofs << "biasV " << biasV << std::endl;
                ofs << "biasVT " << biasVT << std::endl;
                ofs << "biasVN " << biasVN << std::endl;
            }
        } else {
            if (line == "") {
                ofs.close();
            }
        }
        ofs << line << std::endl;
    }
}


int main(void) {
    std::ifstream ifs("TONGKING/TONG_KING_TOWER.obj");
    splitter(ifs, std::filesystem::current_path().concat("/TONGKING"));
    return 0;
}