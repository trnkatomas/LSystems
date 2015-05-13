
#include "utils.h"

std::string& trim(std::string& s){
    int deleted = 0;
    for(unsigned int i=0;i<s.size()-deleted;i++){
        if (s.at(i) == ' '){
            s.erase(s.begin()+i);
            deleted++;
        }
    }
    return s;
}