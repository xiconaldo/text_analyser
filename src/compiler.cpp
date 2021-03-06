#include "compiler.h"

Compiler::Compiler(const std::string& grammar_file, const std::string& words_file){

	parser = new Parser( grammar_file );
	sintatic = new SintaticAnalyser( grammar_file );
	changer = new Changer(words_file);
	
}

Compiler::~Compiler(){
	
	delete parser;
	delete sintatic;
	delete changer;
	
}

void Compiler::analyse(const std::string& code){

	parser->parse(std::cin);
	std::vector< Token > tokens = parser->getTokenList();
	sintatic->analyse(tokens);
	SintaticTree& tree =  sintatic->getSintaticTree();
	changer->analyse(tree);
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
