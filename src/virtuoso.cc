#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "virtuoso.hh"
#include "executor.hh"
#include "interpreter.hh"

void Virtuoso::run(string& filepath) {
    vector<string> lines{};
    ifstream file(filepath.c_str());
    string line;
    
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    IInterpreter *interpreter = new Interpreter();
    IExecutor *executor = new Executor();

    Program *program = interpreter->interpret(lines);
    executor->execute(*program);

    free(interpreter);
    free(executor);
}