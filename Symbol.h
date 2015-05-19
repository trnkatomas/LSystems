#ifndef SYMBOL_H
#define	SYMBOL_H

#include <iostream>
#include <string>
#include <vector>


class Symbol{
protected:
    std::string identifier;
    
public:
    Symbol();;
    
    virtual ~Symbol(){};
    
    Symbol(char i);
    
    virtual const std::string& operator()(void) const;
    
    std::string& getIdentifier();
    
    bool operator==(const Symbol& other);
    
    friend std::ostream& operator<<(std::ostream &out, Symbol& s);
};

std::ostream& operator<<(std::ostream &out,const Symbol& s);


class Axiom: protected Symbol{
public:
    Axiom(char s);
};

class SymbolSequence: public Symbol{
private:
    std::vector<Symbol> symbols;
    
public:
    SymbolSequence();;
    
    ~SymbolSequence(){};
    
    SymbolSequence(char i);
    
    SymbolSequence(const std::string& input);   
    
    const std::string& operator()(void) const;
    
    typedef std::vector<Symbol>::iterator iterator;
    
    iterator begin();
    
    iterator end();
};

class SymbolFactory{
public:
    Symbol* createSymbol(const std::string& input);
};


#endif	/* SYMBOL_H */

