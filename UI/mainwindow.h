#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QMouseEvent>
#include <QtWidgets/QToolButton>
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QPoint previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)
    
    enum MouseType {
        None = 0,
        Top,
        Bottom,
        Left,
        Right,
        Move
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPoint previousPosition() const;

    const QToolButton* get_add_file_button();
    const QToolButton* get_add_folder_button();
    const QToolButton* get_prev_button();
    const QToolButton* get_next_button();
    const QToolButton* get_play_button();
    const QToolButton* get_stop_button();
    const QToolButton* get_shuffle_button();
    const QSlider* get_slider_vol();
    const QSlider* get_slider_track();


    QString get_folder();
    QString get_file();

    QTableView* get_playlist_view();
    QTableView* get_playlists_view();

    
public slots:
    void setPreviousPosition(QPoint previousPosition);
    void set_play_button();
    void set_pause_button();
    void set_shuffle_button();
    void set_repeat_button();
    void set_repeat_one_button();
    void set_direct_play_button();
    
signals:
    void previousPositionChanged(QPoint previousPosition);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
//    QStandardItemModel  *m_playListModel;   // Модель данных плейлиста для отображения
//    QMediaPlayer        *m_player;          // Проигрыватель треков
//    QMediaPlaylist      *m_playlist;        // Плейлиста проигрывателя
    MouseType m_leftMouseButtonPressed;
    QPoint m_previousPosition;

    MouseType checkResizableField(QMouseEvent *event);

};
#endif // MAINWINDOW_H
