#ifndef QuestionPage_H
#define QuestionPage_H

#include "common.h"
#include "page_interface.h"

#include <QObject>
#include <QMap>
#include <QJsonObject>


class QuestionContent;
class Question;
class MultipleChoicesQuestion;
class QuickQuestion;


class QuestionsPage : public PageInterface
{
    Q_OBJECT
    Q_PROPERTY(MultipleChoicesQuestion* mcq READ mcq NOTIFY mcqChanged)
    Q_PROPERTY(QuickQuestion* qq READ qq NOTIFY qqChanged)
    Q_PROPERTY(Common::QuestionTypes currentQuestion READ currentQuestion NOTIFY currentQuestionChanged)


public:
    explicit QuestionsPage(QObject *parent = nullptr);
    ~QuestionsPage();
    QuestionsPage(const QuestionsPage& copy);
    QuestionsPage& operator=(const QuestionsPage &copy);


    void readConfiguration(const QJsonObject &json);
    void next();
    void enter();
    void previous();

    void addReward(Common::QuestionTypes type, int value);
    int getCurrentReward() const;
    Question *getCurrentQuestion();

    // Getters
    MultipleChoicesQuestion *mcq();
    QuickQuestion *qq();
    Common::QuestionTypes currentQuestion() { return m_qType[m_qIndex]; }



private:
    void readMCQConfiguration(const QJsonObject &json);
    void readQQConfiguration(const QJsonObject &json);
    void updateCurrentQuestion();
    void nextQuestion();
    void previousQuestion();


private:
    QMap<Common::QuestionTypes, int> m_rewards;
    Common::QuestionTypes m_currentQuestion;
    QList<Question*> m_qList;
    QList<Common::QuestionTypes> m_qType;
    int m_qIndex;


signals:
    void mcqChanged();
    void qqChanged();
    void currentQuestionChanged();
};



#endif // QuestionPage_H
