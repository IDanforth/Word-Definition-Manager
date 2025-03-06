#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<cctype>
#include<fstream>

class word{
    public:
        std::vector<std::string> definitions;
        void erase_def(int index, bool all){
            if(all){
                definitions.clear();
                return;
            }
            if(index - 1 < definitions.size()){
                definitions.erase(definitions.begin() + index - 1);
            }else{
                std::cout << "No definition to erase\n";
            }
        }
        void list_def(){
            int counter = 1;
            for(std::string def : definitions){
                std::cout << counter << ": " << def << '\n';
                counter++;
            }
        }
};

std::string ignore_case(std::string input){
    std::string output = "";
    for(char chr : input){
        output += std::toupper(chr);
    }
    return output;
}

//reads number of words, number of definitions for each word, the word itself, and each definition
std::map<std::string, word*> read_in(){
    std::ifstream inputfile;
    inputfile.open("WordSave.txt");
    int words, defs;
    inputfile >> words;
    std::string ward;
    std::map<std::string, word*> map;
    for(int i = 0; i < words; i++){
        inputfile >> defs >> ward; inputfile.ignore();
        word* name = new word;
        std::string def;
        for(int j = 0; j < defs; j++){
            std::getline(inputfile, def);
            name->definitions.push_back(def);
        }
        map[ward] = name;
    }
    inputfile.close();
    return map;
}

//outputs number of words, number of definitions for each word, the word itself, and each definition
void read_out(std::map<std::string, word*> map){
    std::ofstream outputfile;
    outputfile.open("WordSave.txt");
    outputfile << map.size() << '\n';
    for(auto pair : map){
        outputfile << pair.second->definitions.size() << ' ' << pair.first << '\n';
        for(int i = 0; i < pair.second->definitions.size(); i++){
            outputfile << pair.second->definitions[i] << '\n';
        }
    }
    outputfile.close();
}

bool contains_letter(std::string string){
    bool letter = false;
    for(char chr : string){
        if(std::isalpha(chr)){
            letter = true;
        }
    }
    return letter;
}

int main(){
    std::string input;
    std::map<std::string, word*> words = read_in();
    std::cout << "Words saved: " << words.size() << '\n';
    //main loop for each word entry
    while(std::getline(std::cin, input)){
        input = ignore_case(input);
        if(input == "PROGRAM_EXIT"){
            read_out(words);
            std::cout << "Words saved: " << words.size() << '\n';
            break;
        }
        if(input == "PROGRAM_LIST"){
            int num = 0;
            for(auto pair : words){
                num++;
                std::cout << num << ' ' << pair.first << '\n';
            }
            continue;
        }
        //if word does not have definitions, meaning word does not exist, it will create a new word
        if(words[input] == nullptr){
            word* temp = new word;
            std::string def;
            std::cout << "Give definitions. When finished type 'done'\n";
            //loop for getting definitions
            while(std::getline(std::cin, def)){
                if(ignore_case(def) == "DONE"){
                    break;
                }
                temp->definitions.push_back(def);
            }
            //resets the word if no defs found
            if(temp->definitions.size() != 0){
                words[input] = temp;
            }else{
                words.erase(input);
            }
        }else{
            //lists known definitions
            words[input]->list_def();
            std::string req;
            //loop for grabbing requests
            while(std::getline(std::cin, req)){
                if(ignore_case(req) == "EXIT"){
                    break;
                }
                //returns a vector of requests. Should be the request and a number
                std::vector<std::string> reqs = {};
                std::string strtopush = "";
                for(char chr : req){
                    if(chr == ' '){
                        reqs.push_back(strtopush);
                        strtopush = "";
                    }else{
                        strtopush += chr;
                    }
                }
                if(!strtopush.empty()){
                    reqs.push_back(strtopush);
                }
                //runs the requests
                if(reqs.size() == 0){
                    continue;
                }else if(reqs.size() > 2){
                    std::cout << "Invalid Request\n";
                }else{
                    //either erases all or the given definition's index. will not print if out of range or the index is a string
                    if(ignore_case(reqs[0]) == "ERASE" && reqs.size() == 2){
                        if(ignore_case(reqs[1]) == "ALL"){
                            words[input]->erase_def(0, true);
                            continue;
                        }
                        if(contains_letter(reqs[1])){
                            std::cout << "Invalid Request\n";
                            continue;
                        }
                        int index = std::stoi(reqs[1]);
                        words[input]->erase_def(index, false);
                    //will list all definitions. Will only print if list is the only word
                    }else if(ignore_case(reqs[0]) == "LIST"){
                        if(reqs.size() > 1){
                            std::cout << "Invalid Request\n";
                            continue;
                        }
                        words[input]->list_def();
                    //will add n number of definitions. will not print if n is a string
                    }else if(ignore_case(reqs[0]) == "ADD" && reqs.size() == 2){
                        if(contains_letter(reqs[1])){
                            std::cout << "Invalid Request\n";
                            continue;
                        }
                        for(int i = 0; i < std::stoi(reqs[1]); i++){
                            std::string added_input;
                            std::cin >> added_input;
                            words[input]->definitions.push_back(added_input);
                        }
                    }else{
                        std::cout << "Invalid Request\n";
                    }
                }
            }
            //resets the word if no defs found
            if(words[input]->definitions.size() == 0){
                words.erase(input);
            }
        }
    }
    return 0;
}