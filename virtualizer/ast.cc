#include <istream>
#include <sstream>
#include "ast.hh"

Program::Program() : functions() {}
Program::Program(vector<Function *> functions) : functions(functions) {}
void Program::add_fn(Function *fn) {functions.push_back(fn);}
void Program::accept(Visitor *v) {v->visit_program(this);}

Var::Var(string name) : name(name) {}
void Var::accept(Visitor *v) {v->visit_var(this);}

Formal::Formal(string name) : name(name) {}
void Formal::accept(Visitor *v) {v->visit_formal(this);}

Int::Int(string val) : val(val) {}
void Int::accept(Visitor *v) {v->visit_int(this);}

Op::Op(string op) : op(op) {}
void Op::accept(Visitor *v) {v->visit_op(this);}

FormalList::FormalList(Formal *initial_formal) : formals() {
    formals.push_back(initial_formal);
}
FormalList::FormalList() : formals() {}
FormalList::FormalList(FormalList *init_list, Formal *new_formal) : formals(init_list->formals) {
    formals.push_back(new_formal);
}
void FormalList::accept(Visitor *v) {v->visit_formal_list(this);}

ExprList::ExprList(Expr *initial_expr) : exprs() {
    exprs.push_back(initial_expr);
}
ExprList::ExprList() : exprs() {}
ExprList::ExprList(ExprList *init_list, Expr *new_expr) : exprs(init_list->exprs) {
    exprs.push_back(new_expr);
}
void ExprList::accept(Visitor *v) {v->visit_expr_list(this);}

ArgList::ArgList(Expr *initial_expr) : exprs() {
    exprs.push_back(initial_expr);
}
ArgList::ArgList() : exprs() {}
ArgList::ArgList(ArgList *init_list, Expr *new_expr) : exprs(init_list->exprs) {
    exprs.push_back(new_expr);
}
void ArgList::accept(Visitor *v) {v->visit_arg_list(this);}

AssignmentExpr::AssignmentExpr(Var *assign_to, Expr *expr) : assign_to(assign_to), expr(expr) {}
void AssignmentExpr::accept(Visitor *v) {v->visit_assignment_expr(this);}

MathExpr::MathExpr(Expr *left, Op *op, Expr *right) : left(left), right(right), op(op) {}
void MathExpr::accept(Visitor *v) {v->visit_math_expr(this);}

FunctionCallExpr::FunctionCallExpr(string fn_name, ArgList *args): fn_name(fn_name), args(args) {}
void FunctionCallExpr::accept(Visitor *v) {v->visit_fn_call_expr(this);}

IfElseExpr::IfElseExpr(Expr *condition, ExprList *if_branch, ExprList *else_branch) 
    : condition(condition), if_branch(if_branch), else_branch(else_branch) {}
void IfElseExpr::accept(Visitor *v) {v->visit_if_else_expr(this);}

ReturnExpr::ReturnExpr(Expr *expr) : expr(expr) {}
void ReturnExpr::accept(Visitor *v) {v->visit_return_expr(this);}

PrintExpr::PrintExpr(Expr *expr) : expr(expr) {}
void PrintExpr::accept(Visitor *v) {v->visit_print_expr(this);}

Function::Function(string name, FormalList *formals, ExprList *body): name(name), formals(formals), body(body) {}
void Function::accept(Visitor *v) {v->visit_function(this);}
vector<string> Function::get_locals() {
    vector<string> locals;
    for (size_t i = 0; i < body->exprs.size(); i++) {
        if (AssignmentExpr *assignment = dynamic_cast<AssignmentExpr*>(body->exprs[i])) {
            string name = assignment->assign_to->name;
            if (!contains_formal_with_name(name)) {
                locals.push_back(name);
            }
        }
    }
    return locals;
}

