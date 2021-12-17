#ifndef FILESYSTEM_HANDLER_H
#define FILESYSTEM_HANDLER_H

#include <QString>
#include <QFileSystemModel>
#include <QMediaContent>
#include <QStringList>

/*!
 * \brief The FileSystem Handler namespace
 *
 * \details Handles work with filesystem (alongside UI-part).
 */
namespace FSHandler
{
    QMediaContent get_music(const QString& path);
    QStringList get_music_filenames(const QString& path);
};

#endif // FILESYSTEM_HANDLER_H
