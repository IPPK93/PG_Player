#ifndef PLAYLISTS_MANAGER_H
#define PLAYLISTS_MANAGER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>
#include <QMediaPlaylist>
#include <QModelIndexList>
#include <QStandardItemModel>

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


    QMap<QString, QList<QString>> titles;

    void create_playlist(QModelIndexList& indices);
    void delete_playlist(const QString& name);

    virtual ~PlaylistsManager() override;

signals:
    void playlist_created();

};

#endif // PLAYLISTS_MANAGER_H
