#include "player.h"
#include <QObject>
#include <QtWidgets/QToolButton>
#include <QDebug>

Player::Player(QObject* parent)
    : QObject(parent)
{
    this->ui = new MainWindow;
    this->core = new Core;

    ui->get_playlist_view()->setModel(core->cur_playlist_model());
    ui->get_playlists_view()->setModel(core->playlists_model());

    connect(ui->get_add_file_button(), &QToolButton::clicked, [this]()
    {
        handle_file();
    });
    connect(ui->get_add_folder_button(), &QToolButton::clicked, [this]()
    {
        handle_folder();
    });
        
    connect(ui->get_play_button(), &QToolButton::clicked, [this]()
    {
        play_button();
    });

    connect(ui->get_shuffle_button(), &QToolButton::clicked, [this]()
    {
        shuffle_button();
    });

    connect(ui->get_slider_vol(), &QSlider::valueChanged, [this](int value)
    {
        core->track_controller->setVolume(value);
    });

    connect(ui->get_slider_track(), &QSlider::sliderMoved, [this](int value)
    {
        on_sldr_track_valueChanged(value);
        //core->track_controller->setVolume(value);
    });        
    
    connect(core->track_controller, &QMediaPlayer::durationChanged, ui->get_slider_track(), &QSlider::setMaximum);
    connect(core->track_controller, &QMediaPlayer::positionChanged, ui->get_slider_track(), &QSlider::setValue);
    connect(ui->get_slider_track(), &QSlider::sliderMoved, core->track_controller, &QMediaPlayer::setPosition);
        
        
    connect(ui->get_prev_button(), &QToolButton::clicked, core->cur_playlist(), &QMediaPlaylist::previous);
    connect(ui->get_next_button(), &QToolButton::clicked, core->cur_playlist(), &QMediaPlaylist::next);
    //connect(ui->get_play_button(), &QToolButton::clicked, core->track_controller, &QMediaPlayer::play);
   // connect(ui->get_pause_button(), &QToolButton::clicked, core->track_controller, &QMediaPlayer::pause);
    connect(ui->get_stop_button(), &QToolButton::clicked, core->track_controller, &QMediaPlayer::stop);
        
    connect(ui->get_playlist_view(), &QTableView::doubleClicked, [this](const QModelIndex &index){
        core->cur_playlist()->setCurrentIndex(index.row());
    });


    ui->show();
}

void Player::play_button()
{
    if(play_clicked == false)
    {
        play_clicked = true;
        core->track_controller->play();
        ui->set_pause_button();
    }
    else
    {
        play_clicked = false;
        core->track_controller->pause();
        ui->set_play_button();
    }
}

void Player::shuffle_button()
{
    switch (shuffle_clicked)
        {
        case 0:
            shuffle_clicked++;
            ui->set_shuffle_button();
            core->playlists_manager->cur_playlist->setPlaybackMode(QMediaPlaylist::Random);
            break;
        case 1:
            shuffle_clicked++;
            ui->set_repeat_button();
            core->playlists_manager->cur_playlist->setPlaybackMode(QMediaPlaylist::Loop);
           // m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
            break;
        case 2:
            shuffle_clicked++;
            ui->set_repeat_one_button();
            core->playlists_manager->cur_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
           // m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            break;
        case 3:
            shuffle_clicked = 0;
            ui->set_direct_play_button();
            core->playlists_manager->cur_playlist->setPlaybackMode(QMediaPlaylist::Sequential);
          //  m_playlist->setPlaybackMode(QMediaPlaylist::Sequential);
            break;
        }
}

//void Player::on_sldr_vol_valueChanged(int value)
//{
//    //m_player->setVolume(value)
//}

void Player::on_sldr_track_valueChanged(int value)
{
    core->track_controller->setNotifyInterval(10);
    core->track_controller->setPosition(value);
}

void Player::handle_folder()
{
    QString folder_path = ui->get_folder();
    if (folder_path != "")
        core->initialize_playlist(folder_path);
}

void Player::handle_file()
{

    QString file_path = ui->get_file();
    if (file_path != "")
        core->initialize_music(file_path);
}


// SHOULD BE IN CONSTRUCTOR. NEED TO REALISE TRACKCONTROLLER TO MAKE THIS WORK
//    connect(core->playlists_manager->, &QMediaPlaylist::currentIndexChanged, [this](int index){
//        ui->ui->currentTrack->setText(core->playlists_manager->cur_playlist_model->data(core->playlists_manager->cur_playlist_model->index(index, 0)).toString());
//    });
