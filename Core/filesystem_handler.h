#ifndef FILESYSTEM_HANDLER_H
#define FILESYSTEM_HANDLER_H

#include <QString>
#include "music.h"
#include "playlist.h"
#include <QFileSystemModel>
#include <QMediaContent>
#include <QMediaPlaylist>
#include <QStandardItemModel>

/*!
 * \brief The FileSystem Handler namespace
 *
 * \details Handles work with filesystem (alongside UI-part).
 */
namespace FSHandler
{
    QMediaContent get_music(const QString& path);
    QStringList get_music_filenames(const QString& path);
    QList<QStandardItem*> get_playlist_info(const QStringList);
    QList<QList<QStandardItem*>>* get_playlist_data_info(const QStringList& path);
};

#endif // FILESYSTEM_HANDLER_H
