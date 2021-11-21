#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QMouseEvent>
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
    
public slots:
    void setPreviousPosition(QPoint previousPosition);  
    
signals:
    void previousPositionChanged(QPoint previousPosition);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_btn_add_clicked(); // Слот для обработки добавления треков через диалоговое окно
//    void abc();

private:
    Ui::MainWindow *ui;
    QStandardItemModel  *m_playListModel;   // Модель данных плейлиста для отображения
    QMediaPlayer        *m_player;          // Проигрыватель треков
    QMediaPlaylist      *m_playlist;        // Плейлиста проигрывателя
    MouseType m_leftMouseButtonPressed;
    QPoint m_previousPosition;

    MouseType checkResizableField(QMouseEvent *event);
};
#endif // MAINWINDOW_H
