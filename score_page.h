#ifndef SCOREPAGE_H
#define SCOREPAGE_H

#include "common.h"
#include "page_interface.h"

#include <QObject>
#include <QQmlListProperty>
#include <QJsonObject>
#include <QString>
#include <QMap>
#include <QVector>



class Team: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged);
    Q_PROPERTY(int score READ score NOTIFY scoreChanged);

public:
    explicit Team(QObject *parent = nullptr);
    Team(const Team &copy);
    Team& operator=(const Team &copy);

    const QString& name() const { return m_name; }
    void setName(const QString& name) { m_name = name; emit nameChanged(); }

    int score() const { return m_score; }
    void setScore(int score) { m_score = score; emit scoreChanged(); }
    void increaseScore(int delta) { setScore(m_score+delta); }

    Common::KeyEvents getKey() const { return m_key; }
    void setKey(Common::KeyEvents key) { m_key = key; }

private:
    QString m_name;
    Common::KeyEvents m_key;
    int m_score;


signals:
    void nameChanged();
    void scoreChanged();

};


//class MessageBoard : public QObject
//{
//    Q_OBJECT
//    Q_PROPERTY(QQmlListProperty<Message> messages READ messages)
//public:
//    QQmlListProperty<Message> messages();

//private:
//    static void append_message(QQmlListProperty<Message> *list, Message *msg);

//    QList<Message *> m_messages;
//};

class ScorePage : public PageInterface
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Team> teams READ teams NOTIFY teamsChanged)
//    Q_PROPERTY(QVariant teams READ teams NOTIFY teamsChanged)
public:
    explicit ScorePage(QObject *parent = nullptr);

    void readConfiguration(const QJsonObject &json);

    // Accessors
    Common::ScoreState getState() const { return m_state; }
    void setState(Common::ScoreState state) { m_state = state; unselectTeam(); }

    void selectTeam(Common::KeyEvents key);
    void unselectTeam() { m_currentTeamIndex = -1; }
    bool isTeamSelected() { return m_currentTeamIndex != -1; }
    void increaseCurrentTeamScore(int delta);

    QQmlListProperty<Team> teams();
    void addTeam(const QString& name, Common::KeyEvents key);

    void clearTeams() { m_teams.clear(); }
    Team* team(int i) { return &(m_teams[i]); }
    int teamCount() const { return m_teams.count(); }



private:
    static void addTeam(QQmlListProperty<Team>*, Team*);
    static int teamCount(QQmlListProperty<Team>*);
    static Team* team(QQmlListProperty<Team>*, int);
    static void clearTeams(QQmlListProperty<Team>*);



private:
    Common::ScoreState m_state;

    int m_currentTeamIndex;
    QVector<Team> m_teams;


signals:
    void teamsChanged();

};

#endif // SCOREPAGE_H
