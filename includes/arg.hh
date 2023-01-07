#ifndef __ARG_HH__
#define __ARG_HH__

#include <string>
#include "execution_context.hh"

using namespace std;

class IArg {
public:
    virtual reg_t get_val(ExecutionContext &context) = 0;
    virtual void put_val(ExecutionContext &context, reg_t val) = 0; 
};

class Constant : public IArg {
public:
    Constant(reg_t val);
    reg_t get_val(ExecutionContext &context) override;
    void put_val(ExecutionContext &context, reg_t val) override;
private:
    reg_t val;
};

class Register : public IArg {
public:
    Register(string reg);
    reg_t get_val(ExecutionContext &context) override;
    void put_val(ExecutionContext &context, reg_t val) override;
private:
    string reg;
};

class PointerRegister : public IArg {
public:
    PointerRegister(string reg);
    reg_t get_val(ExecutionContext &context) override;
    void put_val(ExecutionContext &context, reg_t val) override;
private:
    string reg;
};

class Label : public IArg {
public:
    Label(string label);
    reg_t get_val(ExecutionContext &context) override;
    void put_val(ExecutionContext &context, reg_t val) override;
private:
    string label;
};

class NullArg : public IArg {
public:
    reg_t get_val(ExecutionContext &context) override;
    void put_val(ExecutionContext &context, reg_t val) override;
};

class ArgFactory {
public:
    IArg *create(string &text);
};

#endif