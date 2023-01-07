#include <iostream>
#include <stdlib.h>
#include "execution_context.hh"

ExecutionContext::ExecutionContext(LabelMap *labels) : pc(0), stack_size(0), labels(labels) {
    vector<string> data_reg_names{
        "ra", "fp", "sp"
    };

    for (size_t i = 0; i < data_reg_names.size(); i++) {
        data_regs.insert({data_reg_names[i], 0});
    }

    set_sp((reg_t)stack);
}

int ExecutionContext::get_lineno(string& label) {return labels->get(label);}

void ExecutionContext::inc_pc() {pc++;}

void ExecutionContext::set_pc(reg_t new_pc) {pc = new_pc;}

reg_t ExecutionContext::get_pc() {return pc;}

void ExecutionContext::set_sp(reg_t new_sp) {data_regs["sp"] = new_sp;}

reg_t ExecutionContext::get_sp() {return data_regs["sp"];}

//TODO: handle $ra better (not in data_regs)
void ExecutionContext::set_ra(reg_t new_ra) {data_regs["ra"] = new_ra;}

reg_t ExecutionContext::get_ra() {return data_regs["ra"];}

void ExecutionContext::print_regs() {
    cout << "REGISTERS:" << endl;
    cout << "pc : " << pc << endl;
    map<string, reg_t>::iterator it;
    for (it = data_regs.begin(); it != data_regs.end(); it++) {
        cout << it->first << " : " << it->second << endl;
    }
}

reg_t ExecutionContext::get_reg_val(string& reg) {
        if (data_regs.count(reg)) {
            return data_regs[reg];
        }
        return 0; //TODO: throw error?
}

void ExecutionContext::put_reg_val(string& reg, reg_t val) {
    data_regs[reg] = val;
}

void ExecutionContext::stack_push(reg_t val) {
    stack[stack_size++] = val;
    set_sp(get_sp() + sizeof(reg_t));
}

reg_t ExecutionContext::stack_pop() {
    reg_t val = stack[--stack_size];
    set_sp(get_sp() - sizeof(reg_t));
    return val;
}