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
    void handle_folder();
    void handle_file();
};

#endif // PLAYER_H
