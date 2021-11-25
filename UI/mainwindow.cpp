#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include "stylehelper.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow),
m_leftMouseButtonPressed(None)
{
    ui->setupUi(this);
//    QObject::connect(ui->AddFolder,SIGNAL(clicked()),this, SLOT(abc()));
//    ui->ViewPlaylists;
    //QObject::connect(ui->AddFolder, SIGNAL(clicked()),this, SLOT(on_AddFolder_clicked()));
    /// Настройка UI
    this->setWindowFlags(Qt::FramelessWindowHint);      // Отключаем оформление окна
    this->setAttribute(Qt::WA_TranslucentBackground);   // Делаем фон главного виджета прозрачным
    this->setStyleSheet(StyleHelper::getWindowStyleSheet());    // Устанавливаем стиль виджета
    this->setMouseTracking(true);   // Включаем отслеживание курсора без нажатых кнопокы

    // Создаём эффект тени
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(9); // Устанавливаем радиус размытия
    shadowEffect->setOffset(0);     // Устанавливаем смещение тени
    ui->centralwidget->setGraphicsEffect(shadowEffect);   // Устанавливаем эффект тени на окно
    ui->centralwidget->layout()->setMargin(0);            // Устанавливаем размер полей
    ui->centralwidget->layout()->setSpacing(0);
    ui->label->setText("AIMP Fake Player");
    ui->label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // Установка стилей для всех элементов
    ui->currentTrack->setStyleSheet(StyleHelper::getLabelStyleSheet());
    ui->label->setStyleSheet(StyleHelper::getLabelStyleSheet());
    ui->btn_close->setStyleSheet(StyleHelper::getCloseStyleSheet());
    ui->btn_maximize->setStyleSheet(StyleHelper::getMaximizeStyleSheet());
    ui->btn_minimize->setStyleSheet(StyleHelper::getMinimizeStyleSheet());
    ui->btn_next->setStyleSheet(StyleHelper::getNextStyleSheet());
    ui->btn_previous->setStyleSheet(StyleHelper::getPreviousStyleSheet());
    ui->btn_stop->setStyleSheet(StyleHelper::getStopStyleSheet());
    ui->btn_play->setStyleSheet(StyleHelper::getPlayStyleSheet());
 //   ui->btn_pause->setStyleSheet(StyleHelper::getPauseStyleSheet());
    ui->btn_add->setStyleSheet(StyleHelper::getMenuStyleSheet());
    ui->btn_addf->setStyleSheet(StyleHelper::getMenuStyleSheet());
    ui->btn_sort->setStyleSheet(StyleHelper::getSortStyleSheet());
    ui->btn_shuffle->setStyleSheet(StyleHelper::getDirectStyleSheet());
    ui->btn_addp->setStyleSheet(StyleHelper::getAddpStyleSheet());
    ui->playlistsView->setStyleSheet(StyleHelper::getTableView1StyleSheet());
    ui->playlistView->setStyleSheet(StyleHelper::getTableViewStyleSheet());
    ui->btn_add->setText(tr("Добавить"));
    ui->btn_addf->setText(tr("Добавить папку"));
    ui->btn_sort->setCursor(Qt::PointingHandCursor);
    ui->btn_shuffle->setCursor(Qt::PointingHandCursor);
    ui->btn_addp->setCursor(Qt::PointingHandCursor);
    ui->btn_next->setCursor(Qt::PointingHandCursor);
    ui->btn_previous->setCursor(Qt::PointingHandCursor);
    ui->btn_stop->setCursor(Qt::PointingHandCursor);
    ui->btn_play->setCursor(Qt::PointingHandCursor);
//    ui->btn_pause->setCursor(Qt::PointingHandCursor);

    ui->horizontalLayout->setSpacing(6);
    // Настройка таблицы плейлиста
    m_playListModel = new QStandardItemModel(this);
    ui->playlistView->setModel(m_playListModel); // Устанавливаем модель данных в TableView
    // Устанавливаем заголовки таблицы
    m_playListModel->setHorizontalHeaderLabels(QStringList()  << tr("Audio Track")
                                                            << tr("File Path"));
    ui->playlistView->horizontalHeader()->hide();
    ui->playlistsView->horizontalHeader()->hide();
    ui->playlistView->hideColumn(1);    // Скрываем колонку, в которой хранится путь к файлу
    ui->playlistView->verticalHeader()->setVisible(false);                  // Скрываем нумерацию строк
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);  // Включаем выделение строк
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection); // Разрешаем выделять только одну строку
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);   // Отключаем редактирование
    // Включаем подгонку размера последней видимой колонки к ширине TableView
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);

    m_player = new QMediaPlayer(this);          // Инициализируем плеер
    m_playlist = new QMediaPlaylist(m_player);  // Инициализируем плейлист
    m_player->setPlaylist(m_playlist);          // Устанавливаем плейлист в плеер
    m_player->setVolume(70);                    // Устанавливаем громкость воспроизведения треков
    m_playlist->setPlaybackMode(QMediaPlaylist::Sequential);  // Устанавливаем циклический режим проигрывания плейлиста
    // подключаем кнопки управления к слотам управления
    // Здесь отметим, что навигация по плейлисту осуществляется именно через плейлист
    // а запуск/пауза/остановка через сам плеер
    connect(ui->btn_previous, &QToolButton::clicked, m_playlist, &QMediaPlaylist::previous);
    connect(ui->btn_next, &QToolButton::clicked, m_playlist, &QMediaPlaylist::next);
    connect(ui->btn_stop, &QToolButton::clicked, m_player, &QMediaPlayer::stop);

    /// коннекты для кнопок сворачивания/максимизации/минимизации/закрытия
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
    ///
    // При даблклике по треку в таблице устанавливаем трек в плейлисте
    connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){
        m_playlist->setCurrentIndex(index.row());
    });
    // при изменении индекса текущего трека в плейлисте, устанавливаем название файла в специальном лейбле
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int index){
        ui->currentTrack->setText(m_playListModel->data(m_playListModel->index(index, 0)).toString());
    });

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_playListModel;
    delete m_playlist;
    delete m_player;
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

