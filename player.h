#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include "vidwidget.h"
#include "the_button.h"
#include <QVBoxLayout>
#include "the_button.h"


QT_BEGIN_NAMESPACE
class QAbstractButton;
class QSlider;
class QLabel;
class QUrl;
QT_END_NAMESPACE

class Player: public QWidget

{
    Q_OBJECT

public:
    Player(QWidget *parent = nullptr);
    ~Player();

    void setUrl(const QUrl &url);
    int volume() const;
    void setContent(std::vector<TheButtonInfo> vids);

public slots:
    void play();
    void openFile();

private slots:
    void setFullScreen();
    void setVolume(int volume);
    void setMute();
    void stateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void updateDurationInfo(qint64 position);
    void handleError();

private:
    std::vector<TheButtonInfo> infos;
    std::vector<TheButton*> buttons;
    void createWidgets();
    QVBoxLayout *layout;
    std::vector<QAbstractButton*> btns;
    VidWidget *videoWidget;
    QMediaPlayer* player;
    QAbstractButton *playButton;
    QAbstractButton *prev;
    QAbstractButton *next;
    QAbstractButton *fullScreen;
    QAbstractButton *muteButton;
    QSlider *volSlider;
    QSlider *positionSlider;
    QLabel *timer;
    QLabel *errorLabel;
    qint64 dur;
    int vol;
    bool muted = false;
};

#endif // PLAYER_H
