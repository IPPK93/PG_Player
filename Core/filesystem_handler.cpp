#include "filesystem_handler.h"
#include <QUrl>
#include <QDir>

/*!
 * \brief FSHandler::get_music
 * \param path: const std::string&
 * \return music: Music*
 *
 * \details Get QMediaContent object from a path to a music file.
 */
QMediaContent FSHandler::get_music(const QString& path)
{
    return QUrl::fromLocalFile(path);
}

/*!
 * \brief FSHandler::get_playlist
 * \param path: const std::string&
 * \return playlist: Playlist*
 *
 * \details Get QStringList object of music filenames from a path to a folder.
 */
QStringList FSHandler::get_music_filenames(const QString& folder_path)
{
    QDir directory(folder_path);
    QStringList music_files = directory.entryList(QStringList() << "*.mp3" << "*.flac",QDir::Files|QDir::Readable);

    return music_files;
}
