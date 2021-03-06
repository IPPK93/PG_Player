#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stylehelper.h"
#include <QStandardPaths>
#include <QFileDialog>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include <QAbstractItemView>
#include <QCursor>

MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent),
ui(new Ui::MainWindow),
m_leftMouseButtonPressed(None)
{
    ui->setupUi(this);
    // Настройка UI
    this->setWindowFlags(Qt::FramelessWindowHint);      // Отключаем оформление окна
    this->setAttribute(Qt::WA_TranslucentBackground);   // Делаем фон главного виджета прозрачным
    this->setStyleSheet(StyleHelper::getWindowStyleSheet());    // Устанавливаем стиль виджета
    this->setMouseTracking(true);   // Включаем отслеживание курсора без нажатых кнопокы

    // Создаём эффект тени
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(9); // Устанавливаем радиус размытия
    shadowEffect->setOffset(0);     // Устанавливаем смещение тени
    ui->centralwidget->setGraphicsEffect(shadowEffect);   // Устанавливаем эффект тени на окно
    ui->centralwidget->layout()->setMargin(0);            // Устанавливаем размер полей
    ui->centralwidget->layout()->setSpacing(0);
    ui->label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // Установка стилей для всех элементов
    ui->sldr_track->setStyleSheet(StyleHelper::getSliderStyleSheet());
    ui->sldr_vol->setStyleSheet(StyleHelper::getSliderStyleSheet());
    ui->currentTrack->setStyleSheet(StyleHelper::getLabelStyleSheet());
    ui->label->setStyleSheet(StyleHelper::getLabelStyleSheet());
    ui->btn_close->setStyleSheet(StyleHelper::getCloseStyleSheet());
    ui->btn_maximize->setStyleSheet(StyleHelper::getMaximizeStyleSheet());
    ui->btn_minimize->setStyleSheet(StyleHelper::getMinimizeStyleSheet());
    ui->btn_next->setStyleSheet(StyleHelper::getNextStyleSheet());
    ui->btn_previous->setStyleSheet(StyleHelper::getPreviousStyleSheet());
    ui->btn_stop->setStyleSheet(StyleHelper::getStopStyleSheet());
    ui->btn_play->setStyleSheet(StyleHelper::getPlayStyleSheet());
    ui->btn_add_file->setStyleSheet(StyleHelper::getMenuStyleSheet());
    ui->btn_add_folder->setStyleSheet(StyleHelper::getMenuStyleSheet());
    ui->btn_sort->setStyleSheet(StyleHelper::getSortStyleSheet());
    ui->btn_shuffle->setStyleSheet(StyleHelper::getDirectStyleSheet());
    ui->btn_addp->setStyleSheet(StyleHelper::getAddpStyleSheet());
    ui->playlists_view->setStyleSheet(StyleHelper::getTableView1StyleSheet());
    ui->playlist_view->setStyleSheet(StyleHelper::getTableViewStyleSheet());
    ui->btn_add_file->setText(tr("Add file"));
    ui->btn_add_folder->setText(tr("Add folder"));
    ui->btn_sort->setCursor(Qt::PointingHandCursor);
    ui->btn_shuffle->setCursor(Qt::PointingHandCursor);
    ui->btn_addp->setCursor(Qt::PointingHandCursor);
    ui->btn_next->setCursor(Qt::PointingHandCursor);
    ui->btn_previous->setCursor(Qt::PointingHandCursor);
    ui->btn_stop->setCursor(Qt::PointingHandCursor);
    ui->btn_play->setCursor(Qt::PointingHandCursor);


    ui->horizontalLayout->setSpacing(6);
    ui->playlist_view->horizontalHeader()->hide();
    ui->playlist_view->verticalHeader()->setVisible(false);                  // Скрываем нумерацию строк
    ui->playlist_view->setSelectionBehavior(QAbstractItemView::SelectRows);  // Включаем выделение строк
    ui->playlist_view->setSelectionMode(QAbstractItemView::SingleSelection); // Разрешаем выделять только одну строку
    ui->playlist_view->setEditTriggers(QAbstractItemView::NoEditTriggers);   // Отключаем редактирование
    // Включаем подгонку размера последней видимой колонки к ширине TableView
    ui->playlist_view->horizontalHeader()->setStretchLastSection(true);

    ui->playlists_view->horizontalHeader()->hide();
    ui->playlists_view->verticalHeader()->setVisible(false);                  // Скрываем нумерацию строк
    ui->playlists_view->setSelectionBehavior(QAbstractItemView::SelectRows);  // Включаем выделение строк
    ui->playlists_view->setSelectionMode(QAbstractItemView::SingleSelection); // Разрешаем выделять только одну строку
    ui->playlists_view->setEditTriggers(QAbstractItemView::NoEditTriggers);   // Отключаем редактирование
    // Включаем подгонку размера последней видимой колонки к ширине TableView
    ui->playlists_view->horizontalHeader()->setStretchLastSection(true);
    ui->playlists_view->setSortingEnabled(true);

    // коннекты для кнопок сворачивания/максимизации/минимизации/закрытия
    connect(ui->btn_minimize, &QToolButton::clicked, this, &QWidget::showMinimized);
    connect(ui->btn_maximize, &QToolButton::clicked, [this](){
        if (this->isMaximized()) {
            ui->btn_maximize->setStyleSheet(StyleHelper::getMaximizeStyleSheet());
            this->layout()->setMargin(9);
            this->showNormal();
        } else {
            ui->btn_maximize->setStyleSheet(StyleHelper::getRestoreStyleSheet());
            this->layout()->setMargin(0);
            this->showMaximized();
        }
    });
    connect(ui->btn_close, &QToolButton::clicked, this, &QWidget::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPoint MainWindow::previousPosition() const
{
    return m_previousPosition;
}

void MainWindow::setPreviousPosition(QPoint previousPosition)
{
    if (m_previousPosition == previousPosition)
        return;

    m_previousPosition = previousPosition;
    emit previousPositionChanged(previousPosition);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_leftMouseButtonPressed = checkResizableField(event);
        setPreviousPosition(event->pos());
    }
    return QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_leftMouseButtonPressed = None;
    }
    return QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    switch (m_leftMouseButtonPressed) {
    case Move: {
        if (isMaximized()) {
            ui->btn_maximize->setStyleSheet(StyleHelper::getMaximizeStyleSheet());
            this->layout()->setMargin(9);
            auto part = event->screenPos().x() / width();
            this->showNormal();
            auto offsetX = width() * part;
            setGeometry(event->screenPos().x() - offsetX, 0, width(), height());
            setPreviousPosition(QPoint(offsetX, event->y()));
        } else {
            auto dx = event->x() - m_previousPosition.x();
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x() + dx, y() + dy, width(), height());
        }
        break;
    }
    case Top: {
        if (!isMaximized()) {
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x(), y() + dy, width(), height() - dy);
        }
        break;
    }
    case Bottom: {
        if (!isMaximized()) {
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x(), y(), width(), height() + dy);
            setPreviousPosition(event->pos());
        }
        break;
    }
    case Left: {
        if (!isMaximized()) {
            auto dx = event->x() - m_previousPosition.x();
            setGeometry(x() + dx, y(), width() - dx, height());
        }
        break;
    }
    case Right: {
        if (!isMaximized()) {
            auto dx = event->x() - m_previousPosition.x();
            setGeometry(x(), y(), width() + dx, height());
            setPreviousPosition(event->pos());
        }
        break;
    }
    default:
        checkResizableField(event);
        break;
    }
    return QWidget::mouseMoveEvent(event);
}