//TODO: shouldn't need this, it's a bit of a hack
bool Function::contains_formal_with_name(string name) {
    for (size_t i = 0; i < formals->formals.size(); i++) {
        if (formals->formals[i]->name == name) {
            return true;
        } 
    }
    return false;
}


PrintingVisitor::PrintingVisitor(ostream &stream) : stream(stream) {}

void PrintingVisitor::visit_assignment_expr(AssignmentExpr *assignment_expr) {
    assignment_expr->assign_to->accept(this);
    stream << " = ";
    assignment_expr->expr->accept(this);
}
void PrintingVisitor::visit_fn_call_expr(FunctionCallExpr *fn_call_expr) {
    stream << "<";
    stream << fn_call_expr->fn_name;
    stream << " ";
    fn_call_expr->args->accept(this);
    stream << ">";
}
void PrintingVisitor::visit_if_else_expr(IfElseExpr *if_else_expr) {
    stream << "if ";
    if_else_expr->condition->accept(this);
    stream << " {" << endl;
    if_else_expr->if_branch->accept(this);
    stream << "}";
    if (if_else_expr->else_branch) {
        stream << " else {" << endl;
        if_else_expr->else_branch->accept(this);
        stream << "}";
    }
}
void PrintingVisitor::visit_return_expr(ReturnExpr *return_expr) {
    stream << "return ";
    return_expr->expr->accept(this);
}
void PrintingVisitor::visit_print_expr(PrintExpr *print_expr) {
    stream << "print ";
    print_expr->expr->accept(this);
}
void PrintingVisitor::visit_math_expr(MathExpr *math_expr)  {
    math_expr->left->accept(this);
    stream << " ";
    math_expr->op->accept(this);
    stream << " ";
    math_expr->right->accept(this);
}
void PrintingVisitor::visit_var(Var *var) {
    stream << var->name;
}
void PrintingVisitor::visit_formal(Formal *formal) {
    stream << formal->name;
}
void PrintingVisitor::visit_int(Int *i) {
    stream << i->val;
}
void PrintingVisitor::visit_op(Op *op) {
    stream << op->op;
}
void PrintingVisitor::visit_program(Program *program) {
    for (size_t i = 0; i < program->functions.size(); i++) {
        program->functions[i]->accept(this);
        stream << "\n\n";
    }
}
//TODO: should function declarations go into vars instead of just strings??
void PrintingVisitor::visit_function(Function *function) {
    stream << "def ";
    stream << function->name;
    stream << " ";
    function->formals->accept(this); 
    stream << " {\n";
    function->body->accept(this);
    stream << "}";
}
void PrintingVisitor::visit_expr_list(ExprList *expr_list) {
    for (size_t i = 0; i < expr_list->exprs.size(); i++) {
        expr_list->exprs[i]->accept(this);
        stream << ";\n";
    }
}
void PrintingVisitor::visit_arg_list(ArgList *arg_list) {
    for (size_t i = 0; i < arg_list->exprs.size(); i++) {
        arg_list->exprs[i]->accept(this);
        stream << " ";
    }
}
void PrintingVisitor::visit_formal_list(FormalList *formal_list) {
    for (size_t i = 0; i < formal_list->formals.size(); i++) {
        formal_list->formals[i]->accept(this);
        stream << " ";
    }
}




//////////////////////////////////////////////////
//                CodeGenVisitor                //
//////////////////////////////////////////////////


CodeGenVisitor::CodeGenVisitor(ostream &stream, map<string, vector<string>> fn_locals) : stream(stream), fn_locals(fn_locals), scopes() {}

