#include "Symbol.h"

Symbol::Symbol() {
}

Symbol::Symbol(char i) {
    this->identifier = i;
}

const std::string& Symbol::operator()() const {
    return identifier;
}

/**
 * Overrinden operator allowing symbols to be compared directly according to 
 * their identifier
 * @param other
 * @return 
 */
bool Symbol::operator==(const Symbol& other) {
    const std::string s = other();
    return identifier.compare(s) == 0;
}


std::string& Symbol::getIdentifier() {
    return identifier;
}


SymbolSequence::SymbolSequence() {
}

SymbolSequence::iterator SymbolSequence::begin(){
    return symbols.begin();
}

SymbolSequence::iterator SymbolSequence::end(){
    return symbols.end();
}    


SymbolSequence::SymbolSequence(char i) {
    Symbol s(i);
    symbols.push_back(s);
    /*string identifier;*/
    identifier = s();
}

const std::string& SymbolSequence::operator()(void) const{
    return identifier; 
}


SymbolSequence::SymbolSequence(const std::string& input) {
    for (unsigned int i = 0; i < input.size(); i++) {
        Symbol s(input.at(i));
        symbols.push_back(s);
    }
    std::string s;
    for (unsigned int i = 0; i < symbols.size(); i++) {
        s += symbols[i]();
    }
    this->identifier = s;
}


Axiom::Axiom(char s) {
    std::string id(s, 1);
    this->identifier = id; //();
}

Symbol* SymbolFactory::createSymbol(const std::string& input) {
    if (input.length() == 1) {
        return new Symbol(input.at(0));
    } else {
        return new SymbolSequence(input);
    }
}


std::ostream& operator<<(std::ostream &out,const Symbol& s){
    out << s();
    return out;
};
