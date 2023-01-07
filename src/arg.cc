#include "arg.hh"
#include "strlib.hh"

Constant::Constant(reg_t val) : val(val) {}
reg_t Constant::get_val(ExecutionContext &context) {return val;}
void Constant::put_val(ExecutionContext &context, reg_t val)  {}

Register::Register(string reg) : reg(reg) {}
reg_t Register::get_val(ExecutionContext &context)  {return context.get_reg_val(reg);}
void Register::put_val(ExecutionContext &context, reg_t val)  {context.put_reg_val(reg, val);}

PointerRegister::PointerRegister(string reg) : reg(reg) {}
reg_t PointerRegister::get_val(ExecutionContext &context)  {return *(reg_t *)context.get_reg_val(reg);}
void PointerRegister::put_val(ExecutionContext &context, reg_t val)  {*(reg_t *)context.get_reg_val(reg) = val;}

Label::Label(string label) : label(label) {}
reg_t Label::get_val(ExecutionContext &context)  {return context.get_lineno(label);}
void Label::put_val(ExecutionContext &context, reg_t val)  {}

//TODO: maybe these methods should throw an error??
reg_t NullArg::get_val(ExecutionContext &context)  { return -1; }
void NullArg::put_val(ExecutionContext &context, reg_t val)  {}

IArg *ArgFactory::create(string &text) {
    if (text[0] == '$') {
        return new Register(text.substr(1));
    } else if (text[0] == '*') {
        return new PointerRegister(text.substr(1));
    } else if (text[0] == '@') {
        return new Label(text.substr(1));
    } else if (StringLib::is_num(text)) {
        return new Constant(StringLib::to_num(text));
    } else {
        return new NullArg();
    }
}