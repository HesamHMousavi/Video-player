#include "reponsive_layout_setting.h"

void ReponsiveLayoutSetting::setGeometry(const QRect &r /* our layout should always fit inside r */ ) {
    QLayout::setGeometry(r);
    //store the first element in the list
//    QLayoutItem *c = list_.at(0);

    for(int i=0;i < list_.size();i++){

        QLayoutItem *item = list_.at(i);

    }
}
// following methods provide a trivial list-based implementation of the QLayout class
int ReponsiveLayoutSetting::count() const {
    return list_.size();
}

QLayoutItem *ReponsiveLayoutSetting::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ReponsiveLayoutSetting::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ReponsiveLayoutSetting::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ReponsiveLayoutSetting::sizeHint() const {
    return minimumSize();
}

QSize ReponsiveLayoutSetting::minimumSize() const {
    return QSize(320,320);
}

ReponsiveLayoutSetting::~ReponsiveLayoutSetting() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
