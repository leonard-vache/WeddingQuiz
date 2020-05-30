#ifndef QUESTION_H
#define QUESTION_H

#include "common.h"
#include <QString>
#include <QObject>
#include <QJsonObject>


class Question : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString heading READ heading NOTIFY headingChanged);

public:
    Question(QObject *parent = nullptr);
    Question(const Question &copy);

    virtual void readConfiguration(const QJsonObject &json);

    virtual bool isNextable() const { return true; }
    virtual bool isReturnable() const { return true; }

    virtual void previous() {}
    virtual void next() {}
    virtual void enter() {}

    // Getters
    const QString& heading() const { return m_heading; }

    // Setters
    void setHeading(const QString& heading) { m_heading = heading; emit headingChanged(); }


protected:
    QString m_heading;


signals:
    void headingChanged();

};

#endif // QUESTION_H
