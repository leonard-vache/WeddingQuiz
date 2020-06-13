#include "question.h"

Question::Question(QObject *parent) : QObject(parent)
{
}


Question::Question(const Question &copy)
{
    m_heading = copy.m_heading;
    m_content = copy.m_content;
}


void Question::readConfiguration(const QJsonObject &json)
{
    if(json.contains("heading"))
        setHeading(json["heading"].toString());


    if(json.contains("content"))
        setContent(json["content"].toString());

}




/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

