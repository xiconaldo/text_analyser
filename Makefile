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
	$(CXX) $(CXXFLAGSDEBUG) $(INC) *.cpp -o $(EXEC)

clean:
	rm -f build/* $(EXEC)

test:
	./bin/POSTagger/run-Tagger.sh > output.txt < input.txt
	./bin/compiler conf/grammar.conf symbol < output.txt
