#include "arg.hh"
#include "strlib.hh"

Constant::Constant(int val) : val(val) {}
int Constant::get_val(ExecutionContext &context) {return val;}
void Constant::put_val(ExecutionContext &context, int val)  {}

Register::Register(string reg) : reg(reg) {}
int Register::get_val(ExecutionContext &context)  {return context.get_reg_val(reg);}
void Register::put_val(ExecutionContext &context, int val)  {context.put_reg_val(reg, val);}

Label::Label(string label) : label(label) {}
int Label::get_val(ExecutionContext &context)  {return context.get_lineno(label);}
void Label::put_val(ExecutionContext &context, int val)  {}

//TODO: maybe these methods should throw an error??
int NullArg::get_val(ExecutionContext &context)  { return -1; }
void NullArg::put_val(ExecutionContext &context, int val)  {}

IArg *ArgFactory::create(string &text) {
    if (text[0] == '$') {
        return new Register(text.substr(1));
    } else if (text[0] == '@') {
        return new Label(text.substr(1));
    } else if (StringLib::is_num(text)) {
        return new Constant(StringLib::to_num(text));
    } else {
        return new NullArg();
    }
}