#ifndef QuestionPage_H
#define QuestionPage_H

#include "common.h"
#include "page_interface.h"

#include <QObject>
#include <QMap>
#include <QJsonObject>

class Question;
class MultipleChoicesQuestion;
class QuickQuestion;

class QuestionsPage : public PageInterface
{
    Q_OBJECT
    Q_PROPERTY(MultipleChoicesQuestion* mcq READ mcq NOTIFY mcqChanged)
    Q_PROPERTY(QuickQuestion* qq READ qq NOTIFY qqChanged)
    Q_PROPERTY(QuestionTypes currentQuestion READ currentQuestion NOTIFY currentQuestionChanged)

public:
    enum QuestionTypes {
        E_MULTIPLE_CHOICE,
        E_QUICK
    };
    Q_ENUM(QuestionTypes);
//    Q_PROPERTY(QVector<MultipleChoicesQuestion> mcq READ mcq NOTIFY mcqChanged);

public:
    explicit QuestionsPage(QObject *parent = nullptr);
    ~QuestionsPage();
    QuestionsPage(const QuestionsPage& copy);
    QuestionsPage& operator=(const QuestionsPage &copy);

    void next();
    void enter();
    void previous();

    void nextQuestion();
    void previousQuestion();

    void readConfiguration(const QJsonObject &json);
    void readMCQConfiguration(const QJsonObject &json);
    void readQQConfiguration(const QJsonObject &json);

    void addReward(QuestionTypes type, int value);
    int getCurrentReward() const;

    // Getters
    Question* getCurrentQuestion();
    MultipleChoicesQuestion* mcq();
    QuickQuestion* qq();
    QuestionTypes currentQuestion() { return m_currentQuestion; }

private:
    QMap<QuestionTypes, int> m_rewards;
    QList<MultipleChoicesQuestion> m_mcq;
    QList<QuickQuestion> m_qq;

    QuestionTypes m_currentQuestion;
    int m_globalQuestionId;
    int m_mcqId;
    int m_qqId;


signals:
    void mcqChanged();
    void qqChanged();
    void currentQuestionChanged();
};



#endif // QuestionPage_H
