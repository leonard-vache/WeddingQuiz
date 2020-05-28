#ifndef QUICKQUESTION_H
#define QUICKQUESTION_H

#include "question.h"


class QuickQuestion : public Question
{
    Q_OBJECT
public:
    QuickQuestion(QObject *parent=nullptr);
    ~QuickQuestion();
    QuickQuestion(const QuickQuestion &copy);
    QuickQuestion& operator=(const QuickQuestion &copy);

};

#endif // QUICKQUESTION_H
