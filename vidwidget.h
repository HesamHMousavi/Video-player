#ifndef VIDWIDGET_H
#define VIDWIDGET_H

#include <QVideoWidget>
#include <QKeyEvent>
#include <QMouseEvent>

class VidWidget : public QVideoWidget
{
public:
    explicit VidWidget(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // VIDWIDGET_H
