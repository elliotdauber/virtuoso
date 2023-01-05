#include <string>
#include <vector>
#include <iostream>
#include "instruction.hh"
#include "strlib.hh"

BinMathInstr::BinMathInstr(IArg *arg1, IArg *arg2) : arg1(arg1), arg2(arg2) {}
void BinMathInstr::execute(ExecutionContext &context) {
    int val = operate(arg1->get_val(context), arg2->get_val(context));
    arg1->put_val(context, val);
    context.inc_pc();
}

AddInstr::AddInstr(IArg *arg1, IArg *arg2) : BinMathInstr(arg1, arg2) {}
int AddInstr::operate(int val1, int val2) {
    return val1 + val2;
}

SubInstr::SubInstr(IArg *arg1, IArg *arg2) : BinMathInstr(arg1, arg2) {}
int SubInstr::operate(int val1, int val2) {
    return val1 - val2;
}

MulInstr::MulInstr(IArg *arg1, IArg *arg2) : BinMathInstr(arg1, arg2) {}
int MulInstr::operate(int val1, int val2) {
    return val1 * val2;
}

DivInstr::DivInstr(IArg *arg1, IArg *arg2) : BinMathInstr(arg1, arg2) {}
int DivInstr::operate(int val1, int val2) {
    //TODO: what to do if val2 == 0?
    return val1 / val2;
}

MovInstr::MovInstr(IArg *dst, IArg *src) : dst(dst), src(src) {}
void MovInstr::execute(ExecutionContext &context) {
    dst->put_val(
        context,
        src->get_val(context)
    );
    context.inc_pc();
}

JmpInstr::JmpInstr(IArg *label) : label(label) {}
void JmpInstr::execute(ExecutionContext &context) {
    context.set_pc(
        label->get_val(context)
    );
}

CondJmpInstr::CondJmpInstr(IArg *label, IArg *cond) : label(label), cond(cond) {}
void CondJmpInstr::execute(ExecutionContext &context) {
    if (compare_with_zero(cond->get_val(context))) {
        context.set_pc(label->get_val(context));
    } else {
        context.inc_pc();
    }
}

JeqInstr::JeqInstr(IArg *label, IArg *cond) : CondJmpInstr(label, cond) {}
bool JeqInstr::compare_with_zero(int val) {
    return val == 0;
}

JltInstr::JltInstr(IArg *label, IArg *cond) : CondJmpInstr(label, cond) {}
bool JltInstr::compare_with_zero(int val) {
    return val < 0;
}

JgtInstr::JgtInstr(IArg *label, IArg *cond) : CondJmpInstr(label, cond) {}
bool JgtInstr::compare_with_zero(int val) {
    return val > 0;
}

PushInstr::PushInstr(IArg *src) : src(src) {}
void PushInstr::execute(ExecutionContext &context) {
    context.stack_push(src->get_val(context));
    context.inc_pc();
}

PopInstr::PopInstr(IArg *dst) : dst(dst) {}
void PopInstr::execute(ExecutionContext &context) {
    dst->put_val(
        context,
        context.stack_pop()
    );
    context.inc_pc();
}

JalInstr::JalInstr(IArg *label) : label(label) {}
void JalInstr::execute(ExecutionContext &context) {
    context.set_ra(context.get_pc() + 1);
    context.set_pc(label->get_val(context));
}


RetInstr::RetInstr() {}
void RetInstr::execute(ExecutionContext &context) {
    context.set_pc(context.get_ra());
}

PrintInstr::PrintInstr(IArg *arg) : arg(arg) {}
void PrintInstr::execute(ExecutionContext &context) {
    cout << arg->get_val(context) << endl;
    context.inc_pc();
}

IInstr *InstrFactory::create(string& text) {
    vector<string> tokens = StringLib::tokenize(text);
    if (tokens.size() == 0) return nullptr;

    vector<IArg *> args{};
    for (size_t i = 1; i < tokens.size(); i++) {
        args.push_back(arg_factory.create(tokens[i]));
    }

    string instr_type = tokens[0];
    if (instr_type == "jmp") return new JmpInstr(args[0]);
    if (instr_type == "jeq") return new JeqInstr(args[0], args[1]);
    if (instr_type == "jlt") return new JltInstr(args[0], args[1]);
    if (instr_type == "jgt") return new JgtInstr(args[0], args[1]);
    if (instr_type == "add") return new AddInstr(args[0], args[1]);
    if (instr_type == "sub") return new SubInstr(args[0], args[1]);
    if (instr_type == "mul") return new MulInstr(args[0], args[1]);
    if (instr_type == "div") return new DivInstr(args[0], args[1]);
    if (instr_type == "mov") return new MovInstr(args[0], args[1]);
    if (instr_type == "push") return new PushInstr(args[0]);
    if (instr_type == "pop") return new PopInstr(args[0]);
    if (instr_type == "jal") return new JalInstr(args[0]);
    if (instr_type == "ret") return new RetInstr();
    if (instr_type == "pnt") return new PrintInstr(args[0]);

    return nullptr;
}
