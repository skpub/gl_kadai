#include <string>
#include <fstream>

struct object {
    std::string mtl;
    void reader(std::ifstream &fs) {
    }
};

void splitter(std::ifstream &ifs) {
    object obj;
    std::string line;
    while (getline(ifs, line)) {
        if (line[0] == '#') continue;
        if (line.find("mtllib")) {
            obj.mtl = line.substr(7);
        } else {

        }
    }
}

int main(void) {

}