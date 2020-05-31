#include "questions_page.h"

#include "question.h"
#include "quick_question.h"
#include "multiple_choices_question.h"

#include <QJsonArray>


QuestionsPage::QuestionsPage(QObject *parent) : PageInterface(parent),
    m_currentQuestion(E_MULTIPLE_CHOICE), m_qIndex(0)
{
}


QuestionsPage::~QuestionsPage()
{
    for( int i = 0; i < m_qList.count(); ++i)
        delete m_qList[i];
}


QuestionsPage::QuestionsPage(const QuestionsPage& copy)
{
    m_qType = copy.m_qType;
    m_qList = copy.m_qList;
    m_qIndex = copy.m_qIndex;

}


QuestionsPage& QuestionsPage::operator=(const QuestionsPage &copy)
{
    m_qType = copy.m_qType;
    m_qList = copy.m_qList;
    m_qIndex = copy.m_qIndex;
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
                    MultipleChoicesQuestion *mcq = new MultipleChoicesQuestion();
                    mcq->readConfiguration(q_array[idx].toObject());

                    m_qList.append(mcq);
                    m_qType.append(E_MULTIPLE_CHOICE);

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

        QString title;
        if(q_json.contains("title"))
            title = q_json["title"].toString();

        if (q_json.contains("QuestionsList") && q_json["QuestionsList"].isArray())
        {
            QJsonArray q_array = q_json["QuestionsList"].toArray();
            for (int idx = 0; idx < q_array.size(); ++idx)
            {
                if (q_array[idx].isObject())
                {
                    QuickQuestion* qq = new QuickQuestion();
                    qq->readConfiguration(q_array[idx].toObject());
                    qq->setTitle(title);

                    m_qList.append(qq);
                    m_qType.append(E_QUICK);
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
    return  dynamic_cast<MultipleChoicesQuestion*>(m_qList[m_qIndex]);
}


QuickQuestion* QuestionsPage::qq()
{
    return  dynamic_cast<QuickQuestion*>(m_qList[m_qIndex]);
}


//Question* QuestionsPage::getCurrentQuestion()
//{
//    if( m_currentQuestion == E_MULTIPLE_CHOICE )
//        return mcq();
//    else if ( m_currentQuestion == E_QUICK )
//        return qq();
//    else
//        qWarning() << "Unknown question" << m_currentQuestion;
//        return nullptr;
//}


int QuestionsPage::getCurrentReward() const
{
    return m_rewards[m_qType[m_qIndex]];
}


void QuestionsPage::next()
{    
    if( m_qList[m_qIndex]->isNextable() )
        nextQuestion();
    else
        m_qList[m_qIndex]->next();
}


void QuestionsPage::previous()
{
    if( m_qList[m_qIndex]->isReturnable() )
        previousQuestion();
    else
        m_qList[m_qIndex]->previous();
}


void QuestionsPage::enter()
{
    m_qList[m_qIndex]->enter();
}


void QuestionsPage::previousQuestion()
{
    if( m_qIndex > 0 )
    {
        m_qIndex --;
        updateCurrentQuestion();
    }
}


void QuestionsPage::nextQuestion()
{
    if( m_qIndex <  m_qList.count() -1)
    {
        m_qIndex ++;
        updateCurrentQuestion();
    }
}


void QuestionsPage::updateCurrentQuestion()
{
    switch(m_qType[m_qIndex])
    {
    case E_MULTIPLE_CHOICE:
        emit mcqChanged();
        break;

    case E_QUICK:
        emit qqChanged();
        break;
    }

    emit currentQuestionChanged();
}

