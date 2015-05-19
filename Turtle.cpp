#include "Turtle.h"

Turtle::Turtle(double angle, int x, int y) {
    setAngle(angle);
    currentPoint.x = x;
    currentPoint.y = y;
}

void Turtle::setAngle(double angle) {
    if (angle > 1)
        angle = angle * M_PI / 180.0;
    currentAngle = 0;
    this->angle = angle;
    restart();
}

void Turtle::restart() {
    currentPoint.x = 0;
    currentPoint.y = 0;
    currentAngle = 0;
}

Line* Turtle::makeMove(char& identifier) {
    if ((DRAW_START_1 <= identifier &&
            DRAW_END_1 >= identifier) ||
            (DRAW_START_2 <= identifier &&
            DRAW_END_2 >= identifier)) {
        double newX = cos(currentAngle);
        double newY = sin(currentAngle);
        previousPoint.x = currentPoint.x;
        previousPoint.y = currentPoint.y;
        currentPoint.x = currentPoint.x + newX;
        currentPoint.y = currentPoint.y + newY;
        return new Line(previousPoint.x, previousPoint.y, currentPoint.x, currentPoint.y);        
    }
    if (identifier == TURN_LEFT) {
        currentAngle -= angle;        
    }
    if (identifier == TURN_RIGHT) {
        currentAngle += angle;
    }
    if (identifier == TURN) {
        currentAngle += M_PI;
    }
    if (identifier == STACK_PUSH) {
        double a = currentAngle;
        stackedAngles.push_back(a);
        Point p;
        p.x = currentPoint.x;
        p.y = currentPoint.y;
        stackedPoints.push_back(p);
    }
    if (identifier == STACK_POP) {
        currentAngle = stackedAngles.back();
        stackedAngles.pop_back();
        currentPoint = stackedPoints.back();
        stackedPoints.pop_back();
    }
    if (identifier >= JUST_MOVE_START &&
        JUST_MOVE_END >= identifier){
        double newX = cos(currentAngle);
        double newY = sin(currentAngle);
        previousPoint.x = currentPoint.x;
        previousPoint.y = currentPoint.y;
        currentPoint.x = currentPoint.x + newX;
        currentPoint.y = currentPoint.y + newY;
    }
    return NULL;
}


