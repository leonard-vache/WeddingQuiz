#ifndef QUESTIONDECORATOR_H
#define QUESTIONDECORATOR_H

#include "question.h"


class QuestionDecorator : public Question
{
public:
    QuestionDecorator(QObject *parent=nullptr) : Question(parent) {}

    void readConfiguration(const QJsonObject &json) { m_question->readConfiguration(json); }

    bool isNextable() const { return m_question->isNextable(); }
    bool isReturnable() const { return m_question->isReturnable(); }

    void previous() { m_question->previous(); }
    void next() { m_question->next(); }
    void enter() { m_question->enter(); }

    Question * getQuestion() { return m_question; }

protected:
    Question *m_question;
};



class QuestionWithVideoContent : public QuestionDecorator
{
public:
    QuestionWithVideoContent(QObject *parent=nullptr);
};


class QuestionWithImageContent : public QuestionDecorator
{
public:
    QuestionWithImageContent(QObject *parent=nullptr);
};


#endif // QUESTIONDECORATOR_H
