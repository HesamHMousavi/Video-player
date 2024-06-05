#include "home.h"
#include "responsive_layout.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
//#include <QString>
Home::Home(){

    ResponsiveLayout *lay = new ResponsiveLayout();
    QWidget *nav = new QWidget();
    this->setStyleSheet("background-color:#333;");
    nav->setStyleSheet("background-color:white;border-radius:5px;");
    nav->setObjectName("navbar");
    lay->addWidget(nav);
    const char* btns[4] = { "Home", "Settings", "Player"};
    for(int i = 0;i < 3;i++){
        QPushButton *btn = new QPushButton();
        btn->setObjectName("navBtn"+QString::number(i));
        btn->setText(btns[i]);
        btn->setStyleSheet("background-color:#333; border-radius: 5px; border: 1px solid black; color:white");
        lay->addWidget(btn);
    }


    QPushButton *btnnew = new QPushButton();
    btnnew->setText("Add new");
    btnnew->setStyleSheet("background-color:white; border-radius: 5px; border: 1px solid black; padding: 10px;margin:10px 0;color:#333;border:none;");
    btnnew->setObjectName("addNew");
    lay->addWidget(btnnew);


    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(10);
    for(int i=0; i <3;i++){
        grid->setRowStretch( i, 1 );
        for(int j = 0; j < 2;j++){
            grid->setColumnStretch( j, 1 );
            QWidget *widget = new QWidget();
            QLabel *label = new  QLabel();
            QHBoxLayout *lbllayout = new QHBoxLayout();
            label->setText("Img");
            lbllayout->setAlignment(Qt::AlignCenter);
            lbllayout->addWidget(label);
            widget->setLayout(lbllayout);
            widget->setStyleSheet("background-color:#fff;border-radius:5px;");
            widget->setMinimumHeight(120);
            grid->addWidget(widget,i,j,1,1);
        }
    }
    QWidget *gridWid = new QWidget();
    gridWid->setObjectName("gridWid");
    gridWid->setLayout(grid);
    lay->addWidget(gridWid);

    setLayout(lay);
}

