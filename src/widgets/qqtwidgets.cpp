#include "qqtwidgets.h"

#include <QDesktopWidget>

tagBtnIconTable::tagBtnIconTable()
{
    pixmap[BTN_NORMAL] = "./skin/default/bt_bt_normal.png";
    pixmap[BTN_UNCHECK] = "./skin/default/bt_bt_normal.png";
#ifdef __EMBEDDED_LINUX__
    pixmap[BTN_HOVER] = "./skin/default/bt_bt_hover.png";
    pixmap[BTN_CHECK] = "./skin/default/bt_bt_hover.png";
    pixmap[BTN_PRESS] = "./skin/default/bt_bt_hover.png";
#else
    pixmap[BTN_HOVER] = "./skin/default/bt_bt_hover.png";
    pixmap[BTN_CHECK] = "./skin/default/bt_bt_check.png";
    pixmap[BTN_PRESS] = "./skin/default/bt_bt_press.png";
#endif
    pixmap[BTN_DISABLE] = "./skin/default/bt_bt_disable.png";
}

QString tagBtnIconTable::pixMap ( int index )
{
    if ( index < 0 || index + 1 > BTN_MAX )
        return pixmap[BTN_NORMAL];

    return pixmap[index];
}

void tagBtnIconTable::setPixMap ( int index, QString pix )
{
    if ( index < 0 || index + 1 > BTN_MAX )
        return;

    pixmap[index] = pix;
}

void tagBtnIconTable::initNormal ( QString normal, QString press )
{
    if ( !normal.isEmpty() )
        pixmap[BTN_NORMAL] = normal;

    if ( !press.isEmpty() )
        pixmap[BTN_PRESS] = press;
}

void tagBtnIconTable::initCheck ( QString uncheck, QString check )
{
    if ( !uncheck.isEmpty() )
        pixmap[BTN_UNCHECK] = uncheck;

    if ( !check.isEmpty() )
        pixmap[BTN_CHECK] = check;
}

void tagBtnIconTable::initOther ( QString hover, QString disable )
{
    if ( !hover.isEmpty() )
        pixmap[BTN_HOVER] = hover;

    if ( !disable.isEmpty() )
        pixmap[BTN_DISABLE] = disable;
}

QString& tagBtnIconTable::operator [] ( int index )
{
    if ( index < 0 || index >= BTN_MAX )
        return pixmap[0];

    return pixmap[index];
}

const QString& tagBtnIconTable::operator[] ( int index ) const
{
    if ( index < 0 || index >= BTN_MAX )
        return pixmap[0];

    return pixmap[index];
}

/**
 * ************************************************************************
 */
void moveHCenter ( QWidget* w )
{
    QWidget* targetWidget = w;
    QRect targetGeometry = targetWidget->geometry();

    QDesktopWidget* parentWidget = QApplication::desktop();
    QRect parentGeometry = parentWidget->availableGeometry();

    int x1 = parentGeometry.left()
             + ( parentGeometry.width() - targetWidget->width() ) / 2;
    int y1 = targetGeometry.top();

    targetWidget->move ( x1, y1 );
}

void moveVCenter ( QWidget* w )
{
    QWidget* targetWidget = w;
    QDesktopWidget* parentWidget = QApplication::desktop();

    int x1 = targetWidget->geometry().left();
    int y1 = parentWidget->availableGeometry().top()
             + ( parentWidget->availableGeometry().height()
                 - targetWidget->height() ) / 2;

    targetWidget->move ( x1, y1 );
}

void moveCenter ( QWidget* w )
{
    QWidget* targetWidget = w;
    QDesktopWidget* parentWidget = QApplication::desktop();

    int x1 = parentWidget->availableGeometry().left()
             + ( parentWidget->availableGeometry().width()
                 - targetWidget->width() ) / 2;
    int y1 = parentWidget->availableGeometry().top()
             + ( parentWidget->availableGeometry().height()
                 - targetWidget->height() ) / 2;

    targetWidget->move ( x1, y1 );
}

void moveFull ( QWidget* w )
{
    QWidget* targetWidget = w;
    QDesktopWidget* parentWidget = QApplication::desktop();

    targetWidget->setGeometry ( parentWidget->availableGeometry() );
    targetWidget->move ( parentWidget->availableGeometry().left(),
                         parentWidget->availableGeometry().top() );
}

