#include "score_page.h"

#include <QJsonArray>
#include <QVariantList>
#include <QVariantMap>

TeamObject::TeamObject(QObject *parent): QObject(parent),
    m_score(0)
{
}

TeamObject::TeamObject(const TeamObject &copy)
{
   m_name = copy.m_name;
   m_key = copy.m_key;
   m_score = copy.m_score;
}

TeamObject& TeamObject::operator=(const TeamObject &copy)
{
    m_name = copy.m_name;
    m_key = copy.m_key;
    m_score = copy.m_score;
    return *this;
}



/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/


ScorePage::ScorePage(QObject *parent) : PageInterface(parent),
    m_state(E_STATE_DISPLAY), m_currentTeamIndex(-1)
{
}


void ScorePage::readConfiguration(const QJsonObject &json)
{
//    if (json.contains("teams") && json["teams"].isObject())
    if (json.contains("teams") && json["teams"].isArray())
    {
//        QJsonObject jteams = json["teams"].toObject();
        QJsonArray jteams = json["teams"].toArray();
        for (int i = 0; i < jteams.size(); ++i)
        {
            QJsonObject t_obj = jteams[i].toObject();
            KeyEvents k;

            if(t_obj["key"].toString() == "next")
                k = E_KEY_NEXT;
            if(t_obj["key"].toString() == "return")
                k = E_KEY_RETURN;

            addTeam(t_obj["name"].toString(), k);
        }

        qInfo() << teamCount();
    }
}


void ScorePage::addTeam(const QString& name, KeyEvents key)
{
    TeamObject team;
    team.setName(name);
    team.setKey(key);
    m_teams.append(team);
    emit teamsChanged();
}


void ScorePage::selectTeam(KeyEvents key)
{
    for(int i = 0; i < m_teams.count() ; ++i)
    {
        qInfo() << key << " " << m_teams[i].getKey();
        if( key == m_teams[i].getKey())
        {
            qInfo() << "  > Team selected " << m_teams[i].name();
            m_currentTeamIndex = i;
            break;
        }
    }
}


void ScorePage::increaseCurrentTeamScore(int delta)
{
    qInfo() << "Increase Score";
    qInfo() << "Count index " << teamCount();
    qInfo() << "Current index " << m_currentTeamIndex;
    qInfo() << "Current score " << m_teams[m_currentTeamIndex].score();
    m_teams[m_currentTeamIndex].increaseScore(delta);
}



QQmlListProperty<TeamObject> ScorePage::teams()
{
    return {this, this,
             &ScorePage::addTeam,
             &ScorePage::teamCount,
             &ScorePage::team,
             &ScorePage::clearTeams};
}


void ScorePage::addTeam(QQmlListProperty<TeamObject>* list, TeamObject* p) {
    reinterpret_cast< ScorePage* >(list->data)->addTeam(p->name(), p->getKey());
}

void ScorePage::clearTeams(QQmlListProperty<TeamObject>* list) {
    reinterpret_cast< ScorePage* >(list->data)->clearTeams();
}

TeamObject* ScorePage::team(QQmlListProperty<TeamObject>* list, int i) {
    return reinterpret_cast< ScorePage* >(list->data)->team(i);
}

int ScorePage::teamCount(QQmlListProperty<TeamObject>* list) {
    return reinterpret_cast< ScorePage* >(list->data)->teamCount();
}


//QVariant ScorePage::teams() const
//{
//    QVariantList itemsList;

//    for(const TeamObject &p : m_teams)
//    {
//        QVariantMap itemMap;
//        itemMap.insert("name", p.name());
//        itemMap.insert("score", p.score());
//        itemsList.append(itemMap);
//    }

//    return QVariant::fromValue(itemsList);
//}

