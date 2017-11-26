#include "changer.h"

Changer::Changer(const std::string& config_file){

	std::ifstream config{ config_file };
	if(!config.is_open()){
		std::cerr << "Can't open file " << config_file;
	}

	std::string line;
	std::vector< std::string > aux_words;

	getline(config, line);
	if(line.substr(0, 2) != "#s") return;

    while( getline(config, line) ){
        
		if(line.back() < 31) line.pop_back();
		if(line.substr(0, 2) == "#a") break;

		aux_words = split(line, " ");
		std::unordered_set<std::string> comon_name{ aux_words.begin(), aux_words.end() };

		common_name.push_back(comon_name);
    }

	while( getline(config, line) ){
        
		if(line.back() < 31) line.pop_back();
		if(line.substr(0, 2) == "#v") break;

		aux_words = split(line, " ");
		std::unordered_set<std::string> comon_name{ aux_words.begin(), aux_words.end() };

		adjetive.push_back(comon_name);
    }

	while( getline(config, line) ){
        
		if(line.back() < 31) line.pop_back();

		aux_words = split(line, " ");
		std::unordered_set<std::string> comon_name{ aux_words.begin(), aux_words.end() };

		verb.push_back(comon_name);
    }

	// std::cout << "\n\nSubstantivos:\n\n";
	// for( auto x : common_name){
	// 	for( auto y : x){
	// 		std::cout << y << " ";
	// 	}
	// 	std::cout << "##########" << std::endl;
	// }

	// std::cout << "\n\nAdjetivos:\n\n";
	// for( auto x : adjetive){
	// 	for( auto y : x){
	// 		std::cout << y << " ";
	// 	}
	// 	std::cout << "##########" << std::endl;
	// }

	// std::cout << "\n\nVerbos:\n\n";
	// for( auto x : verb){
	// 	for( auto y : x){
	// 		std::cout << y << " ";
	// 	}
	// 	std::cout << "##########" << std::endl;
	// }

	config.close();

}

void Changer::analyse(const SintaticTree& root){

    try{
        search(root);
    }
    catch( SemanticErrorException err){
        std::ostringstream ss;
        ss << "At line " << err.line_ << ": " << err.description_;
        error_info_.push_back(ss.str());
    }

}

void Changer::search(const SintaticTree& node){

    if (node.token_.type_ == 6){
		for( auto word_list : common_name){

			auto finded = word_list.find( node.token_.token_ );

			if(finded != word_list.end() ){
				
				//node.token_.token_ = (*finded);

				break;
			}

		}
    }

	if(!node.token_.token_.empty())
		std::cout << node.token_.token_.substr(0) << " ";
    
  
    for(uint i = 0; i < node.children_.size(); i++){
        search(node.children_[i]);
    }

}

void Changer::printResults(){
	if( !error_info_.empty() ){
        std::cout << "Semantic error(s) detected:" << std::endl;
        for( std::string err : error_info_)
            std::cout << err << std::endl;
    }
    std::cout << std::endl;
}

bool Changer::success(){
	return error_info_.empty();
}

std::vector<std::string> Changer::split(const std::string& str, const std::string& delimiter){

    std::vector<std::string> output;
    size_t prev = 0;

    while( str.find(delimiter, prev) != std::string::npos ){
        output.push_back(str.substr(prev, str.find(delimiter, prev)-prev));
        prev = str.find(delimiter, prev)+1;
    }

    output.push_back(str.substr(prev));

    return output;
}