#ifndef __PROGRAM_HH__
#define __PROGRAM_HH__

#include <string>
#include "instruction.hh"

using namespace std;

class Program {
public:
    Program();
    void add_instr(IInstr *code);
    void add_label(string label, int line);
    void print();
    IInstr *get_instr(int index);
    LabelMap *get_labels();
private:
    vector<IInstr*> lines; 
    LabelMap *labels;
};

#endif