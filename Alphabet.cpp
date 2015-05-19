#include "Alphabet.h"

/** Implicit constructor*/
Alphabet::Alphabet() {

}

/**
 * Overriden operator ++ creating next generation
 * @return 
 */
Alphabet& Alphabet::operator++() {
    this->nextGeneration();
    return *this;
}

/**
 * Overriden operator () adding new symbol to the alphabet
 * @param s
 * @return 
 */
Alphabet& Alphabet::operator()(char s) {
    addSymbol(s);
    return *this;
}

/**
 * Method adding new symbol to the alphaber
 * @param id
 */
void Alphabet::addSymbol(char id) {
    std::string ids(&id, 1);
    Symbol* s = NULL;
    s = sf.createSymbol(trim(ids));
    if (rules.find(ids.at(0)) == rules.end()) {
        rules[id] = *s;
    }
    delete s;
}

/**
 * Method developing the next generation, next state of the system
 */
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


/**
 * Setter for axiom
 * @param input
 */
void Alphabet::setAxiom(std::string& input) {
    axiom = sf.createSymbol(trim(input));
    if (currentGeneration.empty()) {
        currentGeneration.push_back(*axiom);
    }
}

/**
 * Getter for axiom
 * @return 
 */
Symbol& Alphabet::getAxiom() {
    return *axiom;
}

/**
 * Getter for rules
 * @return 
 */
std::map<char, Symbol> Alphabet::getRules() {
    return rules;
}


/**
 * Method adding rules to the alphabet
 * @param key
 * @param value
 */
void Alphabet::addRule(std::string& key, std::string& value) {
    Symbol* k = NULL; Symbol* v = NULL;
    k = sf.createSymbol(trim(key));
    v = sf.createSymbol(trim(value));
    if (DEBUG_OUTPUT) {
        std::cout << "key: " << (*k) << std::endl;
        std::cout << "value: " << (*v) << std::endl;
    }
    rules[(*k)().at(0)] = *v;
    delete v;
    delete k;
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
