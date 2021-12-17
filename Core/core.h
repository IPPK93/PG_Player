#ifndef CORE_H
#define CORE_H

#include "filesystem_handler.h"
#include "track_controller.h"
#include "playlists_manager.h"
#include <QObject>
#include <QString>
#include <QList>
#include <QMap>
#include <QMediaPlaylist>
#include <QModelIndex>
#include <QModelIndexList>
#include <QStandardItemModel>

/*!
 * \brief The Core class
 *
 * \details Base core class (singleton)
 */
class Core : public QObject
{
    Q_OBJECT
public:
    Core(QObject* parent = nullptr);

    PlaylistsManager* playlists_manager;
    TrackController* track_controller;

    void initialize_playlist(QString folder_path);

    void initialize_music(QString music_path);

    QMediaPlaylist* cur_playlist();
    QMediaPlaylist* playlists();
    QMediaPlaylist* default_playlist();
    QStandardItemModel* cur_playlist_model();
    QStandardItemModel* playlists_model();
    QMap<QModelIndex, QList<QString>> titles();

    void create_playlist(QModelIndexList& indices);
    virtual ~Core() override;
};

#endif // CORE_H
