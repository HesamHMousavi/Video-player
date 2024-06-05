#include "player.h"
//#include <QVBoxLayout>
#include <QPushButton>
#include <QtCore/QDir>
#include <QSlider>
#include <QMessageBox>
#include <QMediaPlayerControl>
#include <QScrollArea>
#include <QLabel>
#include <QFileDialog>
#include <QStandardPaths>
#include <QStyle>
#include <QTime>
#include <QToolButton>
#include <QMouseEvent>
#include <QVideoWidget>
#include <QDebug>





Player::Player(QWidget *parent): QWidget(parent){

    player = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    videoWidget = new VidWidget;

    prev = new QPushButton();
    prev->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    connect(prev, &QAbstractButton::clicked, this, &Player::openFile);

    next = new QPushButton();
    next->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));

    playButton = new QPushButton();
    connect(playButton, &QAbstractButton::clicked ,this, &Player::play);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));


    muteButton = new QToolButton(this);
    connect(muteButton, &QAbstractButton::clicked, this, &Player::setMute);
    muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    volSlider = new QSlider(Qt::Horizontal, this);
    volSlider->setRange(0, 100);
    volSlider->setValue(25);
    connect(volSlider, &QSlider::valueChanged, this, &Player::setVolume);

    fullScreen = new QPushButton();
    fullScreen->setText(" FULL ");

    connect(fullScreen, &QAbstractButton::clicked,this, &Player::setFullScreen);

    btns = {prev,playButton,next};

    positionSlider = new QSlider(Qt::Horizontal);
    positionSlider->setRange(0, 0);
    connect(positionSlider, &QAbstractSlider::sliderMoved,this, &Player::setPosition);

    errorLabel = new QLabel;
    errorLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    timer = new QLabel();
    timer->setText("00:00:00");

    player->setVideoOutput(videoWidget);

    connect(player, &QMediaPlayer::stateChanged,this, &Player::stateChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &Player::positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &Player::durationChanged);
    connect(player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),this, &Player::handleError);

    createWidgets();


    //DEBUG
    player->setMedia(QUrl("file:///home/csunix/ed20h3m/Documents/User-Interfaces/cwk2/comp2811-group-project/2811_cw2-master-release/videos/f.mp4"));

}


void Player::openFile(){
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Movie"));
    QStringList supportedMimeTypes = player->supportedMimeTypes();
    if (!supportedMimeTypes.isEmpty())
        fileDialog.setMimeTypeFilters(supportedMimeTypes);
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted){
        setUrl(fileDialog.selectedUrls().constFirst());
    }


}

Player::~Player(){

}

void Player::setContent(std::vector<TheButtonInfo> vids){
    infos = vids;
//    for(int i=0; i < (int)vids.size();i++){
//        buttons[i]->setIcon(*vids[i].icon);
//    }
}


void Player::setFullScreen(){
    videoWidget->setFullScreen(true);
}


void Player::play(){
    if(player->state() == QMediaPlayer::PlayingState)
        player->pause();
    else
        player->play();
}

