
#ifndef DRAW_LABEL_H
#define DRAW_LABEL_H

#include <qt/QtWidgets/qlabel.h>
#include "Line.h"
#include <sstream>

class DrawLabel : public QLabel{
    
    private:
        std::vector<Line> objects;
        double min_x;
        double max_x;
        double min_y;
        double max_y;
        int width;
        int height;
        double scale;
        double zoom;
        bool rotate;
        double x_pan;
        double y_pan;
        int gen;
    
    Q_OBJECT
    
 
    public:
    explicit DrawLabel( const QString& text ="testovaci string", QWidget * parent = 0 );
        ~DrawLabel();
        
        void resizeEvent(QResizeEvent*);
        virtual void keyPressEvent(QKeyEvent* ev);
        virtual void paintEvent(QPaintEvent*);
        void addLine(Line& l);
        void clearObjects();
        void reset();
 
    signals:
        void clicked();
        void open(std::string);
 
    protected:
        void saveSvg();
        void savePng();
        void mousePressEvent ( QMouseEvent * event ) ;
        void paint(QPainter& p);
};


#endif /*DRAW_LABEL_H*/
