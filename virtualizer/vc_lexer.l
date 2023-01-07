%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */ 
#include "vc_scanner.hh"
#undef  YY_DECL
#define YY_DECL int VC::VCScanner::yylex( VC::VCParser::semantic_type * const lval, VC::VCParser::location_type *loc )

/* typedef to make the returns for the tokens shorter */
using token = VC::VCParser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="VC::VCScanner"
%option noyywrap
%option c++

%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
            /* int n = 0; */
%}

"def"       {return(token::DEF);}

"return"       {return(token::RETURN);}

"print"       {return(token::PRINT);}

[a-zA-Z]+   {
               /**
                * Section 10.1.5.1 of the 3.0.2 Bison Manual says the 
                * following should work:
                * yylval.build( yytext );
                * but it doesn't.
                * ref: http://goo.gl/KLn0w2
                */
               yylval->build< std::string >( yytext );
               return( token::ID );
            }

[0-9]+      {
                yylval->build<std::string>( yytext );
                return(token::INT);
            }

[ \t\f\v\r]+ {}

\n          {
               // Update line number
               loc->lines();
            }

\{          {return(token::LBRACKET);}

\}          {return(token::RBRACKET);}

\<           {return(token::LFNBRACKET);}

\>           {return(token::RFNBRACKET);}

\;          {return(token::SEMICOLON);}

\=           {return(token::ASSIGN);}

[\+\-\*\/]  {
                yylval->build<std::string>(yytext);
                return(token::OPERATOR);
            }
%%

