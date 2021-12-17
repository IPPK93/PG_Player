#ifndef PLAYER_H
#define PLAYER_H

#include "Core/core.h"
#include "UI/mainwindow.h"
#include <QObject>

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
    void sort_button();
    void addp_button();
    void connect_playlist();

private:
    bool sort_clicked = false;
    bool play_clicked = false;
    int shuffle_clicked = 0;
};

#endif // PLAYER_H
