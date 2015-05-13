/* 
 * File:   Turtle.h
 * Author: tomas
 *
 * Created on 04 May 2015, 23:28
 */

#ifndef TURTLE_H
#define	TURTLE_H

/* Standard interpretation of symbols according to the wikipedia page*/

#define JUST_MOVE_START 97
#define JUST_MOVE_END 122
#define DRAW_START_1 65
#define DRAW_END_1 90 
#define DRAW_START_2 48
#define DRAW_END_2 57 
#define TURN_LEFT 45
#define TURN_RIGHT 43
#define TURN 124
#define STACK_PUSH 91
#define STACK_POP 93

#include "Line.h"
#include "Symbol.h"
#include <math.h>
#include <iostream>
#include <vector>

typedef struct{
    double x;
    double y;
} Point;

class Turtle{
private:
    double angle;
    double currentAngle;
    Point currentPoint;
    Point previousPoint;
    std::vector<Point> stackedPoints;
    std::vector<double> stackedAngles;

/**
 * Turtle will move by dist one
 */
    
public:
    Turtle(double angle, int x=0, int y=0);
    
    void setAngle(double angle);
    
    void restart();    
 
    //Line* makeMove(char& identifier);
    Line* makeMove(char& identifier, Line* l);
};

#endif	/* TURTLE_H */

