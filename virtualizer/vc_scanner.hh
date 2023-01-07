#ifndef __VCSCANNER_HH__
#define __VCSCANNER_HH__

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "vc_parser.tab.hh"
#include "location.hh"

namespace VC { 

class VCScanner : public yyFlexLexer{
public:
   
   VCScanner(std::istream *in) : yyFlexLexer(in)
   {
   };
   virtual ~VCScanner() {
   };

   //get rid of override virtual function warning
   using FlexLexer::yylex;

   virtual
   int yylex( VC::VCParser::semantic_type * const lval, 
              VC::VCParser::location_type *location );
   // YY_DECL defined in vc_lexer.l
   // Method body created by flex in vc_lexer.yy.cc


private:
   /* yyval ptr */
   VC::VCParser::semantic_type *yylval = nullptr;
};

}

#endif
