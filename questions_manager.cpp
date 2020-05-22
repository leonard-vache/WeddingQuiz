#include "questions_manager.h"
#include "question.h"
#include "multiple_choices_question.h"
#include "questions_list.h"

#include <QByteArray>

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>


QuestionsManager::QuestionsManager()
{
    m_questionsList = new QuestionsList();
}

QuestionsManager::~QuestionsManager()
{
    delete m_questionsList;
//    QVector<Question*>::iterator it;
//    for (it = m_questionsList.begin(); it != m_questionsList.end(); ++it)
//    {
//        delete *it;
//    }
//    m_questionsList.clear();
}


QuestionsManager::QuestionsManager(const QuestionsManager &copy)
{
    m_questionsList = copy.m_questionsList;
}


QuestionsManager& QuestionsManager::operator=(const QuestionsManager &copy)
{
    *m_questionsList = *copy.m_questionsList;
    return *this;
}


QuestionsList* QuestionsManager::getQuestionList()
{
    return m_questionsList;
}

//Question* QuestionsManager::getQuestion(int id) const
//{
//    QVector<Question*>::const_iterator it;
//    for (it = m_questionsList.cbegin(); it != m_questionsList.cend(); ++it)
//    {
//        if((*it)->id() == id)
//            return *it;
//    }

//    qCritical() << "Error: Question" << id << "not found !";
//    return nullptr;

//}



void QuestionsManager::readConfiguration(const QJsonObject &json)
{
    if (json.contains("MultipleChoicesQuestions") && json["MultipleChoicesQuestions"].isObject())
    {
        QJsonObject mcq_json = json["MultipleChoicesQuestions"].toObject();

        if( mcq_json.contains("reward"))
            m_questionsList->addReward(MultipleChoices, mcq_json["reward"].toInt());

        if (mcq_json.contains("QuestionsList") && mcq_json["QuestionsList"].isArray())
        {
            QJsonArray mcq_array = mcq_json["QuestionsList"].toArray();
            for (int idx = 0; idx < mcq_array.size(); ++idx)
            {
                if (mcq_array[idx].isObject())
                {
                    createQuestion(MultipleChoices, mcq_array[idx].toObject());
                }
                else
                    qWarning() << "QuestionsList index" << idx << "is not an object !" << mcq_array[idx];
            }
        }
    }
}


void QuestionsManager::createQuestion(QuestionTypes type, const QJsonObject &json)
{
    if( type == MultipleChoices) {
//        MultipleChoicesQuestion *mcq = new MultipleChoicesQuestion();
//        mcq->readConfiguration(json);
//        m_questionsList->add(type, mcq);

        MultipleChoicesQuestion mcq;
        mcq.readConfiguration(json);
        m_questionsList->add(type, &mcq);
    }
}




