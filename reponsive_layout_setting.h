#ifndef REPONSIVELAYOUTSETTING_H
#define REPONSIVELAYOUTSETTING_H

#include <QtGui>
#include <QList>
#include <QLayout>
#include <QWidget>
#include <QPushButton>




class ReponsiveLayoutSetting : public QLayout {
public:
    ReponsiveLayoutSetting(): QLayout() {}
    ~ReponsiveLayoutSetting();

    // standard functions for a QLayout
    void setGeometry(const QRect &rect);


    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);

private:
    QList<QLayoutItem*> list_;
};

#endif // REPONSIVELAYOUTSETTING_H
