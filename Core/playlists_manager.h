#ifndef PLAYLISTS_MANAGER_H
#define PLAYLISTS_MANAGER_H

#include <QVector>
#include <QStandardItemModel>
#include <QMediaPlaylist>
#include <QString>
#include <QObject>


/*!
 * \brief The PlaylistsManager class
 *
 * \details Class that regulates playlists workflow
 */
class PlaylistsManager : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistsManager(QObject* parent = nullptr);

    QMediaPlaylist* playlists;
    QMediaPlaylist* cur_playlist;
    QMediaPlaylist* default_playlist;

    QStandardItemModel* playlists_model; // Модель данных плейлистов для отображения
    QStandardItemModel* cur_playlist_model; // Модель данных плейлистов для отображения


    void create_playlist(QMediaPlaylist* playlist, QList<QList<QStandardItemModel*>>* playlist_info); //???
    void delete_playlist(const QString& name);

    virtual ~PlaylistsManager() override;
};

#endif // PLAYLISTS_MANAGER_H
