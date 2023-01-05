#include <iostream>
#include "interpreter.hh"
#include "strlib.hh"

using namespace std;

Program *Interpreter::interpret(vector<string>& instructions) {
    InstrFactory *factory = new InstrFactory();
    // for (size_t i = 0; i < instructions.size(); i++) {
    //     cout << instructions[i] << endl;
    // }

    Program *program = new Program();
    int curr_lineno = 0;
    for (int i = 0; i < instructions.size(); i++) {
        string line = instructions[i];
        StringLib::trim(line);
        if (line.length() == 0) continue;
        char firstchar = line[0];
        if (firstchar == '@') {
            program->add_label(line.substr(1), curr_lineno);
        } else {
            program->add_instr(factory->create(line));
            curr_lineno++;
        }
    }

    free(factory);
    return program;
}