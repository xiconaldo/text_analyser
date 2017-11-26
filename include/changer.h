#ifndef CHANGER_H_INCLUDED
#define CHANGER_H_INCLUDED

#include "sintatic_analyser.h"
#include <unordered_set>

struct SemanticErrorException{
    uint line_;
    std::string description_;

    SemanticErrorException(uint line, const std::string& description) :
        line_(line),
        description_(description)
    {}
};

class Changer{

    const SintaticTree* aux_node = nullptr;  // verificar essa solucao
    std::vector< std::unordered_set<std::string> > common_name;
	std::vector< std::unordered_set<std::string> > adjetive;
	std::vector< std::unordered_set<std::string> > verb;

    std::vector< std::string > error_info_;

public:
    Changer(const std::string& config_file);
    void analyse(SintaticTree& root);
    void swapNodes(SintaticTree& node);
    void search(SintaticTree& root);
    void printResults();
    bool success();
    void print(SintaticTree& node);
    std::vector<std::string> split(const std::string& str, const std::string& delimiter = " ");
};

#endif