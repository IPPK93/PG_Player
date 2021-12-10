#include "core.h"
#include <QStandardPaths>

Core::Core(QObject* parent)
: QObject(parent)
{
    playlists_manager = new PlaylistsManager;
    track_controller = new TrackController;
    track_controller->setMedia(playlists_manager->cur_playlist);
    track_controller->setPlaylist(cur_playlist());          // Устанавливаем плейлист в плеер
    track_controller->setVolume(70);                    // Устанавливаем громкость воспроизведения треков
    cur_playlist()->setPlaybackMode(QMediaPlaylist::Sequential);  // Устанавливаем прямой режим проигрывания плейлиста
}

void Core::initialize_playlist(QString folder_path)
{
    QStringList filenames = FSHandler::get_music_filenames(folder_path);
    QMediaPlaylist* playlist = new QMediaPlaylist;

    for(QString filename : filenames)
    {
        QUrl url = QUrl::fromLocalFile(folder_path + "/" + filename);
        playlist->addMedia(url);
        playlists_manager->default_playlist->addMedia(url);
    }
    if(playlists_manager->default_playlist == playlists_manager->cur_playlist)
    {
        for(const QString& filename : filenames)
        {
            playlists_manager->cur_playlist_model->appendRow(new QStandardItem(QDir(folder_path + "/" + filename).dirName()));
        }
    }
    playlists_manager->playlists->addMedia(QMediaContent(playlist));
    playlists_manager->playlists_model->appendRow(new QStandardItem(QDir(folder_path).dirName()));
}

void Core::initialize_music(QString music_path)
{
    QMediaContent music = FSHandler::get_music(music_path);
    playlists_manager->default_playlist->addMedia(music);
    if (playlists_manager->default_playlist == playlists_manager->cur_playlist)
    {
        playlists_manager->cur_playlist_model->appendRow(new QStandardItem(QDir(music_path).dirName()));
    }
}

QMediaPlaylist* Core::cur_playlist()
{
    return playlists_manager->cur_playlist;
}

QMediaPlaylist* Core::playlists()
{
    return playlists_manager->playlists;
}

QStandardItemModel* Core::cur_playlist_model()
{
    return playlists_manager->cur_playlist_model;
}

QStandardItemModel* Core::playlists_model()
{
    return playlists_manager->playlists_model;
}

Core::~Core()
{
    delete playlists_manager;
    delete track_controller;
}
