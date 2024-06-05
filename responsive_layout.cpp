#include "responsive_layout.h"
#include <QWidget>
#include <QPushButton>

void ResponsiveLayout::setGeometry(const QRect &r /* our layout should always fit inside r */ ) {
    QLayout::setGeometry(r);
    //store the first element in the list
//    QLayoutItem *c = list_.at(0);

    for(int i=0;i < list_.size();i++){

        QLayoutItem *wid = list_.at(i);
        if(i == 0){
            QWidget *widget = static_cast<QWidget *>(wid->widget());
            if(widget->objectName() == "navbar"){
                widget->setGeometry(r.x() + 5 , r.y() + 10, r.width() - 10, 50);
            }
        }
        else if(i > 0 && i < 5){
            QPushButton *widget = static_cast<QPushButton *>(wid->widget());
            if(widget->objectName() == "navBtn0"){
                widget->setGeometry(r.x() + 10 , r.y() + 15 , 80, 40);
//                qDebug() << r.width() << endl;
            }
            else if(widget->objectName() == "navBtn1"){
                widget->setGeometry(r.x() + 95 , r.y() + 15 , 80, 40);
            }
            else if(widget->objectName() == "navBtn2"){
                widget->setGeometry(r.width() - 90, r.y() +15, 80, 40);
            }
            else if(widget->objectName() == "addNew"){
                widget->setGeometry(r.x() + 5, r.y() + 60, r.width() - 10, 60);
            }
        }
        else if(i == 5){
            QWidget *widget = static_cast<QWidget *>(wid->widget());
            if(widget->objectName() == "gridWid"){
                if(r.width() >= 375 && r.width() <= 700)
                    widget->setGeometry(r.x() , r.y() + 110, r.width(), r.height() - 110);
                else if(r.width() > 700 && r.width() <= 1000)
                    widget->setGeometry(r.x() , r.y() + 110, (r.width()/1.5) + 50, r.height() - 110);
            }
        }

    }
}
// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(320,320);
}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
