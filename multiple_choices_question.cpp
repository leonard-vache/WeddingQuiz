#include "multiple_choices_question.h"
#include "question.h"

#include <QJsonArray>

MultipleChoicesQuestion::MultipleChoicesQuestion(QObject *parent) : Question(parent),
    m_answer(3)
{
    setSuggestionIndex(-1);
}

MultipleChoicesQuestion::~MultipleChoicesQuestion() {}

MultipleChoicesQuestion::MultipleChoicesQuestion(const MultipleChoicesQuestion &copy)
{
    m_heading = copy.m_heading;
    m_content = copy.m_content;
    m_team = copy.m_team;
    m_answer = copy.m_answer;
    m_suggestions = copy.m_suggestions;
    m_suggestionIndex = copy.m_suggestionIndex;
    m_showAnswer = copy.m_showAnswer;
}

MultipleChoicesQuestion& MultipleChoicesQuestion::operator=(const MultipleChoicesQuestion &copy)
{
    m_heading = copy.m_heading;
    m_content = copy.m_content;
    m_team = copy.m_team;
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

    if(json.contains("team"))
        setTeam(json["team"].toString());

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
    qInfo() << "m_suggestionIndex" << m_suggestionIndex << " " << m_suggestions.length()-1;
    return m_suggestionIndex == m_suggestions.length()-1;
}


bool MultipleChoicesQuestion::isNextable() const
{
    return m_showAnswer;
}

bool MultipleChoicesQuestion::isReturnable() const
{
    return m_suggestionIndex == -1;
}



void MultipleChoicesQuestion::next()
{
    qInfo() << "In MCQ next" << m_suggestionIndex;
    if(m_suggestionIndex < m_suggestions.length()-1)
        setSuggestionIndex(m_suggestionIndex + 1);
}


void MultipleChoicesQuestion::previous()
{
    qInfo() << "In MCQ previous" << m_suggestionIndex;
    if(m_suggestionIndex >= 0)
    {
        setSuggestionIndex(m_suggestionIndex - 1);
        setShowAnswer(false);
    }

}


void MultipleChoicesQuestion::enter()
{
    qInfo() << "enter in" << m_showAnswer;

    if(false == m_showAnswer )
    {
        if( allSuggestionsShowed() )
            setShowAnswer(true);
    }
    else
    {
        setShowAnswer(false);
    }

    qInfo() << "enter out" << m_showAnswer;

}



