#include "multiple_choices_question.h"
#include "question.h"

#include <QJsonArray>

MultipleChoicesQuestion::MultipleChoicesQuestion(QObject *parent) : Question(parent)
{
    setSuggestionIndex(-1);
    setShowAnswer(false);
}

MultipleChoicesQuestion::~MultipleChoicesQuestion() {}

MultipleChoicesQuestion::MultipleChoicesQuestion(const MultipleChoicesQuestion &copy)
{
    m_heading = copy.m_heading;
    m_content = copy.m_content;
    m_answer = copy.m_answer;
    m_suggestions = copy.m_suggestions;
    m_suggestionIndex = copy.m_suggestionIndex;
    m_showAnswer = copy.m_showAnswer;
}

MultipleChoicesQuestion& MultipleChoicesQuestion::operator=(const MultipleChoicesQuestion &copy)
{
    m_heading = copy.m_heading;
    m_content = copy.m_content;
    m_answer = copy.m_answer;
    m_suggestions = copy.m_suggestions;
    m_suggestionIndex = copy.m_suggestionIndex;
    m_showAnswer = copy.m_showAnswer;
    return *this;
}


void MultipleChoicesQuestion::readConfiguration(const QJsonObject &json)
{
    Question::readConfiguration(json);

    if(json.contains("answer"))
        setAnswer(json["answer"].toInt());


    if(json.contains("suggestions") && json["suggestions"].isArray())
    {
        m_suggestions.clear();
        QVector<QString> sug;
        QJsonArray sug_array = json["suggestions"].toArray();
        for (int idx = 0; idx < sug_array.size(); ++idx)
            sug.append(sug_array[idx].toString());

        setSuggestions(sug);
    }

    if(json.contains("content"))
        setContent(json["content"].toString());

}



bool MultipleChoicesQuestion::allSuggestionsShowed()
{
    return m_suggestionIndex == m_suggestions.length()-1;
}


bool MultipleChoicesQuestion::isNextable() const
{
    return m_showAnswer;
}


bool MultipleChoicesQuestion::showContent() const
{
    return m_content.isEmpty() == false && m_suggestionIndex == -1;
}


bool MultipleChoicesQuestion::isReturnable() const
{
    return m_suggestionIndex == -1;
}



bool MultipleChoicesQuestion::next()
{

    if(m_suggestionIndex < m_suggestions.length()-1)
    {
        setSuggestionIndex(m_suggestionIndex + 1);
        return true;
    }

    return false;
}


bool MultipleChoicesQuestion::previous()
{
    if(m_suggestionIndex >= 0)
    {
        setSuggestionIndex(m_suggestionIndex - 1);
        setShowAnswer(false);
        return true;
    }

    return false;
}


bool MultipleChoicesQuestion::enter()
{
    if(false == m_showAnswer )
    {
        if( allSuggestionsShowed() )
        {
            setShowAnswer(true);
            return true;
        }
    }
    else
    {
        setShowAnswer(false);
        return true;
    }

    return false;
}



