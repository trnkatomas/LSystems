
#include "Controler.h"

/**
 * Constructor
 * @param turtleAngle
 */
Controler::Controler(double turtleAngle) {
    m_value = 0;
    t = new Turtle(turtleAngle);
    alphabet = NULL;
}

/**
 * 
 * @return current generation
 */
int Controler::value() const {
    return m_value;
}

/**
 * Sets the drawing canvas
 * @param w QtWidget
 */
void Controler::setCanvas(DrawLabel& w) {
    canvas = &w;
}

/**
 * Method for setting the alphabet
 * @param a Alphabet
 */
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
}

/**
 * Setter for angle
 * @param angle
 */
void Controler::setAngle(double angle) {
    t->setAngle(angle);
}

/**
 * Slot for saving image of current canvas
 */
void Controler::save(){
    std::string path(this->filename);
    this->canvas->savePng(path);
}

/**
 * Method for parsing the input file
 * @param filename
 */
void Controler::parse(const std::string& filename) {
    std::string line;
    std::ifstream file;
    file.open(filename.c_str(), std::ifstream::in);

    if (file.good()){
        this->filename = filename;
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
    else{
        std::cout << "Error occurred while opening the file" << std::endl;
    }
}

/**
 * Destructor
 */
Controler::~Controler() {
    delete t;
    delete alphabet;
}

/**
 * Increment generation of current alphabet and draw the current state
 */
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

/**
 * Slot for action for incrementing the alphabet
 */
void Controler::clicked() {
    m_value++;
    ++(*alphabet);
    actionDraw();
}

/**
 * Slot for action for loading the new input file
 * @param filename
 */
void Controler::open(std::string filename) {
    std::cout << filename << std::endl;
    filename = filename;
    parse(filename);
}

/**
 * After every action use turtle to interpret the current state of the alphabet
 * as an image
 * @param currentString
 */
void Controler::useTurtle(std::string& currentString) {
    t->restart();
    canvas->clearObjects();
    for (unsigned int i = 0; i < currentString.size(); i++) {
        Line* l = NULL;
        l = t->makeMove(currentString.at(i));
        if (l != NULL) {
            canvas->addLine(*l);
        }
        delete l;
    }
}
