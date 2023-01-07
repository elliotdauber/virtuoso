#include <iostream>
#include "executor.hh"

using namespace std;

void Executor::execute(Program& program) {
    ExecutionContext context(program.get_labels());

    string start = "main";
    context.set_pc(context.get_lineno(start));
    context.set_ra(-1);

    while (true) {
        IInstr *instr = (program.get_instr(context.get_pc()));
        if (!instr) break;
        instr->execute(context);
    }
    // context.print_regs();
}