#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

#include "vc_orchestrator.hh"

using namespace std;

int main(int argc, char *argv[]) {
   if (argc >= 2) {
      VC::VCOrchestrator orchestrator;
      orchestrator.parse(argv[1]);

      if (argc == 3) {
          ofstream outfile(argv[2]);
          orchestrator.print(outfile);
      } else {
          orchestrator.print(cout);
      }
   } else {
       cout << "usage: ./vcompiler <infile> <outfile?>" << endl;
   }
}
