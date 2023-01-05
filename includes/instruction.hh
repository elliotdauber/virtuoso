#ifndef __INSTRUCTION_HH__
#define __INSTRUCTION_HH__

#include <string>
#include <vector>
#include "execution_context.hh"
#include "arg.hh"

using namespace std;

class IInstr {
public:
    virtual void execute(ExecutionContext &context) = 0;
    virtual void print() {}
};

class BinMathInstr : public IInstr {
public:
    BinMathInstr(IArg *arg1, IArg *arg2);
    void execute(ExecutionContext &context) override;
    virtual int operate(int val1, int val2) = 0;
private:
    IArg *arg1, *arg2;
};

class AddInstr : public BinMathInstr {
public:
    AddInstr(IArg *arg1, IArg *arg2);
    int operate(int val1, int val2) override;
};

class SubInstr : public BinMathInstr {
public:
    SubInstr(IArg *arg1, IArg *arg2);
    int operate(int val1, int val2) override;
};

class MulInstr : public BinMathInstr {
public:
    MulInstr(IArg *arg1, IArg *arg2);
    int operate(int val1, int val2) override;
};

class DivInstr : public BinMathInstr {
public:
    DivInstr(IArg *arg1, IArg *arg2);
    int operate(int val1, int val2) override;
};

class MovInstr : public IInstr {
public:
    MovInstr(IArg *dst, IArg *src);
    void execute(ExecutionContext &context) override;
private:
    IArg *dst, *src;
};

class JmpInstr : public IInstr {
public: 
    JmpInstr(IArg *label);
    void execute(ExecutionContext &context) override;
private:
    IArg *label;
};

class CondJmpInstr : public IInstr {
public:
    CondJmpInstr(IArg *label, IArg *cond);
    void execute(ExecutionContext &context) override;
    virtual bool compare_with_zero(int val) = 0;
private:
    IArg *label, *cond;
};

class JeqInstr : public CondJmpInstr {
public: 
    JeqInstr(IArg *label, IArg *cond);
    bool compare_with_zero(int val) override;
};

class JltInstr : public CondJmpInstr {
public: 
    JltInstr(IArg *label, IArg *cond);
    bool compare_with_zero(int val) override;
};

class JgtInstr : public CondJmpInstr {
public: 
    JgtInstr(IArg *label, IArg *cond);
    bool compare_with_zero(int val) override;
};

class PushInstr : public IInstr {
public: 
    PushInstr(IArg *src);
    void execute(ExecutionContext &context) override;
private:
    IArg *src;
};

class PopInstr : public IInstr {
public: 
    PopInstr(IArg *dst);
    void execute(ExecutionContext &context) override;
private:
    IArg *dst;
};

class JalInstr : public IInstr {
public: 
    JalInstr(IArg *dst);
    void execute(ExecutionContext &context) override;
private:
    IArg *label;
};

class RetInstr : public IInstr {
public: 
    RetInstr();
    void execute(ExecutionContext &context) override;
};

class PrintInstr : public IInstr {
public: 
    PrintInstr(IArg *arg);
    void execute(ExecutionContext &context) override;
private:
    IArg *arg;
};

class InstrFactory {
public:
    IInstr *create(string& text);
private:
    ArgFactory arg_factory;
};

#endif