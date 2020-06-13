#include "content_page.h"

#include <QRegExp>

using namespace Common;

ContentPage::ContentPage(QObject *parent) : PageInterface(parent)
{
    clear();
}


ContentPage::ContentPage(const ContentPage &copy)
{
    m_running = copy.m_running;
    m_state = copy.m_state;
}


void ContentPage::clear()
{
    changeState(E_STOP);
    setShowed(false);
    setRunning(false);
}


void ContentPage::changeState(ContentState state)
{
    m_state = state;
    switch(state)
    {
    case E_STOP:
        break;

    case E_PLAY:
        emit play();
        break;

    case E_PAUSE:
        emit pause();
        break;
    }
}


void ContentPage::setQmlObject(QObject *qmlObj)
{
    // C++ To QML
    QObject::connect(this, SIGNAL(reset()),
                     qmlObj, SIGNAL(reset()) );

    QObject::connect(this, SIGNAL(play()),
                     qmlObj, SIGNAL(play()) );

    QObject::connect(this, SIGNAL(pause()),
                     qmlObj, SIGNAL(pause()) );

    // QML to C++
    QObject::connect(qmlObj, SIGNAL(stopped()),
                     this, SLOT(onStopped()) );
    QObject::connect(qmlObj, SIGNAL(positionChanged(int pos)),
                     this, SLOT(onPositionChanged(int pos)) );
}



void ContentPage::next()
{
}


void ContentPage::enter()
{
    if(m_state == E_STOP)
    {
        changeState(E_PLAY);
    }
    else if (m_state == E_PLAY)
    {
        changeState(E_PAUSE);
    }
    else if (m_state == E_PAUSE)
    {
         changeState(E_PLAY);
    }
}


void ContentPage::previous()
{
    changeState(E_PAUSE);
    emit reset();
}


bool ContentPage::isImage(const QString& src) const
{
    QRegExp rx(".*\\.(png|jpg|jpeg)$");
    return rx.exactMatch(src);
}


bool ContentPage::isVideo(const QString& src) const
{
    QRegExp rx(".*\\.(mp4|avi)$");
    return rx.exactMatch(src);
}


void ContentPage::onStopped()
{
//    clear();
}


void ContentPage::onPositionChanged(int pos)
{
    m_position = pos;
    qInfo() << pos;
}