void Player::stateChanged(QMediaPlayer::State state){

    if(state == QMediaPlayer::PlayingState)
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    else
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

}
void Player::positionChanged(qint64 position){

    positionSlider->setValue(position);
    updateDurationInfo(position / 1000);
}
void Player::setMute(){
    if(muted){
        player->setMuted(false);

        muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    }
    else{
        //mutes
        player->setMuted(true);
        volSlider->setValue(0);
        muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
    }
    muted = !muted;
}
void Player::updateDurationInfo(qint64 position){
    QString tStr;
    if (position || dur) {
        QTime currentTime((position / 3600) % 60, (position / 60) % 60,
             position % 60, (position * 1000) % 1000);
        QTime totalTime((dur / 3600) % 60, (dur / 60) % 60,
            dur % 60, (dur * 1000) % 1000);
        QString format = "mm:ss";
        if (dur > 3600)
            format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    timer->setText(tStr);
}
void Player::durationChanged(qint64 duration){
    positionSlider->setRange(0, duration);
    dur = duration / 1000;
    updateDurationInfo(0);
}
void Player::setPosition(int position){
    player->setPosition(position);
}
void Player::handleError(){

}
void Player::setUrl(const QUrl &url){
    errorLabel->setText(QString());
    setWindowFilePath(url.isLocalFile() ? url.toLocalFile() : QString());
    player->setMedia(url);
//    playButton->setEnabled(true);
}


void Player::setVolume(int volume)
{
    if(0 < volume && muted)
        setMute();
    player->setVolume(volume);
}


void Player::createWidgets(){
    layout = new QVBoxLayout();

    QWidget *nav = new QWidget();
    this->setStyleSheet("background-color:#333;");
    nav->setStyleSheet("background-color:white;border-radius:5px;");
    nav->setMaximumHeight(60);

    QHBoxLayout *con = new QHBoxLayout();
    QHBoxLayout *rt = new QHBoxLayout();
    QHBoxLayout *lf = new QHBoxLayout();

    const char* btnsName[4] = { "Home", "Settings", "Player"};
    for(int i = 0;i < 3;i++){
        QPushButton *btn = new QPushButton();
        btn->setText(btnsName[i]);
        btn->setMinimumHeight(35);
        btn->setStyleSheet("background-color:#333; border-radius: 5px; border: 1px solid black;padding:0 20px;color:white;");
        if(i == 2)
            rt->addWidget(btn);
        else
            lf->addWidget(btn);
    }


    lf->setAlignment(Qt::AlignLeft);
    rt->setAlignment(Qt::AlignRight);
    con->addLayout(lf,2);
    con->addLayout(rt,1);
    nav->setLayout(con);
    layout->addWidget(nav);
    layout->setAlignment(Qt::AlignTop);

    QHBoxLayout *vidplyer = new QHBoxLayout();
    vidplyer->addWidget(videoWidget);

    QVBoxLayout *control = new QVBoxLayout();
    QHBoxLayout *sliderLayout= new QHBoxLayout();
    sliderLayout->setAlignment(Qt::AlignRight);
    timer->setAlignment(Qt::AlignRight);
    sliderLayout->addWidget(positionSlider);
    sliderLayout->addWidget(timer);

    QHBoxLayout *playbtnscon = new QHBoxLayout();
    QHBoxLayout *playbtnsright = new QHBoxLayout();
    playbtnsright->addStretch(2);
    playbtnsright->setAlignment(Qt::AlignRight);
    QHBoxLayout *playbtnsleft = new QHBoxLayout();
    playbtnsleft->setAlignment(Qt::AlignLeft);

    for(int i = 0 ;  i < 3;i++){
        btns[i]->setMinimumWidth(40);
        btns[i]->setStyleSheet("background-color:#777; border-radius: 5px;padding:5px 0;color: #fff");
        playbtnsleft->addWidget(btns[i]);
    }
    playbtnsright->addWidget(muteButton);
    playbtnsright->addWidget(volSlider);
    fullScreen->setStyleSheet("background-color:#777; border-radius: 5px;padding:5px 0;color: #fff");
    playbtnsright->addWidget(fullScreen);

    playbtnscon->addLayout(playbtnsleft,1);
    playbtnscon->addLayout(playbtnsright,1);

    QWidget *playbtnsWidget = new QWidget();
    control->addLayout(sliderLayout);
    control->addLayout(playbtnscon);
    playbtnsWidget->setFixedHeight(80);
    playbtnsWidget->setStyleSheet("background-color:#fff;border-radius:5px");
    playbtnsWidget->setLayout(control);

    QScrollArea *scroll = new QScrollArea();
    scroll->setFixedHeight(100);
    scroll->setStyleSheet("border:none;");
    QWidget *con2 = new QWidget();
    QHBoxLayout *scrollLayout = new QHBoxLayout();



    for(int i = 0; i < 4 ;i++){
        TheButton *s = new TheButton(con2);
        buttons.push_back(s);
        s->setStyleSheet("background-color:#fff;border-radius:5px");
        s->setMinimumHeight(50);
        scrollLayout->addWidget(s);
    }

    con2->setLayout(scrollLayout);
    con2->setMinimumWidth(800);
    scroll->setWidget(con2);
    scroll->setWidgetResizable(true);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    layout->addWidget(scroll);
    this->setLayout(layout);

    layout->addLayout(vidplyer);
    layout->addWidget(playbtnsWidget);
    layout->addWidget(scroll);


    setLayout(layout);
}




