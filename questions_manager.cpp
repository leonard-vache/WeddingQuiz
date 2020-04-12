#include "questions_manager.h"
#include "question.h"
#include "multiple_choices_question.h"

#include <QtDebug>
#include <QByteArray>

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>


QuestionsManager::QuestionsManager() {}

QuestionsManager::~QuestionsManager()
{
    QVector<Question*>::iterator it;
    for (it = m_questionsList.begin(); it != m_questionsList.end(); ++it)
    {
        delete *it;
    }
    m_questionsList.clear();
}


QuestionsManager::QuestionsManager(const QuestionsManager &copy)
{
    m_questionsList = copy.m_questionsList;
}

QuestionsManager& QuestionsManager::operator=(const QuestionsManager &copy)
{
    m_questionsList = copy.m_questionsList;
    return *this;
}

int QuestionsManager::getReward(QuestionTypes type) const
{
    return m_rewards[type];
}

Question* QuestionsManager::getQuestion(int id) const
{
    QVector<Question*>::const_iterator it;
    for (it = m_questionsList.cbegin(); it != m_questionsList.cend(); ++it)
    {
        if((*it)->id() == id)
            return *it;
    }
}


bool QuestionsManager::loadConfigurationFile(const QString &qrcFilePath)
{
    QFile config_file(":/" + qrcFilePath);
    if (!config_file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Couldn't open JSON file:" << "qrc:/" + qrcFilePath;
        return false;
    }

    QByteArray config_data = config_file.readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(config_data, &error);
    if(doc.isNull())
    {
        qCritical() << "Invalid JSON document : " << error.errorString();  // https://jsonformatter.curiousconcept.com/
        return false;
    }

    readConfiguration(doc.object());

    return true;
}


void QuestionsManager::readConfiguration(const QJsonObject &json)
{
    if (json.contains("MultipleChoicesQuestions") && json["MultipleChoicesQuestions"].isObject())
    {
        QJsonObject mcq_json = json["MultipleChoicesQuestions"].toObject();

        if( mcq_json.contains("reward"))
            m_rewards[MultipleChoices] = mcq_json["reward"].toInt();

        if (mcq_json.contains("QuestionsList") && mcq_json["QuestionsList"].isArray())
        {
            m_questionsList.clear();
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
        MultipleChoicesQuestion *mcq = new MultipleChoicesQuestion();
        mcq->readConfiguration(json);
        m_questionsList.append(mcq);
    }
}


