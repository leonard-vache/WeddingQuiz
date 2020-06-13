#ifndef REMOTECONTROLLER_H
#define REMOTECONTROLLER_H

#include "common.h"

#include <QObject>
#include <QMap>
#include <QJsonObject>
#include <QJsonValue>


class RemoteController : public QObject
{
    Q_OBJECT

public:
    explicit RemoteController(QObject *parent = nullptr);

    void readConfiguration(const QJsonObject &json);

private:
    void mapKey(Common::KeyEvents key, const QJsonValue &jval);


private:
    QMap<int, Common::KeyEvents> m_keys;


public slots:
    void keyChanged(int key);


signals:
    void keyPressed(Common::KeyEvents key);

    void nexted();
    void returned();
    void edited();
    void entered();
};

#endif // REMOTECONTROLLER_H
