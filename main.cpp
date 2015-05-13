/*
 * File:   main.cpp
 * Author: tomas
 *
 * Created on 29 April 2015, 18:01
 */

/**
 * GUI includes
 */
#include <QApplication>
#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGui>
#include "BorderLayout.h"
/**
 * STL includes
 */
#include <string>
#include <iostream>
#include <sstream>

/**
 * Local includes
 */
#include "DrawLabel.h"
#include "Alphabet.h"
#include "Controler.h"

#define DEBUG(X) (cout << #X << ": " << (X) << "\n")

using namespace std;

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    // create and show your widgets here
    QWidget* w = new QWidget;
    //w->setFixedSize(100,100);
    w->resize(300,400);
    w->setMinimumSize(300,400);
    BorderLayout* layout = new BorderLayout;
    layout->setContentsMargins(0,0,0,0);
    
    DrawLabel c;
    QLabel* label = &c; //new QLabel;
    label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    label->setContentsMargins(0,0,0,0);
    label->setStyleSheet("background-color:white");
    label->setText("test");
    layout->addWidget(label, BorderLayout::Center);
    QLabel* help = new QLabel;
    help->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    help->setContentsMargins(0,0,0,0);
    help->setText("o - open, r - rotate, q - quit, ->,space,Enter - next generation");
    layout->addWidget(help, BorderLayout::South);
    w->setLayout(layout);
    w->show();
    
    QPicture pi;
    c.setPicture(pi);
     
    Controler contr;
    contr.setCanvas(c);
    QObject::connect(&c, SIGNAL(clicked()),
                      &contr, SLOT(clicked()));
    QObject::connect(&c, SIGNAL(open(std::string)),
                      &contr, SLOT(open(std::string)));
    c.setFocus();
    //c.grabKeyboard();
    return app.exec();
}
