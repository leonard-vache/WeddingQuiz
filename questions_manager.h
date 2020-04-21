#ifndef QUESTIONSMANAGER_H
#define QUESTIONSMANAGER_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QJsonObject>

#include "common.h"

class Question;
class QuestionsList;

class QuestionsManager
{

public:

    QuestionsManager();
    ~QuestionsManager();

    QuestionsManager(const QuestionsManager &copy);
    QuestionsManager& operator=(const QuestionsManager &copy);

    bool loadConfigurationFile(const QString &qrcFilePath);
    void readConfiguration(const QJsonObject &json);

//    Question* getQuestion(int id) const;

    int getReward(QuestionTypes type) const;

    QuestionsList* getQuestionList();


private:
    void createQuestion(QuestionTypes type, const QJsonObject &json);


private:
//    QMap<QuestionTypes, int> m_rewards;
//    QVector<Question*> m_questionsList;
    QuestionsList *m_questionsList;

};


#endif // QUESTIONSMANAGER_H
