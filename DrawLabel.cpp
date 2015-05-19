#include "DrawLabel.h"
#include <iostream>
#include <QWidget>
#include <QFileDialog>
#include <QApplication>
#include <QEvent>
#include <QMouseEvent>
#include <QString>
#include <QMessageBox>
#include <QDir>
#include <QPainter>
#include <QUrl>
#define HELP_STRING "LSystems\no\topen file\n<\tpan left\n>\tpan right\n^\tpan up\nv\tpan down\nr\trotate 90deg\n+\tzoom in\n-\tzoom out\np\tsave current canvas as png\nz\treset viewpoint\nspace\tnext generation\nh\tthis help\nq\tquit\n\ninput file:\nall symols separated by space\naxiom\nrules in form A->B \ndegree for drawing"
                     

DrawLabel::DrawLabel(const QString& text, QWidget * parent) :
QLabel(parent)
 {
    this->setText(text);
    min_x = 0;
    max_x = 0;
    min_y = 0;
    max_y = 0;
    scale = 1;
    zoom = 1;
    rotate = false;
    x_pan = 0;
    y_pan = 0;
    width = size().rwidth();
    height = size().rheight();
    gen = 0;
}

DrawLabel::~DrawLabel() {
}

void DrawLabel::reset(){
    min_x = 0;
    max_x = 0;
    min_y = 0;
    max_y = 0;
    scale = 1;
    zoom = 1;
    rotate = false;
    x_pan = 0;
    y_pan = 0; 
    width = size().rwidth();
    height = size().rheight();
    gen = 0;
}


/**
 * Store current size of the window
 * @param 
 */
void DrawLabel::resizeEvent(QResizeEvent*){
    /*std::cout << size().rheight() << std::endl;
    std::cout << size().rwidth() << std::endl;*/
    width = size().rwidth();
    height = size().rheight();
}

/**
 * Mouse button press listener
 * @param event
 */
void DrawLabel::mousePressEvent(QMouseEvent * event)
 {
    QPoint position =  event->pos();
    std::cout << "x: " << position.rx() << std::endl;
    std::cout << "y: " << position.ry() << std::endl;    
}

void DrawLabel::clearObjects(){
    objects.clear();
}

/** Add line to the drawing and update min and max coordinates*/
void DrawLabel::addLine(Line& l){
    objects.push_back(l);
    min_x = (l.start_x < min_x) ? l.start_x : min_x;
    min_x = (l.stop_x < min_x) ? l.stop_x : min_x;
    max_x = (l.start_x> max_x) ? l.start_x : max_x;
    max_x = (l.stop_x > max_x) ? l.stop_x : max_x;
    min_y = (l.start_y < min_y) ? l.start_y : min_y;
    min_y = (l.stop_y < min_y) ? l.stop_y : min_y;
    max_y = (l.start_y> max_y) ? l.start_y : max_y;
    max_y = (l.stop_y > max_y) ? l.stop_y : max_y;
}

/**
 * Record pressed key do assigned action
 * @param k
 */
