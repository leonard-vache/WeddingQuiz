#include "quick_question.h"


QuickQuestion::QuickQuestion(QObject *parent) : Question(parent)
{
}

QuickQuestion::~QuickQuestion() {}


QuickQuestion::QuickQuestion(const QuickQuestion &copy)
{
    m_heading = copy.m_heading;;
}

QuickQuestion& QuickQuestion::operator=(const QuickQuestion &copy)
{
    m_heading = copy.m_heading;
    return *this;
}


