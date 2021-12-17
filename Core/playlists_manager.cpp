#include "playlists_manager.h"
#include <QModelIndex>
#include <QStandardItem>

PlaylistsManager::PlaylistsManager(QObject* parent)
    : QObject(parent)
{
    playlists = new QMediaPlaylist;
    playlists_model = new QStandardItemModel(this);

    playlists->addMedia(new QMediaPlaylist);
    default_playlist = playlists->media(0).playlist();

    playlists_model->appendRow(new QStandardItem("Default"));
    titles.insert("Default", QList<QString>());
    playlists_model->setHorizontalHeaderLabels(QStringList()  << tr("Playlist"));

    cur_playlist = default_playlist;
    cur_playlist_model = new QStandardItemModel(this);
    cur_playlist_model->setHorizontalHeaderLabels(QStringList()  << tr("Audio Track"));
}

/*!
 * \brief PlaylistsManager::create_playlist
 * \param name
 * \param data
 *
 * \details Create a playlist with a given name from a given music data
 *
 */
void PlaylistsManager::create_playlist(QModelIndexList& indices)
{
    QString name = "New Playlist " + QString::number(playlists_model->rowCount());
    QMediaPlaylist* playlist = new QMediaPlaylist(this);
    for(QModelIndex index : indices)
    {
        titles[name].append(index.data().toString());
        playlist->addMedia(playlists->media(index.row()));
    }

    playlists->addMedia(playlist);
    playlists_model->appendRow(new QStandardItem(name));

    emit playlist_created();
}

PlaylistsManager::~PlaylistsManager()
{
    for(int i = 0; i < playlists->mediaCount(); ++i)
        playlists->removeMedia(i);
    delete playlists_model;
    delete cur_playlist_model;
}
