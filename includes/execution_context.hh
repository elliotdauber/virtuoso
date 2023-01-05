#ifndef __EXECUTION_CONTEXT_HH__
#define __EXECUTION_CONTEXT_HH__

#include <string>
#include <vector>
#include "label_map.hh"

using namespace std;

class ExecutionContext {
public:
    ExecutionContext(LabelMap *labels);
    int get_lineno(string& label);

    int get_reg_val(string& reg);
    void put_reg_val(string& reg, int val);
    void inc_pc();
    void set_pc(int new_pc);
    int get_pc();
    
    void stack_push(int val);
    int stack_pop();

    void set_ra(int new_ra);
    int get_ra();

    void print_regs();
private:
    int pc;
    int sp;
    vector<int> stack;
    map<string, int> data_regs;
    LabelMap *labels;
};

#endif