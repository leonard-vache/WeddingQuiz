#ifndef QUICKQUESTION_H
#define QUICKQUESTION_H

#include "question.h"


class QuickQuestion : public Question
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged);

public:
    QuickQuestion(QObject *parent=nullptr);
    ~QuickQuestion();
    QuickQuestion(const QuickQuestion &copy);
    QuickQuestion& operator=(const QuickQuestion &copy);

//    void readConfiguration(const QJsonObject &json);

    const QString& title() const { return m_title; }
    void setTitle(const QString& title) { m_title = title; emit titleChanged(); }


private:
    QString m_title;


signals:
    void titleChanged();

};

#endif // QUICKQUESTION_H
