#include <qqtwidgeteffect.h>

#include <QGraphicsEffect>
#include <qqtanimation.h>

void setShadowEffect ( QWidget* widget )
{
    Q_ASSERT ( widget );

    /*
     * blurRadius 阴影清晰度，越小越清晰
     * dx x方向阴影位置和偏移量，正值在右方，值越大偏移越大
     * dy y方向阴影位置和偏移量，正值在下方，值越大偏移越大
     */
    static QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius ( 10 );
    shadow->setColor ( QColor ( 0, 0, 0, 160 ) );
    shadow->setOffset ( 5, 5 );
    shadow->setEnabled ( true );
    widget->setGraphicsEffect ( shadow );

}

void setFadeEffect ( QWidget* widget, quint32 millseconds, qreal startOpacity, qreal endOpacity )
{
    Q_ASSERT ( widget );

    static QPropertyAnimation* show_animation_ = new QPropertyAnimation ( widget, "windowOpacity" );
    show_animation_->setDuration ( millseconds );
    show_animation_->setStartValue ( startOpacity );
    show_animation_->setEndValue ( endOpacity );
    show_animation_->start();
    widget->show();
}

void setHighlightTextEffect ( QWidget* widget )
{
    Q_ASSERT ( widget );

    static QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect;
    shadow_effect->setOffset ( 0, 0 );
    shadow_effect->setColor ( Qt::gray );
    shadow_effect->setBlurRadius ( 20 );
    widget->setGraphicsEffect ( shadow_effect );
}

void setFadeTextEffect ( QWidget* widget, QColor color )
{
    Q_ASSERT ( widget );

    static QGraphicsColorizeEffect* m_effect = new QGraphicsColorizeEffect;
    m_effect->setColor ( color ); //( QColor ( 122, 193, 66 ) );
    m_effect->setStrength ( 0 );
    m_effect->setEnabled ( true );
    widget->setGraphicsEffect ( m_effect );
}
