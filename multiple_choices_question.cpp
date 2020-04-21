#include "question.h"
#include "multiple_choices_question.h"

#include <QJsonArray>

MultipleChoicesQuestion::MultipleChoicesQuestion(QObject *parent) : Question(parent),
    m_answer(3)
{
}

MultipleChoicesQuestion::~MultipleChoicesQuestion() {}

MultipleChoicesQuestion::MultipleChoicesQuestion(const MultipleChoicesQuestion &copy)
{
    m_id = copy.m_id;
    m_team = copy.m_team;
    m_heading = copy.m_heading;
    m_answer = copy.m_answer;
    m_content = copy.m_content;
    m_suggestions = copy.m_suggestions;
}

MultipleChoicesQuestion& MultipleChoicesQuestion::operator=(const MultipleChoicesQuestion &copy)
{
    m_id = copy.m_id;
    m_team = copy.m_team;
    m_heading = copy.m_heading;
    m_answer = copy.m_answer;
    m_content = copy.m_content;
    m_suggestions = copy.m_suggestions;
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


    qDebug().nospace() << "id=" << id() << " heading=" << m_heading;
}


