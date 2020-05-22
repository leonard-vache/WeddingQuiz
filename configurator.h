#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <QJsonObject>
#include <QString>


class Configurator
{
public:
    Configurator();

    bool loadConfigurationFile(const QString &qrcFilePath);

    bool isSection(const QString& section) const;
    const QJsonObject getSection(const QString& section) const;

private:
    void readSections(const QJsonObject &json);


private:
    QJsonObject m_JConfSections;


};

#endif // CONFIGURATOR_H
