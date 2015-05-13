#ifndef CONTROLER_H
#define CONTROLER_H

#include <QObject>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Alphabet.h"
#include "Turtle.h"
#include "DrawLabel.h"

 class Controler : public QObject
 {
     Q_OBJECT

 public:
     Controler(double turtleAngle=90);

     ~Controler();

     int value() const;
     
     void setCanvas(DrawLabel& w);
     
     void setAngle(double angle);
     
     void setAlphabet(Alphabet& a);
     
     void parse(const std::string& filename);
     

 public slots:
     void clicked();
     
     void open(std::string filename);

 signals:
    void clickedSignal();

 private:
     int m_value;
     Alphabet* alphabet;
     Turtle* t;
     DrawLabel* canvas;
     
     void useTurtle(std::string& currentString);
     
     void actionDraw();
 };

#endif /*CONTROLER_H*/
