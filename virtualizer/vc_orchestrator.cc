#include <cctype>
#include <fstream>
#include <cassert>

#include "vc_orchestrator.hh"

VC::VCOrchestrator::~VCOrchestrator()
{
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
}

void 
VC::VCOrchestrator::parse(const char *const filename)
{
   assert(filename != nullptr);
   std::ifstream in_file(filename);
   if(!in_file.good())
   {
       exit(EXIT_FAILURE);
   }
   parse_helper(in_file);
   return;
}

void
VC::VCOrchestrator::parse(std::istream &stream)
{
   if(!stream.good()  && stream.eof())
   {
       return;
   }
   //else
   parse_helper(stream); 
   return;
}


void 
VC::VCOrchestrator::parse_helper(std::istream &stream)
{
   
   delete(scanner);
   try
   {
      scanner = new VCScanner(&stream);
   }
   catch(std::bad_alloc &ba)
   {
      std::cerr << "Failed to allocate scanner: (" <<
         ba.what() << "), exiting!!\n";
      exit(EXIT_FAILURE);
   }
   
   delete(parser); 
   try
   {
      parser = new VCParser((*scanner) /* scanner */, 
                                  (*this) /* orchestrator */);
   }
   catch(std::bad_alloc &ba)
   {
      std::cerr << "Failed to allocate parser: (" << 
         ba.what() << "), exiting!!\n";
      exit(EXIT_FAILURE);
   }
   const int accept(0);
   if(parser->parse() != accept)
   {
      std::cerr << "Parse failed!!\n";
   }
   return;
}


std::ostream& 
VC::VCOrchestrator::print(std::ostream &stream)
{
    //TODO: do this better (make it into a new visitor?? analysis visitor? then pass it into the codegenvisitor
    map<string, vector<string>> fn_locals{};
    for (size_t i = 0; i < program->functions.size(); i++) {
        vector<string> locals = program->functions[i]->get_locals();
        fn_locals[program->functions[i]->name] = locals;
    }
    // Visitor *v = new PrintingVisitor(stream);
    Visitor *v = new CodeGenVisitor(stream, fn_locals);
    program->accept(v);
    delete(v);
    return stream;
}

void VC::VCOrchestrator::add_fn(Function *fn) {
    program->add_fn(fn);
}