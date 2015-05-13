
#include "Controler.h"

Controler::Controler(double turtleAngle) {
    m_value = 0;
    t = new Turtle(turtleAngle);
    alphabet = NULL;
}

int Controler::value() const {
    return m_value;
}

void Controler::setCanvas(DrawLabel& w) {
    canvas = &w;
}

void Controler::setAlphabet(Alphabet& a) {
    if (this->alphabet != NULL) {
        //delete alphabet;
    }
    this->alphabet = &a;
    std::stringstream ss;
    ss << *alphabet;
    std::string curStr = ss.str();
    useTurtle(curStr);
    std::cout << m_value << ": " << ss.str() << std::endl;
    //std::cout << m_value << ": " << *alphabet << std::endl;
}

void Controler::setAngle(double angle) {
    t->setAngle(angle);
}

void Controler::parse(const std::string& filename) {
    std::string line;
    std::ifstream file;
    file.open(filename.c_str(), std::ifstream::in);

    /* Process symbols of alphabet */
    std::getline(file, line);
    std::istringstream symbols(line);
    char s;
    Alphabet *a = new Alphabet();
    while (symbols >> s) {
        (*a)(s);
    }

    /* Get axiom */
    std::getline(file, line);
    (*a).setAxiom(line);

    /* Process rewriting rules */
    while (std::getline(file, line)) {
        std::string delimiter = "->";
        int index = line.find(delimiter);
        if (index < 0) {
            break;
        }
        std::string key = line.substr(0, index);
        std::string value = line.substr(index + delimiter.length());
        (*a).addRule(key, value);
    }

    /* Read angle */
    double angle = std::atof(line.c_str());

    setAlphabet(*a);
    setAngle(angle);
    canvas->reset();
    m_value = 0;
    actionDraw();
}

Controler::~Controler() {
    delete t;
    delete alphabet;
}

void Controler::actionDraw(){
    std::stringstream ss;
    ss << (*alphabet);
    std::string curStr = ss.str();
    useTurtle(curStr);
    if (ss.str().size() < 100) {
        std::cout << m_value << ": " << ss.str() << std::endl;
    } else {
        std::cout << m_value << ": output too long, has " << ss.str().size() << " chars" << std::endl;
    }
}

void Controler::clicked() {
    m_value++;
    ++(*alphabet);
    actionDraw();
}

void Controler::open(std::string filename) {
    std::cout << filename << std::endl;
    parse(filename);
}

void Controler::useTurtle(std::string& currentString) {
    t->restart();
    canvas->clearObjects();
    for (unsigned int i = 0; i < currentString.size(); i++) {
        Line* l = NULL;
        l = t->makeMove(currentString.at(i), l);
        if (l != NULL) {
            canvas->addLine(*l);
        }
        delete l;
    }
}
