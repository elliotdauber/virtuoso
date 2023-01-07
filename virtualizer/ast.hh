#ifndef __AST_HH__
#define __AST_HH__

#include <string>
#include <vector>
#include <map>

using namespace std;

class Visitor;

class ProgramNode {
    virtual void accept(Visitor *v) = 0;
};

class Expr : public ProgramNode {
public:
    virtual void accept(Visitor *v) = 0;
};

class Var : public Expr {
public:
    Var(string name);
    void accept(Visitor *v) override;
    string name;
};

class Int : public Expr {
public:
    Int(string val);
    void accept(Visitor *v) override;
    string val;
};

class Formal : public ProgramNode {
public:
    Formal(string name);
    void accept(Visitor *v) override;
    string name;
};

class Op : public ProgramNode {
public:
    Op(string op);
    void accept(Visitor *v) override;
    string op;
};

class FormalList : public ProgramNode {
public:
    FormalList();
    FormalList(FormalList *init_list, Formal *new_formal);
    FormalList(Formal *new_formal);
    void accept(Visitor *v) override;
    vector<Formal*> formals;
};

class ExprList : public ProgramNode {
public:
    ExprList();
    ExprList(ExprList *init_list, Expr *new_expr);
    ExprList(Expr *new_expr);
    void accept(Visitor *v) override;
    vector<Expr *> exprs;
};

class ArgList : public ProgramNode {
public:
    ArgList();
    ArgList(ArgList *init_list, Expr *new_expr);
    ArgList(Expr *new_expr);
    void accept(Visitor *v) override;
    vector<Expr *> exprs;
};

class MathExpr : public Expr {
public:
    MathExpr(Expr *left, Op *op, Expr *right);
    void accept(Visitor *v) override;
    Expr *left, *right;
    Op *op;
};

class FunctionCallExpr : public Expr {
public:
    FunctionCallExpr(string fn_name, ArgList *args);
    void accept(Visitor *v) override;
    string fn_name;
    ArgList *args;
};

class AssignmentExpr : public Expr {
public:
    AssignmentExpr(Var *assign_to, Expr *expr);
    void accept(Visitor *v) override;
    Var *assign_to; 
    Expr *expr;
};

class IfElseExpr : public Expr {
public:
    IfElseExpr(Expr *condition, ExprList *if_branch, ExprList *else_branch);
    void accept(Visitor *v) override;
    Expr *condition;
    ExprList *if_branch, *else_branch;
};

class ReturnExpr : public Expr {
public:
    ReturnExpr(Expr *expr);
    void accept(Visitor *v) override;
    Expr *expr;
};

class PrintExpr : public Expr {
public:
    PrintExpr(Expr *expr);
    void accept(Visitor *v) override;
    Expr *expr;
};

class Function : public ProgramNode {
public:
    Function(string name, FormalList *formals, ExprList *body);
    void accept(Visitor *v) override;
    vector<string> get_locals();
    bool contains_formal_with_name(string name);
    string name;
    FormalList *formals;
    ExprList *body;
};

class Program : public ProgramNode {
public:
    Program();
    Program(vector<Function *> functions);
    void add_fn(Function *fn);
    void accept(Visitor *v) override;
    vector<Function *> functions;
};

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit_assignment_expr(AssignmentExpr *assignment_expr) = 0;
    virtual void visit_fn_call_expr(FunctionCallExpr *fn_call_expr) = 0;
    virtual void visit_if_else_expr(IfElseExpr *if_else_expr) = 0;
    virtual void visit_math_expr(MathExpr *math_expr) = 0;
    virtual void visit_return_expr(ReturnExpr *return_expr) = 0;
    virtual void visit_print_expr(PrintExpr *print_expr) = 0;
    virtual void visit_var(Var *var) = 0;
    virtual void visit_formal(Formal *formal) = 0;
    virtual void visit_int(Int *i) = 0;
    virtual void visit_op(Op *op) = 0;
    virtual void visit_program(Program *program) = 0;
    virtual void visit_function(Function *function) = 0;
    virtual void visit_expr_list(ExprList *expr_list) = 0;
    virtual void visit_arg_list(ArgList *arg_list) = 0;
    virtual void visit_formal_list(FormalList *formal_list) = 0;
};

class PrintingVisitor : public Visitor {
public:
    PrintingVisitor(ostream &stream);
    void visit_assignment_expr(AssignmentExpr *assignment_expr);
    void visit_fn_call_expr(FunctionCallExpr *fn_call_expr);
    void visit_if_else_expr(IfElseExpr *if_else_expr);
    void visit_math_expr(MathExpr *math_expr);
    void visit_return_expr(ReturnExpr *return_expr);
    void visit_print_expr(PrintExpr *print_expr);
    void visit_var(Var *var);
    void visit_formal(Formal *formal);
    void visit_int(Int *i);
    void visit_op(Op *op);
    void visit_program(Program *program);
    void visit_function(Function *function);
    void visit_expr_list(ExprList *expr_list);
    void visit_arg_list(ArgList *arg_list);
    void visit_formal_list(FormalList *formal_list);
private:
    ostream &stream;
};

class ScopedVar {
public:
    enum Type {
        Formal,
        Local
    };
    ScopedVar(int index, Type type);
    int index;
    Type type;
};

class Scope {
public:
    Scope() = default;
    bool contains(string key);
    ScopedVar *get(string key);
    void put(string key, ScopedVar::Type type);
private:
    map<string, ScopedVar *> scope;
};

class ScopeStack {
public:
    ScopeStack() = default;
    void put(string key, ScopedVar::Type type);
    ScopedVar *get(string key);
    void push_scope();
    void pop_scope();
private:
    vector<Scope> scopes;
};

class CodeGenVisitor : public Visitor {
public:
    CodeGenVisitor(ostream &stream, map<string, vector<string>> fn_locals);
    void visit_assignment_expr(AssignmentExpr *assignment_expr);
    void visit_if_else_expr(IfElseExpr *if_else_expr);
    void visit_fn_call_expr(FunctionCallExpr *fn_call_expr);
    void visit_math_expr(MathExpr *math_expr);
    void visit_return_expr(ReturnExpr *return_expr);
    void visit_print_expr(PrintExpr *print_expr);
    void visit_var(Var *var);
    void visit_formal(Formal *formal);
    void visit_int(Int *i);
    void visit_op(Op *op);
    void visit_program(Program *program);
    void visit_function(Function *function);
    void visit_expr_list(ExprList *expr_list);
    void visit_arg_list(ArgList *arg_list);
    void visit_formal_list(FormalList *formal_list);
private:
    vector<string> get_fn_locals(string fn_name);
    string fresh_label(string label);
    ostream &stream;
    map<string, vector<string>> fn_locals;
    ScopeStack scopes;
    map<string, int> labels;
};

#endif

