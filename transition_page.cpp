#include "transition_page.h"

using namespace Common;

TransitionPage::TransitionPage(QObject *parent): PageInterface(parent)
{
}


void TransitionPage::readConfiguration(const QJsonObject &json)
{
    if (json.contains("MultipleChoicesQuestions") == true )
        m_sourceByQuestion[E_MULTIPLE_CHOICE_QUESTION] = json["MultipleChoicesQuestions"].toString();

    if (json.contains("QuickQuestions") == true )
        m_sourceByQuestion[E_QUICK_QUESTION] = json["QuickQuestions"].toString();
}
