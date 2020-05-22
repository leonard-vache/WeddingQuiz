#ifndef QUESTIONSLIST_H
#define QUESTIONSLIST_H

#include "common.h"

#include <QObject>
#include <QVector>
#include <QQmlListProperty>
#include <QMap>
#include <QEvent>

class Question;
class MultipleChoicesQuestion;

class QuestionsList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MultipleChoicesQuestion* mcq READ mcq NOTIFY mcqChanged)

//    Q_PROPERTY(QVector<MultipleChoicesQuestion> mcq READ mcq NOTIFY mcqChanged);

public:
    explicit QuestionsList(QObject *parent = nullptr);
    ~QuestionsList();
    QuestionsList(const QuestionsList& copy);
    QuestionsList& operator=(const QuestionsList &copy);

    Q_INVOKABLE void next();


//    void add(QuestionTypes type, Question* q);
    void add(QuestionTypes type, Question* q);
    void addReward(QuestionTypes type, int value);

    // Getters
    MultipleChoicesQuestion* mcq();

private:
    QMap<QuestionTypes, int> m_rewards;
    QList<MultipleChoicesQuestion> m_mcq;
    int m_currentId;


signals:
    void mcqChanged();
};



#endif // QUESTIONSLIST_H
