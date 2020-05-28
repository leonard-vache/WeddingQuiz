#include "questions_page.h"

#include "question.h"
#include "quick_question.h"
#include "multiple_choices_question.h"

#include <QJsonArray>


QuestionsPage::QuestionsPage(QObject *parent) : PageInterface(parent),
    m_currentQuestion(E_MULTIPLE_CHOICE), m_globalQuestionId(0), m_mcqId(0), m_qqId(0)
{
}


QuestionsPage::~QuestionsPage()
{
}


QuestionsPage::QuestionsPage(const QuestionsPage& copy)
{
    m_mcq = copy.m_mcq;
    m_qq = copy.m_qq;

    m_globalQuestionId = copy.m_globalQuestionId;
    m_mcqId = copy.m_mcqId;
    m_qqId = copy.m_qqId;
}


QuestionsPage& QuestionsPage::operator=(const QuestionsPage &copy)
{
    m_mcq = copy.m_mcq;
    m_qq = copy.m_qq;

    m_globalQuestionId = copy.m_globalQuestionId;
    m_mcqId = copy.m_mcqId;
    m_qqId = copy.m_qqId;
    return *this;
}


void QuestionsPage::readConfiguration(const QJsonObject &json)
{
    readMCQConfiguration(json);
    readQQConfiguration(json);
}


void QuestionsPage::readMCQConfiguration(const QJsonObject &json)
{
    if (json.contains("MultipleChoicesQuestions") && json["MultipleChoicesQuestions"].isObject())
    {
        QJsonObject q_json = json["MultipleChoicesQuestions"].toObject();

        if( q_json.contains("reward"))
            addReward(E_MULTIPLE_CHOICE, q_json["reward"].toInt());

        if (q_json.contains("QuestionsList") && q_json["QuestionsList"].isArray())
        {
            QJsonArray q_array = q_json["QuestionsList"].toArray();
            for (int idx = 0; idx < q_array.size(); ++idx)
            {
                if (q_array[idx].isObject())
                {
                    MultipleChoicesQuestion mcq;
                    mcq.readConfiguration(q_array[idx].toObject());
                    m_mcq.append(mcq);
                }
                else
                    qWarning() << "MCQ index" << idx << "is not an object !" << q_array[idx];
            }
        }
    }
}


void QuestionsPage::readQQConfiguration(const QJsonObject &json)
{
    if (json.contains("QuickQuestions") && json["QuickQuestions"].isObject())
    {
        QJsonObject q_json = json["QuickQuestions"].toObject();

        if( q_json.contains("reward"))
            addReward(E_QUICK, q_json["reward"].toInt());

        if (q_json.contains("QuestionsList") && q_json["QuestionsList"].isArray())
        {
            QJsonArray q_array = q_json["QuestionsList"].toArray();
            for (int idx = 0; idx < q_array.size(); ++idx)
            {
                if (q_array[idx].isObject())
                {
                    QuickQuestion qq;
                    qq.readConfiguration(q_array[idx].toObject());
                    m_qq.append(qq);
                }
                else
                    qWarning() << "QQ index" << idx << "is not an object !" << q_array[idx];
            }
        }
    }
}




void QuestionsPage::addMultiplechoiceQuestion(MultipleChoicesQuestion& q)
{
    m_mcq.append(q);
    emit mcqChanged();
}


void QuestionsPage::addQuickQuestion(QuickQuestion& q)
{
    m_qq.append(q);
    emit qqChanged();
}


void QuestionsPage::addReward(QuestionTypes type, int value)
{
    m_rewards[type] = value;
}


MultipleChoicesQuestion* QuestionsPage::mcq()
{
    return &m_mcq[m_mcqId];
}


QuickQuestion* QuestionsPage::qq()
{
    return &m_qq[m_qqId];
}


Question* QuestionsPage::getCurrentQuestion()
{
    if( m_currentQuestion == E_MULTIPLE_CHOICE )
        return mcq();
    else if ( m_currentQuestion == E_QUICK )
        return qq();
    else
        qWarning() << "Unknown question" << m_currentQuestion;
        return nullptr;
}


int QuestionsPage::getCurrentReward() const
{
    return m_rewards[m_currentQuestion];
}



void QuestionsPage::next()
{
    m_globalQuestionId ++;
    if( m_globalQuestionId < m_mcq.length() )
    {
        m_mcqId ++;
        m_currentQuestion = E_MULTIPLE_CHOICE;
        emit currentQuestionChanged();
        emit mcqChanged();
    }
    else if ( m_globalQuestionId < m_qq.length() )
    {
        m_qqId ++;
        m_currentQuestion = E_QUICK;
        emit currentQuestionChanged();
        emit qqChanged();
    }

}




