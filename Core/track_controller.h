#ifndef TRACK_CONTROLLER_H
#define TRACK_CONTROLLER_H

//#include "music.h"
#include "timer.h"
#include <QMediaContent>
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

    Timer timer;
};

#endif // TRACK_CONTROLLER_H
