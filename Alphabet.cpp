#include "Alphabet.h"

Alphabet::Alphabet() {

}


Alphabet& Alphabet::operator++() {
    this->nextGeneration();
    return *this;
}


Alphabet& Alphabet::operator()(char s) {
    addSymbol(s);
    return *this;
}


void Alphabet::addSymbol(char id) {
    std::string ids(&id, 1);
    Symbol* s = NULL;
    s = sf.createSymbol(trim(ids), s);
    if (rules.find(ids.at(0)) == rules.end()) {
        rules[id] = *s;
    }
}


void Alphabet::nextGeneration() {
    std::vector<Symbol> new_gen;
    for (unsigned int i = 0; i < currentGeneration.size(); i++) {
        Symbol* s = &currentGeneration[i];
        std::string id = (*s)();
        if (DEBUG_OUTPUT)
            std::cout << id.length() << std::endl;
        for (unsigned int p = 0; p < id.length(); p++) {
            Symbol* new_s = &rules[id.at(p)];
            new_gen.push_back(*new_s);
        }
    }
    currentGeneration.clear();
    currentGeneration.swap(new_gen);
}

void Alphabet::setAxiom(std::string& input) {
    axiom = sf.createSymbol(trim(input), axiom);
    if (currentGeneration.empty()) {
        currentGeneration.push_back(*axiom);
    }
}

Symbol& Alphabet::getAxiom() {
    return *axiom;
}


std::map<char, Symbol> Alphabet::getRules() {
    return rules;
}



void Alphabet::addRule(std::string& key, std::string& value) {
    Symbol* k = NULL; Symbol* v = NULL;
    k = sf.createSymbol(trim(key), k);
    v = sf.createSymbol(trim(value), v);
    if (DEBUG_OUTPUT) {
        std::cout << "key: " << (*k) << std::endl;
        std::cout << "value: " << (*v) << std::endl;
    }
    rules[(*k)().at(0)] = *v;
}

Alphabet::iterator Alphabet::begin() {
    return currentGeneration.begin();
}

Alphabet::iterator Alphabet::end() {
    return currentGeneration.end();
}


std::ostream& operator<<(std::ostream &out,Alphabet& a){
    if (DEBUG_OUTPUT)
        out << "Current state:" << "\n\t" ;
    for (Alphabet::iterator it = a.begin();it < a.end();it++){
        out << (*it)();// << " ";
    }
    if (DEBUG_OUTPUT){
        if (&a.getAxiom()!=NULL)
            out << "\nAxiom:" <<  a.getAxiom()() << std::endl;
        if (a.getRules().size() > 0){
            out << "Rules:" << "\n\t" ;

        }
    }
    return out;
}
