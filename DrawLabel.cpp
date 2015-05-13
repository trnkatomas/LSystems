#include "DrawLabel.h"
#include <iostream>
#include <QWidget>
#include <QFileDialog>
#include <QApplication>
#include <QEvent>
#include <QMouseEvent>
#include <QString>
#include <QDir>
#include <QPainter>
#include <QUrl>
//#include <QSvgGenerator>

DrawLabel::DrawLabel(const QString& text, QWidget * parent) :
QLabel(parent)
 {
    this->setText(text);
    //resize(800,800);
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
    //resize(800,800);
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


void DrawLabel::resizeEvent(QResizeEvent*){
    /*std::cout << size().rheight() << std::endl;
    std::cout << size().rwidth() << std::endl;*/
    width = size().rwidth();
    height = size().rheight();
}

void DrawLabel::mousePressEvent(QMouseEvent * event)
 {
    QPoint position =  event->pos();
    std::cout << "x: " << position.rx() << std::endl;
    std::cout << "y: " << position.ry() << std::endl;    
}

void DrawLabel::clearObjects(){
    objects.clear();
}

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

//void DrawLabel::addControler(Controler& c) {
//    controler = &c;
//}

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
        case 80:       // letter p
            savePng();
            break;
        case 82:       // letter r
            rotate = !rotate;
            break;
        case 81:                               // letter q
            QApplication::exit();
            break;
        case 49:
            zoom *= 2;
            x_pan *= 2;
            y_pan *= 2;
            std::cout << "zoom: " << zoom << std::endl;
            break;
        case 16777234: // doleva
            if (rotate){
                y_pan += 30;
            }else{
                x_pan += 30;
            }
            break;
        case 16777235: // nahoru
            if (rotate){
                x_pan += 30;
            }else{
                y_pan += 30;
            }            
            break;
        case 16777237: // dolu
            if (rotate){
                x_pan -= 30;
            }else{
                y_pan -= 30;
            }           
            break;
        case 16777236: // doleva//doprava
            if (rotate){
                y_pan -= 30;
            }else{
                x_pan -= 30;
            }           
            break;
        case 45:
            zoom /= 2; 
            x_pan /= 2;
            y_pan /= 2;
            std::cout << "zoom: " << zoom << std::endl;
            break;
        case 89:
            zoom = 1;
            x_pan = 0;
            y_pan = 0;
            break;
        case 32:case 16777220:
            gen++;
            emit clicked();
            break;
        default:
            std::cout << "key pressed: " << k->key() << std::endl;
    }
}


void DrawLabel::saveSvg()
{
    
    QFileDialog dialog;
    dialog.setOptions(QFileDialog::DontUseNativeDialog);
    dialog.setDirectory( QDir::home() );
    //dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("SVG file (*.svg)");
    QString path;// = dialog.selectFile();
 
    if (path.isEmpty())
        return;
 
    /*QSvgGenerator generator;
    generator.setFileName(path);
    generator.setSize(QSize(200, 200));
    generator.setViewBox(QRect(0, 0, 200, 200));
    generator.setTitle(tr("SVG Generator Example Drawing"));
    generator.setDescription(tr("An SVG drawing created by the SVG Generator "
                             "Example provided with Qt."));
    QPainter painter;    
    painter.begin(&generator);
    paint(painter);
    painter.end();*/
}

void DrawLabel::savePng()
{
    QFileDialog dialog;
    dialog.setOptions(QFileDialog::DontUseNativeDialog);
    dialog.setDirectory( QDir::home() );
    //dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Png file (*.png)");
    //dialog.setAcceptMode(QFileDialog::AcceptSave);
    QString path;
    path = dialog.getSaveFileName();
    
    if (path.isEmpty())
        return;
    //QString path = QFileDialog::getSaveFileName(this, tr("Save as image"), "", tr("PNG file (*.png)"));
    
    QImage img(width, height, QImage::Format_ARGB32);
 
    QPainter painter;
    painter.begin(&img);
    paint(painter);
    painter.end(); 
    img.save(path);
}

void DrawLabel::paintEvent(QPaintEvent*){
    QPainter p(this);
    paint(p);
    update();
}

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