void DrawLabel::keyPressEvent( QKeyEvent *k )
{
    switch ( k->key() ) {
        case 79: {                              // letter O
            QFileDialog dialog;
            QString filename;
            dialog.setOptions(QFileDialog::DontUseNativeDialog);
            dialog.setDirectory( QDir::home() );
            dialog.setFileMode(QFileDialog::ExistingFile);
            dialog.setNameFilter("Plain text (*.txt)");
            if (dialog.exec()) {
                QStringList filenames = dialog.selectedFiles();
                filename = filenames.at(0);
                emit open(filename.toStdString());
                //std::cout << filename.toStdString() << std::endl;
            }
            //std::cout << filename.toStdString() << std::endl;
            break;
        }
        case 72: // leter h
            QMessageBox::information(NULL, "Help", HELP_STRING);
            std::cout << HELP_STRING << std::endl;
            break;
        case 80: // letter p
            emit save();
            //savePng();
            break;
        case 82: // letter r
            rotate = !rotate;
            break;
        case 81: // letter q
            QApplication::exit();
            break;
        case 49: // symbol +
            zoom *= 2;
            x_pan *= 2;
            y_pan *= 2;
            std::cout << "zoom: " << zoom << std::endl;
            break;
        case 16777234: // key left
            if (rotate){
                y_pan += 30;
            }else{
                x_pan += 30;
            }
            break;
        case 16777235: // key up
            if (rotate){
                x_pan += 30;
            }else{
                y_pan += 30;
            }            
            break;
        case 16777237: // key down
            if (rotate){
                x_pan -= 30;
            }else{
                y_pan -= 30;
            }           
            break;
        case 16777236: // key right
            if (rotate){
                y_pan -= 30;
            }else{
                x_pan -= 30;
            }           
            break;
        case 45: // symbol -
            zoom /= 2; 
            x_pan /= 2;
            y_pan /= 2;
            std::cout << "zoom: " << zoom << std::endl;
            break;
        case 89: // letter z
            zoom = 1;
            x_pan = 0;
            y_pan = 0;
            break;
        case 32:case 16777220: // keys space and enter
            gen++;
            emit clicked();
            break;
        default: // any other key
            std::cout << "key pressed: " << k->key() << std::endl;
    }
}

/**
 * Saves the current canvas to png file;
 * @param path
 */
void DrawLabel::savePng(std::string& path){
    QImage img(width, height, QImage::Format_ARGB32);
    std::stringstream ss;
    ss << path;
    ss << "_" << width << "_" << height << "_" << x_pan << "_" << y_pan;
    ss << "_" << gen << "_" << zoom << "_" << rotate << ".png";
    QPainter painter;
    painter.begin(&img);
    paint(painter);
    painter.end(); 
    img.save(ss.str().c_str());
    std::cout << "File " << ss.str() << " was saved." << std::endl;
}

/**
 * Overriden method for drawing all the turtle lines
 * @param 
 */
void DrawLabel::paintEvent(QPaintEvent*){
    QPainter p(this);
    paint(p);
    update();
}

/**
 * Method paint used for drawing into the widget and into the image
 * @param p
 */
void DrawLabel::paint(QPainter& p){
    p.setPen(QPen(Qt::black, scale/20.0, Qt::SolidLine, Qt::RoundCap));
    p.setRenderHint(QPainter::Antialiasing);
    double scale_x = 0.9 / ((max_x - min_x) / width);
    double scale_y = 0.9 / ((max_y - min_y) / height);
    if (rotate){
        scale_x = 0.9 / ((max_x - min_x) / height);
        scale_y = 0.9 / ((max_y - min_y) / width);    
    }
    scale = (scale_x > scale_y) ? scale_y : scale_x;
    
    std::ostringstream os;
    os << "current pan: x: " << x_pan  << ", y: " << y_pan;            
    p.drawText(5,20,os.str().c_str());
    std::ostringstream os2;
    os2 << "current zoom: " << zoom;
    p.drawText(5,40,os2.str().c_str());
    std::ostringstream os3;
    os3 << "current generation: " << gen;
    p.drawText(5,60,os3.str().c_str());
    
    p.scale(zoom,zoom);
    double centering_x,centering_y;
    if (rotate){
        centering_x = (height-scale*(max_x - min_x))/2;
        centering_y = (width-scale*(max_y - min_y))/2;
        p.translate(centering_y + y_pan, centering_x + x_pan);
        //p.rotate(180);
    }else{
        centering_x = (width-scale*(max_x - min_x))/2;
        centering_y = (height-scale*(max_y - min_y))/2;
        p.translate(centering_x + x_pan, centering_y + y_pan);
    }
    for(unsigned int i = 0;i<objects.size();i++){
        Line& l = objects[i];
        double start_x = scale*(l.start_x-min_x);
        double start_y = scale*(l.start_y-min_y);
        double end_x =   scale*(l.stop_x-min_x);      
        double end_y =   scale*(l.stop_y-min_y);
        if (!rotate){
            p.drawLine(start_x,start_y,end_x,end_y);
        }else{
            p.drawLine(start_y,start_x,end_y,end_x);
        }
    }  
}
