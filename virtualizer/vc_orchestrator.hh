#ifndef __VC_ORCHESTRATOR_HH__
#define __VC_ORCHESTRATOR_HH__

#include <string>
#include <cstddef>
#include <istream>
// #include <vector>
// #include <map>

#include "ast.hh"
#include "vc_scanner.hh"
#include "vc_parser.tab.hh"

using namespace std;

namespace VC {

class VCOrchestrator{
public:
   VCOrchestrator() = default;

   virtual ~VCOrchestrator();
   
   /** 
    * parse - parse from a file
    * @param filename - valid string with input file
    */
   void parse(const char *const filename);
   /** 
    * parse - parse from a c++ input stream
    * @param is - istream&, valid input stream
    */
   void parse(istream &iss);

   void add_fn(Function *fn);

   ostream& print(ostream &stream);
private:

   void parse_helper(istream &stream);
   VCParser  *parser  = nullptr;
   VCScanner *scanner = nullptr;

   Program *program = new Program();

   const string red   = "\033[1;31m";
   const string blue  = "\033[1;36m";
   const string norm  = "\033[0m";
};

}

#endif
