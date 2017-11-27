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

void Changer::analyse(SintaticTree& root){

    try{
		std::cout << "\nOriginal: ";
		print(root, false);
		search(root);
		
		srand(time(NULL));
		if(rand()%2) swapNodes(root);

		std::cout << std::endl;
		std::cout << "Changed: ";
		print(root, true);
		std::cout << std::endl;
    }
    catch( SemanticErrorException err){
        std::ostringstream ss;
        ss << "At line " << err.line_ << ": " << err.description_;
        error_info_.push_back(ss.str());
    }
}

void Changer::swapNodes(SintaticTree& node){


	struct SwapClass{
		SintaticTree* p1 = nullptr;
		SintaticTree* p2 = nullptr;
		SintaticTree s1;
		SintaticTree s2;
		int lp1;
		int lp2;

		void operator()(SintaticTree& node){

			for(uint i = 0; i < node.children_.size(); i++){
				if(node.children_[i].token_.type_ == -2 && p1 == nullptr){
					p1 = &node;
					lp1 = i;
					s1 = node.children_[i];
					break;
				}
				else if(node.children_[i].token_.type_ == -11 && p2 == nullptr){
					p2 = &node;
					lp2 = i;
					s2 = node.children_[i];
					break;
				}
			}

			for(uint i = 0; i < node.children_.size(); i++){
				operator()(node.children_[i]);
			}
		}
	};

	SwapClass myFunctor;
	myFunctor(node);

	myFunctor.p1->children_[myFunctor.lp1] = myFunctor.s2;
	myFunctor.p2->children_[myFunctor.lp2] = myFunctor.s1;

	SintaticTree t;
	t.token_ = { 31, ",", 0 };
	myFunctor.p1->children_[myFunctor.lp1].children_.push_back( t );

}

void Changer::search(SintaticTree& node){

    if (node.token_.type_ == 6){
		for( auto word_list : common_name){

			auto finded = word_list.find( node.token_.token_ );

			if(finded != word_list.end() ){

				srand(time(NULL));
				int r = rand()%word_list.size();
				auto it = word_list.begin();
				for(int i = 0; i < r; i++) it++;
				node.token_.token_ = *it;
				break;
			}
		}
	}
	else if (node.token_.type_ == 1){
		for( auto word_list : adjetive){

			auto finded = word_list.find( node.token_.token_ );

			if(finded != word_list.end() ){

				srand(time(NULL));
				int r = rand()%word_list.size();
				auto it = word_list.begin();
				for(int i = 0; i < r; i++) it++;
				node.token_.token_ = *it;
				break;
			}
		}
	}
	else if (node.token_.type_ == 20){
		for( auto word_list : verb){

			auto finded = word_list.find( node.token_.token_ );

			if(finded != word_list.end() ){

				srand(time(NULL));
				int r = rand()%word_list.size();
				auto it = word_list.begin();
				for(int i = 0; i < r; i++) it++;
				node.token_.token_ = *it;
				break;
			}
		}
	}

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

void Changer::print(SintaticTree& node, bool change){

	static bool first = true;

	if(!change){
		if(!node.token_.token_.empty())
			std::cout << node.token_.token_ << " ";
	}
	else if(!node.token_.token_.empty()){
		if(first && islower(node.token_.token_[0] ))
			std::cout << (char)toupper(node.token_.token_[0]) << node.token_.token_.substr(1) << " ";
		else if(node.token_.type_ != 30 && isupper(node.token_.token_[0] ) ){
			std::cout << (char)tolower(node.token_.token_[0]) << node.token_.token_.substr(1) << " ";
		}
		else{
			std::cout << node.token_.token_ << " ";
		}

		first = false;
	}
  
    for(uint i = 0; i < node.children_.size(); i++){
        print(node.children_[i], change);
    }
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