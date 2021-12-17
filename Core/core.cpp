#include "core.h"
#include <QStringList>
#include <QDir>
#include <QUrl>
#include <QStandardItem>
#include <QMediaContent>
#include <QStandardPaths>

Core::Core(QObject* parent)
: QObject(parent)
{
    playlists_manager = new PlaylistsManager;
    track_controller = new TrackController;
    track_controller->setPlaylist(cur_playlist());          // Устанавливаем плейлист в плеер
    track_controller->setVolume(70);                    // Устанавливаем громкость воспроизведения треков
    cur_playlist()->setPlaybackMode(QMediaPlaylist::Sequential);  // Устанавливаем прямой режим проигрывания плейлиста
}

void Core::initialize_playlist(QString folder_path)
{
    QStringList filenames = FSHandler::get_music_filenames(folder_path);


    playlists()->addMedia(QMediaContent(new QMediaPlaylist));
    playlists_model()->appendRow(new QStandardItem(QDir(folder_path).dirName()));
    QModelIndex index = playlists_model()->index(playlists()->mediaCount() - 1, 0);

    for(QString filename : filenames)
    {
        QUrl url = QUrl::fromLocalFile(folder_path + "/" + filename);
        playlists()->media(playlists()->mediaCount() - 1).playlist()->addMedia(url);
        default_playlist()->addMedia(url);

        QString new_title = QDir(folder_path + "/" + filename).dirName();
        playlists_manager->titles[index.data().toString()].append(new_title);
        playlists_manager->titles["Default"].append(new_title);
    }

    if(cur_playlist() == default_playlist())
    {
        for(auto& elem : playlists_manager->titles[index.data().toString()])
        {
            cur_playlist_model()->appendRow(new QStandardItem(elem));
        }
    }
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

QMediaPlaylist* Core::default_playlist()
{
    return playlists_manager->default_playlist;
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

void Core::create_playlist(QModelIndexList& indices)
{
    playlists_manager->create_playlist(indices);
}

Core::~Core()
{
    delete playlists_manager;
    delete track_controller;
}
