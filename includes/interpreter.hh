#ifndef __INTERPRETER_HH__
#define __INTERPRETER_HH__

#include <vector>
#include <string>
#include "program.hh"

using namespace std;

class IInterpreter {
public:
    virtual Program *interpret(vector<string>& instructions) = 0;
};

class Interpreter : public IInterpreter {
public:
    Program *interpret(vector<string>& instructions) override;
};

#endif