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

    connect(ui->get_prev_button(), &QToolButton::clicked, core->cur_playlist(), &QMediaPlaylist::previous);
    connect(ui->get_next_button(), &QToolButton::clicked, core->cur_playlist(), &QMediaPlaylist::next);
    connect(ui->get_play_button(), &QToolButton::clicked, core->track_controller, &QMediaPlayer::play);
    connect(ui->get_pause_button(), &QToolButton::clicked, core->track_controller, &QMediaPlayer::pause);
    connect(ui->get_stop_button(), &QToolButton::clicked, core->track_controller, &QMediaPlayer::stop);

    connect(ui->get_playlist_view(), &QTableView::doubleClicked, [this](const QModelIndex &index){
        core->cur_playlist()->setCurrentIndex(index.row());
    });


    ui->show();
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
