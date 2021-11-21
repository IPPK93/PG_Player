#include "stylehelper.h"

QString StyleHelper::getWindowStyleSheet()
{
    return "QWidget { "
           "background-color: #454545; "
           "border: 1px solid black; "
           "}";
}

QString StyleHelper::getLabelStyleSheet()
{
    return "QLabel { "
           "color: #8f8f8f; "
           "border: none; "
           "margin: 6px; "
           "}";
}

QString StyleHelper::getCloseStyleSheet()
{
    return "QToolButton { "
           "image: url(:/close-orange.png);"
           "background-color: #292929; "
           "icon-size: 12px;"
           "padding-left: 10px;"
           "padding-right: 10px;"
           "padding-top: 5px;"
           "padding-bottom: 5px;"
           "border: 1px solid #292929; "
           "}"
           "QToolButton:hover {"
           "image: url(:/close.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/close.png);"
           "background-color: #de8e37; "
           "}";
}

QString StyleHelper::getMaximizeStyleSheet()
{
    return "QToolButton { "
           "image: url(:/window-maximize-gray.png);"
           "background-color: #292929;"
           "icon-size: 12px;"
           "padding-left: 10px;"
           "padding-right: 10px;"
           "padding-top: 5px;"
           "padding-bottom: 5px;"
           "border: 1px solid #292929; "
           "}"
           "QToolButton:hover {"
           "image: url(:/window-maximize.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/window-maximize.png);"
           "background-color: #de8e37; "
           "}";
}

QString StyleHelper::getRestoreStyleSheet()
{
    return "QToolButton { "
           "image: url(:/window-restore-gray.png);"
           "background-color: #292929;"
           "icon-size: 12px;"
           "padding-left: 10px;"
           "padding-right: 10px;"
           "padding-top: 5px;"
           "padding-bottom: 5px;"
           "border: 1px solid #292929; "
           "}"
           "QToolButton:hover {"
           "image: url(:/window-restore.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/window-restore.png);"
           "background-color: #de8e37; "
           "}";
}

QString StyleHelper::getMinimizeStyleSheet()
{
    return "QToolButton { "
           "image: url(:/window-minimize-gray.png);"
           "background-color: #292929;"
           "icon-size: 12px;"
           "padding-left: 10px;"
           "padding-right: 10px;"
           "padding-top: 5px;"
           "padding-bottom: 5px;"
           "border: 1px solid #292929; "
           "}"
           "QToolButton:hover { "
           "image: url(:/window-minimize.png); "
           "}"
           "QToolButton:pressed { "
           "image: url(:/window-minimize.png);"
           "background-color: #de8e37; "
           "}";
}

QString StyleHelper::getNextStyleSheet()
{
    return "QToolButton { "
           "image: url(:/skip-next.png);"
           "icon-size: 24px;"
           "padding: 6px;"
           "margin: 6px;"
           "border: none;"
           "}"
           "QToolButton:pressed { "
           "image: url(:/skip-next-orange.png)"
           "}";
}

QString StyleHelper::getPreviousStyleSheet()
{
    return "QToolButton { "
           "image: url(:/skip-previous.png);"
           "icon-size: 24px;"
           "padding: 6px;"
           "margin: 6px;"
           "border: none;"
           "}"
           "QToolButton:pressed { "
           "image: url(:/skip-previous-orange.png)"
           "}";
}

QString StyleHelper::getStopStyleSheet()
{
    return "QToolButton { "
           "image: url(:/stop.png);"
           "icon-size: 24px;"
           "padding: 6px;"
           "margin: 6px;"
           "border: none;"
           "}"
           "QToolButton:pressed { "
           "image: url(:/stop-orange.png)"
           "}";
}

QString StyleHelper::getPlayStyleSheet()
{
    return "QToolButton { "
           "image: url(:/play.png);"
           "icon-size: 48px;"
           "padding: 6px;"
           "margin: 6px;"
           "border: none;"
           "}"
           "QToolButton:pressed { "
           "image: url(:/play-orange.png)"
           "}";
}

QString StyleHelper::getPauseStyleSheet()
{
    return "QToolButton { "
           "image: url(:/pause.png);"
           "icon-size: 24px;"
           "padding: 6px;"
           "margin: 6px;"
           "border: none;"
           "}"
           "QToolButton:pressed { "
           "image: url(:/pause-orange.png)"
           "}";
}

QString StyleHelper::getMenuStyleSheet()
{
    return "QToolButton { "
           "color: #8f8f8f;"
           "background-color: #292929;"
           "icon-size: 12px;"
           "padding-left: 10px;"
           "padding-right: 10px;"
           "padding-top: 5px;"
           "padding-bottom: 5px;"
           "border: 1px solid #292929; "
           "}"
           "QToolButton:hover {"
           "color: white;"
           "}"
           "QToolButton:pressed { "
           "color: white; "
           "background-color: #de8e37; "
           "}";
}

QString StyleHelper::getTableViewStyleSheet()
{
    return "QTableView { "
           "background-color: white; "
           "color: black; "
           "border: 1px solid #e2e2de;"
           "}"
           "QTableView::item:selected {"
           "background-color: #de8e37;"
           "}"
           "QHeaderView::section:horizintal {"
           "background-color: white;"
           "border-style: none;"
           "color: black; "
           "border: 1px solid #e2e2de; "
           "padding: 6px; "
           "}";
}
