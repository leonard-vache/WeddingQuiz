#include "question.h"

Question::Question(QObject *parent) : QObject(parent)
{
}

Question::Question(const Question &copy)
{
    m_id = copy.m_id;
    m_team = copy.m_team;
    m_heading = copy.m_team;
}


void Question::readConfiguration(const QJsonObject &json)
{
    if(json.contains("id"))
        setId(json["id"].toInt());

    if(json.contains("team"))
        setTeam(json["team"].toString());

    if(json.contains("heading"))
        setHeading(json["heading"].toString());
}
