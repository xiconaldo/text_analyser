CXX := g++
CXXFLAGS := -std=c++11 -O3
CXXFLAGSDEBUG := -std=c++11 -O0 -g3

BUILDDIR := build
SRCDIR := src
INCDIR := include
EXECDIR := bin

SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(SRC:.cpp=.o)
OBJ := $(subst $(SRCDIR),$(BUILDDIR),$(OBJ))
INC := -I$(INCDIR)
EXEC := $(EXECDIR)/compiler

$(EXEC): $(OBJ)
	@mkdir -p $(EXECDIR)
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $(EXEC)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INC) $^ -c -o $@

debug:
	gdb ./bin/compiler

clean:
	rm -f build/* $(EXEC)

tree:
	@./bin/POSTagger/run-Tagger.sh > tmp.txt < input/$(IN)
	@./bin/compiler conf/grammar_v4.conf conf/sinonimos.conf tree < tmp.txt
	@rm tmp.txt

symbol:
	@./bin/POSTagger/run-Tagger.sh > tmp.txt < input/$(IN)
	@./bin/compiler conf/grammar_v4.conf conf/sinonimos.conf symbol < tmp.txt
	@rm tmp.txt

simple:
	@./bin/POSTagger/run-Tagger.sh > tmp.txt < input/$(IN)
	@./bin/compiler conf/grammar_v4.conf conf/sinonimos.conf < tmp.txt
	@rm tmp.txt
