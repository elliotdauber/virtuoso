#include <iostream>
#include <string>
#include "virtuoso.hh"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./execute <filepath>" << endl;
        return 1;
    }

    Virtuoso *v = new Virtuoso();
    string filepath = string(argv[1]);
    v->run(filepath);
}