MainWindow::MouseType MainWindow::checkResizableField(QMouseEvent* event)
{
    QPointF position = event->screenPos();
    qreal x = this->x();
    qreal y = this->y();
    qreal width = this->width();
    qreal height = this->height();

    QRectF rectTop(x + 9, y, width - 18, 7);
    QRectF rectBottom(x + 9, y + height - 7, width - 18, 7);
    QRectF rectLeft(x, y + 9, 7, height - 18);
    QRectF rectRight(x + width - 7, y + 9, 7, height - 18);
    QRectF rectInterface(x + 9, y + 9, width - 18, height - 18);

    if (rectTop.contains(position)) {
        setCursor(Qt::SizeVerCursor);
        return Top;
    } else if (rectBottom.contains(position)) {
        setCursor(Qt::SizeVerCursor);
        return Bottom;
    } else if (rectLeft.contains(position)) {
        setCursor(Qt::SizeHorCursor);
        return Left;
    } else if (rectRight.contains(position)) {
        setCursor(Qt::SizeHorCursor);
        return Right;
    } else if (rectInterface.contains(position)){
        setCursor(QCursor());
        return Move;
    } else {
        setCursor(QCursor());
        return None;
    }
}

QString MainWindow::get_folder()
{
    QString dir = QFileDialog::getExistingDirectory(this,
                                                    tr("Open Directory"),
                                                    QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    return dir;
}

QString MainWindow::get_file()
{
    return QFileDialog::getOpenFileName(this,
                                        tr("Open File"),
                                        QStandardPaths::writableLocation(QStandardPaths::DownloadLocation),
                                        tr("Audio Files (*.mp3)"));
}

void MainWindow::set_play_button()
{
    ui->btn_play->setStyleSheet(StyleHelper::getPlayStyleSheet());
}

void MainWindow::set_pause_button()
{
    ui->btn_play->setStyleSheet(StyleHelper::getPauseStyleSheet());
}

void MainWindow::set_shuffle_button()
{
    ui->btn_shuffle->setStyleSheet(StyleHelper::getShuffleStyleSheet());
}
void MainWindow::set_repeat_button()
{
    ui->btn_shuffle->setStyleSheet(StyleHelper::getRepeatStyleSheet());
}
void MainWindow::set_repeat_one_button()
{
    ui->btn_shuffle->setStyleSheet(StyleHelper::getRepeatOneStyleSheet());
}
void MainWindow::set_direct_play_button()
{
    ui->btn_shuffle->setStyleSheet(StyleHelper::getDirectStyleSheet());
}

const QToolButton* MainWindow::get_add_file_button()
{
    return ui->btn_add_file;
}

const QToolButton* MainWindow::get_add_folder_button()
{
    return ui->btn_add_folder;
}

const QToolButton* MainWindow::get_add_playlist_button()
{
    return ui->btn_addp;
}

QLabel* MainWindow::get_current_track()
{
    return ui->currentTrack;
}

const QToolButton* MainWindow::get_prev_button()
{
    return ui->btn_previous;
}

const QToolButton* MainWindow::get_next_button()
{
    return ui->btn_next;
}

const QToolButton* MainWindow::get_play_button()
{
    return ui->btn_play;
}

const QToolButton* MainWindow::get_shuffle_button()
{
    return ui->btn_shuffle;
}

const QSlider* MainWindow::get_slider_vol()
{
    return ui->sldr_vol;
}

const QSlider* MainWindow::get_slider_track()
{
    return ui->sldr_track;
}

const QToolButton* MainWindow::get_stop_button()
{
    return ui->btn_stop;
}

const QToolButton* MainWindow::get_sort_button()
{
    return ui->btn_sort;
}

const QToolButton* MainWindow::get_addp_button()
{
    return ui->btn_addp;
}

QTableView* MainWindow::get_playlist_view()
{
    return ui->playlist_view;
}

QTableView* MainWindow::get_playlists_view()
{
    return ui->playlists_view;
}

