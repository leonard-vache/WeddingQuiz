#ifndef QUESTION_H
#define QUESTION_H

#include "common.h"
#include <QString>
#include <QObject>
#include <QJsonObject>


class Question : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     id      READ id      NOTIFY idChanged);
    Q_PROPERTY(QString team    READ team    NOTIFY teamChanged);
    Q_PROPERTY(QString heading READ heading NOTIFY headingChanged);

public:
    Question(QObject *parent = nullptr);
    Question(const Question &copy);

    virtual void readConfiguration(const QJsonObject &json);

    // Getters
    int id() const { return m_id; }
    const QString& team() const { return m_team; }
    const QString& heading() const { return m_heading; }

    // Setters
    void setId(int id) { m_id = id; emit idChanged(); }
    void setTeam(const QString& team) { m_team = team; emit teamChanged(); }
    void setHeading(const QString& heading) { m_heading = heading; emit headingChanged(); }


protected:
    int m_id;
    QString m_team;
    QString m_heading;


signals:
    void idChanged();
    void teamChanged();
    void headingChanged();

};

#endif // QUESTION_H
