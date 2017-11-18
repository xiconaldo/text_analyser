CXX = g++
CXXFLAGS = -std=c++11 -O3
CXXFLAGSDEBUG = -std=c++11 -O0 -g3
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = compiler

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $@

debug:
	$(CXX) $(CXXFLAGSDEBUG) *.cpp -o $(EXEC)

clean:
	rm -f *.o compiler

test:
	./POSTagger/run-Tagger.sh > output.txt < input.txt
	./compiler grammar.conf symbol < output.txt
