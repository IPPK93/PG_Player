#ifndef TRACK_CONTROLLER_H
#define TRACK_CONTROLLER_H

#include <QObject>
#include <QMediaPlayer>

/*!
 * \brief The TrackController class
 *
 * \details Class that controls tracks' workflow
 */
class TrackController : public QMediaPlayer
{
    Q_OBJECT
public:
    explicit TrackController(QObject* parent = nullptr);
};

#endif // TRACK_CONTROLLER_H
