#include "remote_controller.h"

#include <QDebug>



RemoteController::RemoteController(QObject *parent) : QObject(parent)
{

}

void RemoteController::readConfiguration(const QJsonObject &json)
{
    // Remote
    if( json.contains("next"))
        m_keys[json["next"].toInt()] = E_KEY_NEXT;

    if( json.contains("return"))
        m_keys[json["return"].toInt()] = E_KEY_RETURN;

    if( json.contains("enter"))
        m_keys[json["enter"].toInt()] = E_KEY_ENTER;

    if( json.contains("edit"))
        m_keys[json["edit"].toInt()] = E_KEY_EDIT;

    // Keybord Debug
    m_keys[Qt::Key_Right] = E_KEY_NEXT;
    m_keys[Qt::Key_Left] = E_KEY_RETURN;
    m_keys[Qt::Key_Enter] = E_KEY_ENTER;
    m_keys[Qt::Key_Shift] = E_KEY_EDIT;
}



void RemoteController::keyChanged(int key) {
    qInfo() << "Key Pressed " << key;

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