void moveLeft ( QWidget* w )
{
    QWidget* targetWidget = w;
    QRect targetGeometry = targetWidget->geometry();

    QDesktopWidget* parentWidget = QApplication::desktop();
    QRect parentGeometry = parentWidget->availableGeometry();

    int x1 = parentGeometry.left();
    int y1 = targetGeometry.top();

    targetWidget->move ( x1, y1 );
}

void moveRight ( QWidget* w )
{
    QWidget* targetWidget = w;
    QDesktopWidget* parentWidget = QApplication::desktop();

    int x1 = parentWidget->availableGeometry().right()
             - targetWidget->width();
    int y1 = targetWidget->geometry().top();

    targetWidget->move ( x1, y1 );
}

void moveTop ( QWidget* w )
{
    QWidget* targetWidget = w;
    QRect targetGeometry = targetWidget->geometry();

    QDesktopWidget* parentWidget = QApplication::desktop();
    QRect parentGeometry = parentWidget->availableGeometry();

    int x1 = targetGeometry.left();
    int y1 = parentGeometry.top();

    targetWidget->move ( x1, y1 );
}

void moveBottom ( QWidget* w )
{
    QWidget* targetWidget = w;
    QRect targetGeometry = targetWidget->geometry();

    QDesktopWidget* parentWidget = QApplication::desktop();
    QRect parentGeometry = parentWidget->availableGeometry();

    int x1 = targetGeometry.left();
    int y1 = parentGeometry.bottom();

    targetWidget->move ( x1, y1 );
}


/**
 * ************************************************************************
 */
void moveHCenter ( QWidget* w, QWidget* parent )
{
    QRect targetGeometry = w->geometry();

    QRect parentRect = parent->rect();
    if ( !parent )
        parentRect = QApplication::desktop()->availableGeometry();

    int x1 = parentRect.left()
             + ( parentRect.width() - targetGeometry.width() ) / 2;
    int y1 = targetGeometry.top();

    w->move ( x1, y1 );
}

void moveVCenter ( QWidget* w, QWidget* parent )
{
    QRect targetGeometry = w->geometry();

    QRect parentRect = parent->rect();
    if ( !parent )
        parentRect = QApplication::desktop()->availableGeometry();

    int x1 = targetGeometry.left();
    int y1 = parentRect.top()
             + ( parentRect.height() - targetGeometry.height() ) / 2;

    w->move ( x1, y1 );
}

void moveCenter ( QWidget* w, QWidget* parent )
{
    QRect targetGeometry = w->geometry();

    QRect parentRect = parent->rect();
    if ( !parent )
        parentRect = QApplication::desktop()->availableGeometry();

    int x1 = parentRect.left()
             + ( parentRect.width() - targetGeometry.width() ) / 2;
    int y1 = parentRect.top()
             + ( parentRect.height() - targetGeometry.height() ) / 2;

    w->move ( x1, y1 );
}

void moveFull ( QWidget* w, QWidget* parent )
{
    QRect targetGeometry = w->geometry();

    QRect parentRect = parent->rect();
    if ( !parent )
        parentRect = QApplication::desktop()->availableGeometry();

    w->setGeometry ( parentRect );
    w->move ( parentRect.left(), parentRect.top() );
}

void moveLeft ( QWidget* w, QWidget* parent )
{
    QRect targetGeometry = w->geometry();

    QRect parentRect = parent->rect();
    if ( !parent )
        parentRect = QApplication::desktop()->availableGeometry();

    int x1 = parentRect.left();
    int y1 = targetGeometry.top();

    w->move ( x1, y1 );
}

void moveRight ( QWidget* w, QWidget* parent )
{
    QRect targetGeometry = w->geometry();

    QRect parentRect = parent->rect();
    if ( !parent )
        parentRect = QApplication::desktop()->availableGeometry();

    int x1 = parentRect.right() - targetGeometry.width();
    int y1 = targetGeometry.top();

    w->move ( x1, y1 );
}

void moveTop ( QWidget* w, QWidget* parent )
{
    QRect targetGeometry = w->geometry();

    QRect parentRect = parent->rect();
    if ( !parent )
        parentRect = QApplication::desktop()->availableGeometry();

    int x1 = targetGeometry.left();
    int y1 = parentRect.top();

    w->move ( x1, y1 );
}

void moveBottom ( QWidget* w, QWidget* parent )
{
    QRect targetGeometry = w->geometry();

    QRect parentRect = parent->rect();
    if ( !parent )
        parentRect = QApplication::desktop()->availableGeometry();

    int x1 = targetGeometry.left();
    int y1 = parentRect.bottom();

    w->move ( x1, y1 );
}

