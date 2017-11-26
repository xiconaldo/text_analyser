#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include "token.h"

class Parser{

public:
    Parser(const std::string& config_file);
    void parse(std::istream& in_stream);
    const std::vector< Token >& getTokenList();
	void printGeneratedTable();

private:
    std::vector<std::string> split(const std::string& str, const std::string& delimiter = " ");

    std::unordered_map< std::string, int > type_map_;
    std::vector< Token > outputTokeList_;
    std::vector<std::string> token_type_strings_;
    
};

#endif // PARSER