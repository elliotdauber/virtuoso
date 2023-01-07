#ifndef __EXECUTION_CONTEXT_HH__
#define __EXECUTION_CONTEXT_HH__

#include <string>
#include <vector>
#include "label_map.hh"

using namespace std;

typedef int64_t reg_t;

class ExecutionContext {
public:
    ExecutionContext(LabelMap *labels);
    int get_lineno(string& label);

    reg_t get_reg_val(string& reg);
    void put_reg_val(string& reg, reg_t val);
    void inc_pc();
    void set_pc(reg_t new_pc);
    reg_t get_pc();
    
    void stack_push(reg_t val);
    reg_t stack_pop();

    void set_ra(reg_t new_ra);
    reg_t get_ra();

    void print_regs();
private:
    reg_t pc;
    size_t stack_size;
    reg_t stack[1000]; 
    map<string, reg_t> data_regs;
    LabelMap *labels;

    void set_sp(reg_t new_sp);
    reg_t get_sp();
};

#endif