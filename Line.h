#ifndef LINE_H
#define	LINE_H

#include <iostream>

class Line{
public:
    double start_x;
    double start_y;
    double stop_x;    
    double stop_y;

    Line(double _start_x, double _start_y, double _stop_x, double _stop_y){
        start_x = _start_x;
        start_y = _start_y;
        stop_x = _stop_x;
        stop_y = _stop_y;
    }
    
};

#endif	/* LINE_H */

