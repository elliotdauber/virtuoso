#ifndef __ARG_HH__
#define __ARG_HH__

#include <string>
#include "execution_context.hh"

using namespace std;

class IArg {
public:
    virtual int get_val(ExecutionContext &context) = 0;
    virtual void put_val(ExecutionContext &context, int val) = 0; 
};

class Constant : public IArg {
public:
    Constant(int val);
    int get_val(ExecutionContext &context) override;
    void put_val(ExecutionContext &context, int val) override;
private:
    int val;
};

class Register : public IArg {
public:
    Register(string reg);
    int get_val(ExecutionContext &context) override;
    void put_val(ExecutionContext &context, int val) override;
private:
    string reg;
};

class Label : public IArg {
public:
    Label(string label);
    int get_val(ExecutionContext &context) override;
    void put_val(ExecutionContext &context, int val) override;
private:
    string label;
};

class NullArg : public IArg {
public:
    int get_val(ExecutionContext &context) override;
    void put_val(ExecutionContext &context, int val) override;
};

class ArgFactory {
public:
    IArg *create(string &text);
};

#endif