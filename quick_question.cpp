#include "quick_question.h"


QuickQuestion::QuickQuestion(QObject *parent) : Question(parent)
{
}

QuickQuestion::~QuickQuestion() {}


QuickQuestion::QuickQuestion(const QuickQuestion &copy)
{
    m_heading = copy.m_heading;
    m_title = copy.m_title;
}

QuickQuestion& QuickQuestion::operator=(const QuickQuestion &copy)
{
    m_heading = copy.m_heading;
    m_title = copy.m_title;
    return *this;
}

