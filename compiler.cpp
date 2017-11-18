#include "compiler.h"

Compiler::Compiler(const std::string& grammar_file){

	parser = new Parser;
	sintatic = new SintaticAnalyser( grammar_file );
	
}

Compiler::~Compiler(){
	
	delete parser;
	delete sintatic;
	
}

void Compiler::analyse(const std::string& code){

	parser->parse(std::cin);
	std::vector< Token > tokens = parser->getTokenList();
	sintatic->analyse(tokens);
	const SintaticTree& tree =  sintatic->getSintaticTree();
}

void Compiler::printResults(){

	if( sintatic->success() ){
		std::cout << "\nSuccessfully compilation!" << std::endl << std::endl;
		return;
	}

	std::cout << "\nCompilation failed!";
	sintatic->printResults();
}

void Compiler::printLexicalTable(){
	parser->printGeneratedTable();
}

void Compiler::printSintaticTree(){
	sintatic->printTree();
}
