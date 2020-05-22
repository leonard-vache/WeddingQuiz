#include "configurator.h"
#include <QDebug>

#include <QFile>
#include <QJsonDocument>

Configurator::Configurator()
{

}

bool Configurator::loadConfigurationFile(const QString &qrcFilePath)
{
    QFile config_file(":/" + qrcFilePath);
    if (!config_file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Error: Couldn't open JSON file:" << "qrc:/" + qrcFilePath;
        return false;
    }

    QByteArray config_data = config_file.readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(config_data, &error);
    if(doc.isNull())
    {
        qCritical() << "Error: Invalid JSON document : " << error.errorString();  // https://jsonformatter.curiousconcept.com/
        return false;
    }

    m_JConfSections = doc.object();

    return true;
}


bool Configurator::isSection(const QString& section) const
{
    return  m_JConfSections.contains(section) && m_JConfSections[section].isObject();
}



const QJsonObject Configurator::getSection(const QString& section) const
{
    return m_JConfSections[section].toObject();
}



