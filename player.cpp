#include "player.h"
#include <QObject>
#include <QtWidgets/QToolButton>
#include <QDebug>

Player::Player(QObject* parent)
: QObject(parent)
{
    this->ui = new MainWindow;
    this->core = new Core;

    ui->get_playlists_view()->setModel(core->playlists_model());
    ui->get_playlist_view()->setModel(core->cur_playlist_model());

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

    connect(ui->get_addp_button(), &QToolButton::clicked, [this]()
    {
        addp_button();
    });

    connect(ui->get_shuffle_button(), &QToolButton::clicked, [this]()
    {
        shuffle_button();
    });

    connect(ui->get_sort_button(), &QToolButton::clicked, [this]()
    {
        sort_button();
    });

    connect(ui->get_slider_vol(), &QSlider::valueChanged, [this](int value)
    {
        core->track_controller->setVolume(value);
    });

    connect(core->track_controller, &QMediaPlayer::durationChanged, ui->get_slider_track(), &QSlider::setMaximum);
    connect(core->track_controller, &QMediaPlayer::positionChanged, ui->get_slider_track(), &QSlider::setValue);
    connect(ui->get_slider_track(), &QSlider::sliderMoved, core->track_controller, &QMediaPlayer::setPosition);

    connect(ui->get_prev_button(), &QToolButton::clicked, core->cur_playlist(), &QMediaPlaylist::previous);
    connect(ui->get_next_button(), &QToolButton::clicked, core->cur_playlist(), &QMediaPlaylist::next);
    connect(ui->get_stop_button(), &QToolButton::clicked, core->track_controller, &QMediaPlayer::stop);


    connect(ui->get_playlist_view(), &QTableView::doubleClicked, [this](const QModelIndex &index)
    {
        core->cur_playlist()->setCurrentIndex(index.row());
        play_clicked = true;
        core->track_controller->play();
        ui->set_pause_button();
    });

    connect(core->cur_playlist(), &QMediaPlaylist::currentIndexChanged, [this](int index)
    {
        if(core->cur_playlist_model()->index(index, 0).isValid())
            ui->get_current_track()->setText(core->cur_playlist_model()->item(index)->text());
    });

    connect(ui->get_playlists_view(), &QTableView::doubleClicked, [this](const QModelIndex& index)
    {

        core->playlists()->setCurrentIndex(index.row());
        core->playlists_manager->cur_playlist = core->playlists()->currentMedia().playlist();

        core->cur_playlist_model()->removeRows(0, core->cur_playlist_model()->rowCount());
        for(auto title : core->playlists_manager->titles[index.data().toString()])
            core->cur_playlist_model()->appendRow(new QStandardItem(title));
        core->track_controller->setPlaylist(core->cur_playlist());

        if(play_clicked)
        {
            play_clicked = false;
            core->track_controller->pause();
            ui->set_play_button();
        }

        core->track_controller->setPlaylist(core->cur_playlist());

        ui->get_current_track()->setText("Current track");
    });

    connect(core->playlists_manager, SIGNAL(core->playlists_manager->playlist_created), this, SLOT(connect_playlist));

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
        core->cur_playlist()->setPlaybackMode(QMediaPlaylist::Random);
        break;
    case 1:
        shuffle_clicked++;
        ui->set_repeat_button();
        core->cur_playlist()->setPlaybackMode(QMediaPlaylist::Loop);
        break;
    case 2:
        shuffle_clicked++;
        ui->set_repeat_one_button();
        core->cur_playlist()->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        break;
    case 3:
        shuffle_clicked = 0;
        ui->set_direct_play_button();
        core->cur_playlist()->setPlaybackMode(QMediaPlaylist::Sequential);
        break;
    }
}

void Player::sort_button()
{
    if (sort_clicked == 0)
    {
        ui->get_playlist_view()->sortByColumn(0, Qt::AscendingOrder);
        sort_clicked = 1;
    }
    else
    {
        ui->get_playlist_view()->sortByColumn(0,Qt::DescendingOrder);
        sort_clicked = 0;
    }
}

void Player::handle_folder()
{
    QString folder_path = ui->get_folder();
    if (folder_path != "")
    {
        core->initialize_playlist(folder_path);

        connect(core->playlists()->media(core->playlists()->mediaCount() - 1).playlist(), &QMediaPlaylist::currentIndexChanged, [this](int index)
        {
            if(core->cur_playlist_model()->index(index, 0).isValid())
                ui->get_current_track()->setText(core->cur_playlist_model()->item(index)->text());
        });
    }
}

void Player::connect_playlist()
{
    connect(core->playlists()->media(core->playlists()->mediaCount() - 1).playlist(), &QMediaPlaylist::currentIndexChanged, [this](int index)
    {
        if(core->cur_playlist_model()->index(index, 0).isValid())
            ui->get_current_track()->setText(core->cur_playlist_model()->item(index)->text());
    });


}

void Player::handle_file()
{

    QString file_path = ui->get_file();
    if (file_path != "")
        core->initialize_music(file_path);
}

void Player::addp_button()
{
    if( ui->get_playlist_view()->selectionMode() == QAbstractItemView::MultiSelection)
    {
        QModelIndexList selection = ui->get_playlist_view()->selectionModel()->selectedRows();
        core->create_playlist(selection);

        ui->get_playlist_view()->clearSelection();
        ui->get_playlist_view()->setSelectionMode(QAbstractItemView::SingleSelection);
    }
    else if( ui->get_playlist_view()->selectionMode() == QAbstractItemView::SingleSelection)
        ui->get_playlist_view()->setSelectionMode(QAbstractItemView::MultiSelection);
}
