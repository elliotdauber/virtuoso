%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {VC}
/**
 * bison 3.3.2 change
 * %define parser_class_name to this, updated
 * should work for previous bison versions as 
 * well. -jcb 24 Jan 2020
 */
%define api.parser.class {VCParser}

%code requires{
   namespace VC {
      class VCOrchestrator;
      class VCScanner;
   }
   
   class MathExpr;
   class Expr;
   class Function;
   class ExprList;
   class FunctionCallExpr;
   class AssignmentExpr;
   class FormalList;
   class ArgList;
   class ReturnExpr;
   class PrintExpr;
   class IfElseExpr;


// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { VCScanner       &scanner  }
%parse-param { VCOrchestrator  &orchestrator  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   #include "vc_orchestrator.hh"

#undef yylex
#define yylex scanner.yylex
}

/* %union {
  int int_val;
  std::string str_val;
  MathExpr math_expr;
  Var var;
} */

%define api.value.type variant
%define parse.assert

%token               END    0     "end of file"
%token <std::string> ID
%token               LBRACKET
%token               RBRACKET
%token               LFNBRACKET
%token               RFNBRACKET
%token               LPAREN
%token               RPAREN
%token               SEMICOLON
%token               DEF
%token               RETURN
%token               IF
%token               ELSE
%token               PRINT
%token               ASSIGN
%token <std::string> OPERATOR
%token <std::string> INT

%locations

%type <MathExpr*> math_expr
%type <Function*> function
%type <Expr*> expr
%type <ExprList*> expr_list
%type <FunctionCallExpr*> fn_call
%type <AssignmentExpr*> assignment
%type <FormalList*> formal_list
%type <ArgList*> arg_list
%type <ReturnExpr*> return_expr
%type <PrintExpr*> print_expr
%type <IfElseExpr*> if_else_expr
%type <ExprList*> else_expr

%%

program_option : END | program END;

program : function | program function;

function : DEF ID formal_list LBRACKET expr_list RBRACKET {
    orchestrator.add_fn(new Function($2, $3, $5));
};

formal_list : ID {$$ = new FormalList(new Formal($1));} 
            | formal_list ID {$$ = new FormalList($1, new Formal($2));}
            | %empty {$$ = new FormalList();}
            ;

expr_list : expr SEMICOLON {$$ = new ExprList($1);}
          | expr_list expr SEMICOLON {$$ = new ExprList($1, $2);}
          | %empty {$$ = new ExprList();}
          ;

expr : math_expr {$$ = $1;} 
     | fn_call {$$ = $1;} 
     | assignment {$$ = $1;}
     | return_expr {$$ = $1;}
     | print_expr {$$ = $1;}
     | if_else_expr {$$ = $1;}
     | LPAREN expr RPAREN {$$ = $2;}
     | INT {$$ = new Int($1);}
     | ID {$$ = new Var($1);} 
     ;

math_expr : expr OPERATOR expr {
    $$ = new MathExpr($1, new Op($2), $3);
};

fn_call : LFNBRACKET ID arg_list RFNBRACKET {
    $$ = new FunctionCallExpr($2, $3);
};

arg_list : expr {$$ = new ArgList($1);} 
            | arg_list expr {$$ = new ArgList($1, $2);}
            | %empty {$$ = new ArgList();}
            ;

assignment : ID ASSIGN expr {$$ = new AssignmentExpr(new Var($1), $3);};

return_expr : RETURN expr {$$ = new ReturnExpr($2);}

print_expr : PRINT expr {$$ = new PrintExpr($2);}

if_else_expr: IF expr LBRACKET expr_list RBRACKET else_expr {$$ = new IfElseExpr($2, $4, $6);};

else_expr: ELSE LBRACKET expr_list RBRACKET {$$ = $3;} | %empty {$$ = nullptr;};

%%


void VC::VCParser::error( const location_type &l, const std::string &err_message) {
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
