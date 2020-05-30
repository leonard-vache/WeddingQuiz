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

    m_questionIdToIndex = copy.m_questionIdToIndex;
    m_globalQuestionId = copy.m_globalQuestionId;
    m_mcqId = copy.m_mcqId;
    m_qqId = copy.m_qqId;
}


QuestionsPage& QuestionsPage::operator=(const QuestionsPage &copy)
{
    m_mcq = copy.m_mcq;
    m_qq = copy.m_qq;

    m_questionIdToIndex = copy.m_questionIdToIndex;
    m_globalQuestionId = copy.m_globalQuestionId;
    m_mcqId = copy.m_mcqId;
    m_qqId = copy.m_qqId;
    return *this;
}


void QuestionsPage::readConfiguration(const QJsonObject &json)
{
    int global = m_globalQuestionId;
    m_globalQuestionId = 0;
    readMCQConfiguration(json);
    readQQConfiguration(json);
    m_globalQuestionId = global;
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
                    m_questionIdToIndex[m_globalQuestionId] = m_mcq.length();
                    m_globalQuestionId++;
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
                    m_questionIdToIndex[m_globalQuestionId] = m_qq.length();
                    m_globalQuestionId++;
                    m_qq.append(qq);
                }
                else
                    qWarning() << "QQ index" << idx << "is not an object !" << q_array[idx];
            }
        }
    }
}


void QuestionsPage::addReward(QuestionTypes type, int value)
{
    m_rewards[type] = value;
}


MultipleChoicesQuestion* QuestionsPage::mcq()
{
    int index = m_questionIdToIndex[m_globalQuestionId];
    return &m_mcq[index];
}


QuickQuestion* QuestionsPage::qq()
{
    int index = m_questionIdToIndex[m_globalQuestionId];
    return &m_qq[index];
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
    Question *q = getCurrentQuestion();
    if( q->isNextable() )
        nextQuestion();
    else
        q->next();
}


void QuestionsPage::previous()
{
    Question *q = getCurrentQuestion();
    if( q->isReturnable() )
        previousQuestion();
    else
        q->previous();
}


void QuestionsPage::enter()
{
    qInfo() << "Go to Question Enter";
    Question *q = getCurrentQuestion();
    q->enter();
}


void QuestionsPage::previousQuestion()
{
    if( m_globalQuestionId > 0 )
    {
        m_globalQuestionId --;
        updateCurrentQuestion();
    }
}


void QuestionsPage::nextQuestion()
{
    if( m_globalQuestionId <  m_questionIdToIndex.count() -1)
    {
        m_globalQuestionId ++;
        updateCurrentQuestion();
    }
}


void QuestionsPage::updateCurrentQuestion()
{
    if( m_globalQuestionId < m_mcq.length() )
    {
        setCurrentQuestion(E_MULTIPLE_CHOICE);
        emit mcqChanged();
    }
    else if( m_globalQuestionId < m_qq.length() + m_mcq.length() )
    {
        setCurrentQuestion(E_QUICK);
        emit qqChanged();
    }
}