//void MainWindow::abc()
//{
//   // ui->ViewPlaylists->
//    ui->listWidget->addItem("Audi");
//}


void MainWindow::on_btn_add_clicked()
{
    // С помощью диалога выбора файлов делаем множественный выбор mp3 файлов
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Open files"),
                                                      QString(),
                                                      tr("Audio Files (*.mp3)"));

    // Далее устанавливаем данные по именам и пути к файлам
    // в плейлист и таблицу отображающую плейлист
    foreach (QString filePath, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        m_playListModel->appendRow(items);
        m_playlist->addMedia(QUrl(filePath));
    };
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton ) {
        m_leftMouseButtonPressed = checkResizableField(event);
        setPreviousPosition(event->pos());
    }
    return QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_leftMouseButtonPressed = None;
    }
    return QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
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

MainWindow::MouseType MainWindow::checkResizableField(QMouseEvent *event)
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




bool c = false;
void MainWindow::on_btn_play_clicked()
{
    if(c == false)
    {
        c = true;
        m_player->play();
        ui->btn_play->setStyleSheet(StyleHelper::getPauseStyleSheet());
    }
    else
    {
        c = false;
        m_player->pause();
        ui->btn_play->setStyleSheet(StyleHelper::getPlayStyleSheet());
    }
}

int c1 = 0;
void MainWindow::on_btn_shuffle_clicked()
{
    switch (c1)
    {
    case 0:
        c1++;
        ui->btn_shuffle->setStyleSheet(StyleHelper::getShuffleStyleSheet());
        m_playlist->setPlaybackMode(QMediaPlaylist::Random);
        break;
    case 1:
        c1++;
        ui->btn_shuffle->setStyleSheet(StyleHelper::getRepeatStyleSheet());
        m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
        break;
    case 2:
        c1++;
        ui->btn_shuffle->setStyleSheet(StyleHelper::getRepeatOneStyleSheet());
        m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        break;
    case 3:
        c1 = 0;
        ui->btn_shuffle->setStyleSheet(StyleHelper::getDirectStyleSheet());
        m_playlist->setPlaybackMode(QMediaPlaylist::Sequential);
        break;
    }

}

void MainWindow::on_sldr_vol_valueChanged(int value)
{
    m_player->setVolume(value);
}


void MainWindow::on_sldr_track_valueChanged(int value)
{
//    m_player->setNotifyInterval(10);
//    m_player->setPosition(value);
}
