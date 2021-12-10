#ifndef PLAYER_H
#define PLAYER_H

#include "Core/core.h"
#include "UI/mainwindow.h"
#include <QStringList>

/*!
 * \brief The Player class
 *
 * \details Key program class
 */
class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject* parent = nullptr);

    Core* core;
    MainWindow* ui;


public slots:
    void play_button();
    void shuffle_button();
    void handle_folder();
    void handle_file();
   // void on_sldr_vol_valueChanged(int value);
    void on_sldr_track_valueChanged(int value);
};

#endif // PLAYER_H
