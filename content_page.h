#ifndef ContentPage_H
#define ContentPage_H

#include <QObject>
#include <QJsonObject>
#include <QMap>

#include "common.h"
#include "page_interface.h"


class ContentPage : public PageInterface
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running NOTIFY runningChanged);

public:
    explicit ContentPage(QObject *parent = nullptr);
    ContentPage(const ContentPage &copy);

    void readConfiguration(const QJsonObject &json);

    bool running() const { return m_running; }
    void setRunning(bool running) { m_running = running; emit runningChanged(); }

    Common::ContentState getState() const { return m_state; }
    void changeState(Common::ContentState state);

    void setQmlObject(QObject *qmlObj);

    Q_INVOKABLE bool isImage(const QString& src) const;
    Q_INVOKABLE bool isVideo(const QString& src) const;
    Q_INVOKABLE void clear();
    Q_INVOKABLE int getAutoPause(const QString &src) const;

    void next();
    void enter();
    void previous();
    void edit();

private:
    bool m_running;
    int m_position;
    QMap<QString, int> m_autopauses;

    Common::ContentState m_state;

public slots:
    void onStopped();
    void onPositionChanged(int pos);


signals:
    void runningChanged();

    void reset();
    void play();
    void pause();
};



#endif // ContentPage_H
