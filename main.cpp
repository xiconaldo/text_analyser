#include <iostream>
#include "compiler.h"

int main(int argc, char* argv[])
{

	Compiler comp{ std::string{argv[1]} };
	comp.analyse(std::string{argv[1]});
	
	if(argc > 2){
		std::cout << "\n";
		std::string arg2 = std::string{argv[2]};
	if(arg2 == "symbol")
		comp.printLexicalTable();
	else if(arg2 == "tree")
		comp.printSintaticTree();
	}

	comp.printResults();

    return 0;
}
