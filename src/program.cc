#include <string>
#include <iostream>
#include "program.hh"


Program::Program() : labels(new LabelMap()) {}

void Program::add_instr(IInstr *code) {lines.push_back(code);}

void Program::add_label(string label, int line) {labels->put(label, line);}

void Program::print() {
    cout << "labels:" << endl;
    labels->print();
}

IInstr *Program::get_instr(int index) {
    if (index >= lines.size()) return nullptr;
    return lines[index];
}

LabelMap *Program::get_labels() {return labels;}