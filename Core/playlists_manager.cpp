#include "playlists_manager.h"

PlaylistsManager::PlaylistsManager(QObject* parent)
    : QObject(parent)
{
    this->playlists = new QMediaPlaylist;
    this->playlists_model = new QStandardItemModel(this);

    this->default_playlist = new QMediaPlaylist;

    this->playlists->addMedia(default_playlist);
    this->playlists_model->appendRow(new QStandardItem("Default"));
    this->playlists_model->setHorizontalHeaderLabels(QStringList()  << tr("Playlist"));


    this->cur_playlist = default_playlist;
    this->cur_playlist_model = new QStandardItemModel(this);
    this->cur_playlist_model->setHorizontalHeaderLabels(QStringList()  << tr("Audio Track"));
}

/*!
 * \brief PlaylistsManager::create_playlist
 * \param name
 * \param data
 *
 * \details Create a playlist with a given name from a given music data
 *
 * NOTE: Parameters are still under consideration
 */
void PlaylistsManager::create_playlist(QMediaPlaylist* playlist, QList<QList<QStandardItemModel*>>* playlist_info)
{
//    this->playlists->addMedia(playlist);
//    this->playLists_model->appendRow(playlist_info);
}

/*!
 * \brief PlaylistsManager::delete_playlist
 * \param name
 *
 * \details Delete playlist with a given name
 *
 * NOTE: Parameters are still under consideration
 */
void PlaylistsManager::delete_playlist(const QString& name)
{

}

PlaylistsManager::~PlaylistsManager()
{ }
