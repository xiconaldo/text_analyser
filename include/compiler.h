#ifndef COMPILER_H_INCLUDED
#define COMPILER_H_INCLUDED

// #include "lexical_analyser.h"
#include "sintatic_analyser.h"
#include "parser.h"
#include "changer.h"

class Compiler{

private:

	// LexicalAnalyser* lexical = nullptr;
	Parser* parser = nullptr;
	SintaticAnalyser* sintatic = nullptr;
	Changer* changer = nullptr;

public:

	Compiler(const std::string& grammar_file, const std::string& words_file);
	~Compiler();
	void analyse(const std::string& code);
	void printResults();
	void printLexicalTable();
	void printSintaticTree();
};

#endif
