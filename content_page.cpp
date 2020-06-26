#include "content_page.h"

#include <QRegExp>
#include <QJsonArray>

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


void ContentPage::readConfiguration(const QJsonObject &json) {

    qInfo() << json;

    if( json.contains("AutoPause") && json["AutoPause"].isObject())
    {
        QJsonObject j_pauses = json["AutoPause"].toObject();
        QStringList key = j_pauses.keys();
        QStringList::const_iterator constIterator;
        for (constIterator = key.constBegin(); constIterator != key.constEnd(); ++constIterator)
        {
            QString k = (*constIterator).toLocal8Bit().constData();
            m_autopauses[k] = j_pauses[k].toInt();
        }

        qInfo() << m_autopauses;

    }
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

//    QObject::connect(qmlObj, SIGNAL(positionChanged(int pos)),
//                     this, SLOT(onPositionChanged(int pos)) );
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


int ContentPage::getAutoPause(const QString &src) const
{
    if(isVideo(src) && m_autopauses.contains(src))
        return m_autopauses[src];
    else
        return -1;
}


void ContentPage::onPositionChanged(int pos)
{

    m_position = pos;
    qInfo() << pos;
}