void CodeGenVisitor::visit_assignment_expr(AssignmentExpr *assignment_expr) {
    assignment_expr->expr->accept(this);
    ScopedVar *scoped_var = scopes.get(assignment_expr->assign_to->name);
    if (scoped_var) {
        stream << "mov $t0 $fp" << endl;
        //TODO: how do we get the new value there?
        if (scoped_var->type == ScopedVar::Type::Formal) {
            stream << "sub $t0 " << 8 * (scoped_var->index + 1) << endl; //TODO: magic var (size of entry on stack)
        } else if (scoped_var->type == ScopedVar::Type::Local) {
            stream << "add $t0 " << 8 * scoped_var->index << endl; //TODO: magic var (size of entry on stack)
        }
        stream << "store *t0 $a0" << endl;
    } else {
        stream << "UNKNOWN VAR" << endl;
        //TODO: throw error?? should already be in scopes
    }
}
void CodeGenVisitor::visit_fn_call_expr(FunctionCallExpr *fn_call_expr) {
    //TODO: currently not using these $rN registers, could put fn args in them
    //TODO: should the jal instruction store fp and ra??
    stream << "push $r0" << endl;
    stream << "push $r1" << endl;
    stream << "push $ra" << endl;
    stream << "push $fp" << endl;
    //push args to stack
    fn_call_expr->args->accept(this);

    stream << "jal @" << fn_call_expr->fn_name << endl;

    //pop fn locals allocated from fn just called from stack
    vector<string> fn_locals = get_fn_locals(fn_call_expr->fn_name);
    for (size_t i = 0; i < fn_locals.size(); i++) {
        stream << "pop $t0" << endl;
    }

    //pop args from stack
    for (size_t i = 0; i < fn_call_expr->args->exprs.size(); i++) {
        stream << "pop $t0" << endl;
    }

    stream << "pop $fp" << endl;
    stream << "pop $ra" << endl;
    stream << "pop $r1" << endl;
    stream << "pop $r0" << endl;
}
void CodeGenVisitor::visit_if_else_expr(IfElseExpr *if_else_expr) {
    if_else_expr->condition->accept(this);
    if (if_else_expr->else_branch) {
        string else_label = fresh_label("else");
        string ifelseend_label = fresh_label("ifelseend");
        stream << "jeq " << else_label << " $a0" << endl;
        if_else_expr->if_branch->accept(this);
        stream << "jmp " << ifelseend_label << " $a0" << endl; //TODO
        stream << else_label << endl;
        if_else_expr->else_branch->accept(this);
        stream << ifelseend_label << endl;
    } else {
        string ifend_label = fresh_label("ifend");
        stream << "jeq " << ifend_label << " $a0" << endl;
        if_else_expr->if_branch->accept(this);
        stream << ifend_label << endl;
    }
}
void CodeGenVisitor::visit_return_expr(ReturnExpr *return_expr) {
    return_expr->expr->accept(this);
    stream << "ret" << endl;
}
void CodeGenVisitor::visit_print_expr(PrintExpr *print_expr) {
    print_expr->expr->accept(this);
    stream << "pnt $a0" << endl;
}
void CodeGenVisitor::visit_math_expr(MathExpr *math_expr)  {
    math_expr->left->accept(this);
    stream << "push $a0" << endl;
    math_expr->right->accept(this);
    stream << "pop $t0" << endl;
    string command;
    if (math_expr->op->op == "+") {
        command = "add";
    } else if (math_expr->op->op == "-") {
        command = "sub";
    } else if (math_expr->op->op == "*") {
        command = "mul";
    } else if (math_expr->op->op == "*") {
        command = "div";
    }
    stream << command << " $t0 $a0" << endl;
    stream << "mov $a0 $t0" << endl;
}
void CodeGenVisitor::visit_var(Var *var) {
    ScopedVar *scoped_var = scopes.get(var->name);
    if (scoped_var) {
        stream << "mov $t0 $fp" << endl;
        if (scoped_var->type == ScopedVar::Type::Formal) {
            stream << "sub $t0 " << 8 * (scoped_var->index + 1) << endl; //TODO: magic var (size of entry on stack)
        } else if (scoped_var->type == ScopedVar::Type::Local) {
            stream << "add $t0 " << 8 * scoped_var->index << endl;
        }
        stream << "load $a0 *t0" << endl;
    } else {
        //TODO: error?
        stream << "UNKNOWN VAR" << endl;
    }
}
void CodeGenVisitor::visit_formal(Formal *formal) {
    // stream << formal->name;
    //ADD FORMAL TO SCOPE (TODO check order with regards to how args are pushed to stack)
    scopes.put(formal->name, ScopedVar::Type::Formal);
}
void CodeGenVisitor::visit_int(Int *i) {
    stream << "mov $a0 " << i->val << endl;
}
void CodeGenVisitor::visit_op(Op *op) {
    // stream << op->op;
}
void CodeGenVisitor::visit_program(Program *program) {
    for (size_t i = 0; i < program->functions.size(); i++) {
        program->functions[i]->accept(this);
        stream << endl << endl;
    }
}
//TODO: should function declarations go into vars instead of just strings??
void CodeGenVisitor::visit_function(Function *function) {
    stream << "@" << function->name << endl;
    stream << "mov $fp $sp" << endl;
    //create a new scope
    scopes.push_scope();
    function->formals->accept(this);

    //figure out how many locals are created and push the locals (init to 0) to the stack
    vector<string> locals = get_fn_locals(function->name);
    for (size_t i = 0; i < locals.size(); i++) {
        if (!scopes.get(locals[i])) {
            scopes.put(locals[i], ScopedVar::Type::Local);
            stream << "push 0" << endl;
        }
    }
    
    function->body->accept(this);

    //todo: pop args off stack (but must do it before printing "ret")

    //remove function scope
    scopes.pop_scope();
}
void CodeGenVisitor::visit_expr_list(ExprList *expr_list) {
    for (size_t i = 0; i < expr_list->exprs.size(); i++) {
        expr_list->exprs[i]->accept(this);
    }
}

