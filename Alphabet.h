/* 
 * File:   Alphabet.h
 * Author: tomas
 *
 * Created on 02 May 2015, 23:24
 */

#ifndef ALPHABET_H
#define	ALPHABET_H

#include "utils.h"
#include "Symbol.h"
#include <algorithm>
#include <map>
#include <vector>
#define DEBUG(X) (cout << #X << ": " << (X) << "\n")
#define DEBUG_OUTPUT 0

/**
 * According to the 
 * http://cs.wikipedia.org/w/index.php?title=L-syst%C3%A9m#Interpretace_symbol.C5.AF
 * */

class Alphabet{

private:
    std::map<char,Symbol> rules;
    Symbol* axiom = NULL;
    std::vector<Symbol> currentGeneration;
    SymbolFactory sf;

public:
    Alphabet();
    
    ~Alphabet(){
        delete axiom;        
    }
    
    void setAxiom(std::string& input);
    
    Symbol& getAxiom();
        
    std::map<char,Symbol> getRules();
    
    void addSymbol(char id);
    
    void nextGeneration();
    
    Alphabet& operator++();
    
    Alphabet& operator()(char s);        
    
    void addRule(std::string& key, std::string& value);
    
    typedef std::vector<Symbol>::iterator iterator;
    
    iterator begin();
    
    iterator end();
    
};

std::ostream& operator<<(std::ostream &out,Alphabet& a);


#endif	/* ALPHABET_H */

