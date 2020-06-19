#include "remote_controller.h"

#include <QDebug>
#include <QJsonArray>

using namespace Common;

RemoteController::RemoteController(QObject *parent) : QObject(parent)
{
}


void RemoteController::mapKey(KeyEvents key, const QJsonValue &jval)
{
    if( jval.isArray() )
    {
        QJsonArray array = jval.toArray();
        for(int i = 0; i < array.size(); ++i)
            m_keys[array[i].toInt()] = key;
    }
    else
    {
        m_keys[jval.toInt()] = key;
    }
}


void RemoteController::readConfiguration(const QJsonObject &json)
{
    // Remote
    if( json.contains("next"))
        mapKey(E_KEY_NEXT, json["next"]);

    if( json.contains("return"))
        mapKey(E_KEY_RETURN, json["return"]);

    if( json.contains("enter"))
        mapKey(E_KEY_ENTER, json["enter"]);

    if( json.contains("edit"))
        mapKey(E_KEY_EDIT, json["edit"]);

    // Keybord Debug
    m_keys[Qt::Key_Right] = E_KEY_NEXT;
    m_keys[Qt::Key_Left] = E_KEY_RETURN;
    m_keys[Qt::Key_Enter] = E_KEY_ENTER;
    m_keys[Qt::Key_Shift] = E_KEY_EDIT;
}



void RemoteController::keyChanged(int key) {
    //qInfo() << "Key Pressed " << key;

    if(m_keys.contains(key))
        emit keyPressed(m_keys[key]);

    switch( m_keys[key])
    {
    case E_KEY_NEXT:
        emit nexted();
        break;

    case E_KEY_RETURN:
        emit returned();
        break;

    case E_KEY_ENTER:
        emit entered();
        break;

    case E_KEY_EDIT:
        emit edited();
        break;
    }

}
