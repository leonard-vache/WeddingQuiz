#include "questions_list.h"
#include "question.h"
#include "multiple_choices_question.h"


QuestionsList::QuestionsList(QObject *parent) : QObject(parent), m_currentId(0)
{
//    m_mcq.append(new MultipleChoicesQuestion());
//    emit mcqChanged();
}


QuestionsList::~QuestionsList()
{
}


QuestionsList::QuestionsList(const QuestionsList& copy)
{
    m_mcq = copy.m_mcq;
}


QuestionsList& QuestionsList::operator=(const QuestionsList &copy)
{
    m_mcq = copy.m_mcq;
    return *this;
}


void QuestionsList::add(QuestionTypes type, Question* q)
{
    if(type == MultipleChoices)
    {
        MultipleChoicesQuestion *new_q = dynamic_cast<MultipleChoicesQuestion*>(q);
        m_mcq.append(*new_q);
        emit mcqChanged();
    }
}


void QuestionsList::addReward(QuestionTypes type, int value)
{
    m_rewards[type] = value;
}


MultipleChoicesQuestion* QuestionsList::mcq()
{
    return &m_mcq[m_currentId];
}


void QuestionsList::next()
{
    if(m_currentId < m_mcq.length()){
        m_currentId++;
        emit mcqChanged();
    }
}



