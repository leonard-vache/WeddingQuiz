#ifndef REMOTECONTROLLER_H
#define REMOTECONTROLLER_H

#include "common.h"

#include <QObject>
#include <QMap>
#include <QJsonObject>


class RemoteController : public QObject
{
    Q_OBJECT

public:
    explicit RemoteController(QObject *parent = nullptr);

    void readConfiguration(const QJsonObject &json);


private:
    QMap<int, KeyEvents> m_keys;


public slots:
    void keyChanged(int key);


signals:
    void keyPressed(KeyEvents key);

    void nexted();
    void returned();
    void edited();
    void entered();
};

#endif // REMOTECONTROLLER_H
