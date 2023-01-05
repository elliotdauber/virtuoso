#ifndef __EXECUTOR_HH__
#define __EXECUTOR_HH__

#include <vector>
#include <string>
#include "program.hh"

using namespace std;

class IExecutor {
public:
    virtual void execute(Program &program) = 0;
};

class Executor : public IExecutor {
public:
    void execute(Program &program) override;
};

#endif