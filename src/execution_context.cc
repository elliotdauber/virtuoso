#include <iostream>
#include "execution_context.hh"

ExecutionContext::ExecutionContext(LabelMap *labels) : pc(0), sp(0), labels(labels) {
    vector<string> data_reg_names{
        "r0", "r1", "r2", "r3", "r4", "r5", "ra"
    };

    for (size_t i = 0; i < data_reg_names.size(); i++) {
        data_regs.insert({data_reg_names[i], 0});
    }
}

int ExecutionContext::get_lineno(string& label) {return labels->get(label);}

void ExecutionContext::inc_pc() {pc++;}

void ExecutionContext::set_pc(int new_pc) {pc = new_pc;}

int ExecutionContext::get_pc() {return pc;}

//TODO: handle $ra better (not in data_regs)
void ExecutionContext::set_ra(int new_ra) {data_regs["ra"] = new_ra;}

int ExecutionContext::get_ra() {return data_regs["ra"];}

void ExecutionContext::print_regs() {
    cout << "REGISTERS:" << endl;
    cout << "pc : " << pc << endl;
    cout << "sp : " << sp << endl;
    map<string, int>::iterator it;
    for (it = data_regs.begin(); it != data_regs.end(); it++) {
        cout << it->first << " : " << it->second << endl;
    }
}

int ExecutionContext::get_reg_val(string& reg) {
        if (data_regs.count(reg)) {
            return data_regs[reg];
        }
        return -1; //TODO: throw error?
}

void ExecutionContext::put_reg_val(string& reg, int val) {
    if (data_regs.count(reg)) {
        data_regs[reg] = val;
    }
}

void ExecutionContext::stack_push(int val) {
    stack.push_back(val);
    sp ++;
}

int ExecutionContext::stack_pop() {
    int val = stack[stack.size() - 1];
    stack.pop_back();
    sp --;
    return val;
}