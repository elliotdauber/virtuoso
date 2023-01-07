CC    ?= clang
CXX   ?= clang++

EXE = vcompiler

CDEBUG = -g -Wall

CXXDEBUG = -g -Wall

CSTD = -std=c99
CXXSTD = -std=c++14

CFLAGS = -Wno-deprecated-register -O0  $(CDEBUG) $(CSTD) 
CXXFLAGS = -Wno-deprecated-register -O0  $(CXXDEBUG) $(CXXSTD)


CPPOBJ = main vc_orchestrator ast
SOBJ =  parser lexer

FILES = $(addsuffix .cc, $(CPPOBJ))

OBJS  = $(addsuffix .o, $(CPPOBJ))

CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
				 vc_parser.tab.cc vc_parser.tab.hh \
				 location.hh position.hh \
			    stack.hh vc_parser.output parser.o \
				 lexer.o vc_lexer.yy.cc $(EXE)\

.PHONY: all
all: vcompiler

vcompiler: $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) parser.o lexer.o $(LIBS)


parser: vc_parser.yy
	bison -d -v vc_parser.yy
	$(CXX) $(CXXFLAGS) -c -o parser.o vc_parser.tab.cc

lexer: vc_lexer.l
	flex --outfile=vc_lexer.yy.cc  $<
	$(CXX)  $(CXXFLAGS) -c vc_lexer.yy.cc -o lexer.o

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)