//TODO: traverse backwards or forwards?
void CodeGenVisitor::visit_arg_list(ArgList *arg_list) {
    for (int i = arg_list->exprs.size() - 1; i >= 0; i--) {
        arg_list->exprs[i]->accept(this);
        stream << "push $a0" << endl;
    }
}
void CodeGenVisitor::visit_formal_list(FormalList *formal_list) {
    for (size_t i = 0; i < formal_list->formals.size(); i++) {
        formal_list->formals[i]->accept(this);
    }
}

vector<string> CodeGenVisitor::get_fn_locals(string fn_name) {
    if (fn_locals.count(fn_name)) {
        return fn_locals[fn_name];
    }
    //TODO: throw error? this means we are calling a function that doesn't exist
    return {};
}

string CodeGenVisitor::fresh_label(string label) {
    if (!labels.count(label)) {
        labels[label] = 0;
    }
    ostringstream str;
    str << "@" << label << labels[label]++;
    return str.str();
}
//////////////////////////////////////////////////
//                     ScopeStack               //
//////////////////////////////////////////////////

//TODO: free memory in these data structures
ScopedVar::ScopedVar(int index, Type type) : index(index), type(type) {}

bool Scope::contains(string key) {return scope.count(key);}
ScopedVar *Scope::get(string key) {return scope[key];}
void Scope::put(string key, ScopedVar::Type type) {scope[key] = new ScopedVar(scope.size(), type);}

void ScopeStack::put(string key, ScopedVar::Type type) {
    scopes[scopes.size() - 1].put(key, type);
}
ScopedVar *ScopeStack::get(string key) {
    // for (int i = scopes.size() - 1; i >= 0; i--) {
    //     if (scopes[i].contains(key)) {
    //         return scopes[i].get(key);
    //     }
    // }
    if (scopes[scopes.size()-1].contains(key)) {
        return scopes[scopes.size()-1].get(key);
    }
    return nullptr;
};
void ScopeStack::push_scope() {scopes.push_back(Scope());}
void ScopeStack::pop_scope() {scopes.pop_back();}