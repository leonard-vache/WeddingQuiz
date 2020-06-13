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
    Q_PROPERTY(QString content READ content NOTIFY contentChanged);

public:
    Question(QObject *parent = nullptr);
    Question(const Question &copy);

    virtual void readConfiguration(const QJsonObject &json);

    // Criteria
    virtual bool isNextable() const { return true; } // Go to next question
    virtual bool isReturnable() const { return true; } // Go to previous question
    virtual bool showContent() const { return m_content.isEmpty() == false; }

    virtual bool previous() { return false; }
    virtual bool next() { return false; }
    virtual bool enter() { return false; }

    // Getters
    bool hasContent() { return m_content != ""; }
    const QString& heading() const { return m_heading; }
    const QString& content() const { return m_content; }

    // Setters
    void setHeading(const QString& heading) { m_heading = heading; emit headingChanged(); }
    void setContent(const QString& content) { m_content = content; emit contentChanged(); }


protected:
    QString m_heading;
    QString m_content;


signals:
    void headingChanged();
    void contentChanged();

};



#endif // QUESTION_H
