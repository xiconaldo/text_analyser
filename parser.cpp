#include "parser.h"

Parser::Parser(){
    type_map_.insert({{"PREP", 0}, {"CN", 1}, {"PRS", 2},
                      {"V", 3}, {"ADJ", 4}, {"PNT", 5}});

    std::string trash[] = {"PREP", "CN", "PRS", "V", "ADJ", "PNT"}; 
    token_type_strings_.insert(token_type_strings_.begin(), trash, trash+6); 
}

std::vector<std::string> Parser::split(const std::string& str, const std::string& delimiter){

    std::vector<std::string> output;
    size_t prev = 0;

    while( str.find(delimiter, prev) != std::string::npos ){
        output.push_back(str.substr(prev, str.find(delimiter, prev)-prev));
        prev = str.find(delimiter, prev)+1;
    }

    output.push_back(str.substr(prev));

    return output;
}

void Parser::parse(std::istream& in_stream){

    std::string aux_str = "";
    std::string input = "";
    std::vector< std::string > tmp;

    while(true){
        if( !(in_stream >> aux_str) ) break;
        input.append(aux_str);
        input.append(" ");
    }

    size_t prev = 0;
    size_t aux_value;
    while( (aux_value = input.find("*//", prev)) != std::string::npos){
        input.replace(aux_value, 3, "/");
        prev = aux_value;
    }

    std::string special = " ";
    std::vector<std::string> tokens;

    tokens = split(input, special);

    for( auto t : tokens){
        tmp = split(t, "/");
        if(tmp.size() < 2) continue;

        outputTokeList_.push_back( Token{ type_map_[tmp[1]], tmp[0], 0 } );
    }

}

const std::vector< Token >& Parser::getTokenList(){
	return outputTokeList_;
}

void Parser::printGeneratedTable(){

    uint space = 12;
    for( Token t : outputTokeList_)
        space = std::max( (uint)t.token_.size(), space);
    space += 3;

    std::cout << std::setw( space ) << std::left << std::setfill('-') << "|";
    std::cout << std::setw(22) << std::setfill('-') << "+";
    std::cout << std::setw(7) << std::setfill('-') << "+" << "|" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << std::setw( space ) << std::left << "| TOKEN";
    std::cout << std::setw(22) << std::left << "| CLASSIFICATION";
    std::cout << std::setw(7) << std::left << "| LINE" << "|" << std::endl;
    std::cout << std::setw( space ) << std::setfill('-') << "|";
    std::cout << std::setw(22) << std::setfill('-') << "+";
    std::cout << std::setw(7) << std::setfill('-') << "+" << "|" << std::endl;

    for( Token t : outputTokeList_){
        std::cout << std::setfill(' ');
        std::cout << std::setw(0) << std::left << "| ";
        std::cout << std::setw( space-2 ) << std::left << t.token_;
        std::cout << std::setw(0) << std::left << "| ";
        std::cout << std::setw(20) << std::left << token_type_strings_[t.type_];
        std::cout << std::setw(0) << std::left << "| ";
        std::cout << std::setw(5) << std::left << t.line_ << "|" << std::endl;
        std::cout << std::setw( space ) << std::setfill('-') << "|";
        std::cout << std::setw(22) << std::setfill('-') << "+";
        std::cout << std::setw(7) << std::setfill('-') << "+" << "|" << std::endl;
    }

    std::cout << std::endl;
}