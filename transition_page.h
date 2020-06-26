#ifndef TRANSITIONPAGE_H
#define TRANSITIONPAGE_H

#include <QMap>
#include <QJsonObject>
#include "common.h"
#include "page_interface.h"


class TransitionPage : public PageInterface
{
    Q_OBJECT
    Q_PROPERTY(QString imageSource READ imageSource NOTIFY imageSourceChanged);

public:
    TransitionPage(QObject *parent = nullptr);

    QString imageSource() { return m_sourceByQuestion[m_currentQuestion]; }
    void setQuestionTransition(Common::QuestionTypes q) { m_currentQuestion = q; emit imageSourceChanged(); }

    void readConfiguration(const QJsonObject &json);


private:
    QMap<Common::QuestionTypes, QString> m_sourceByQuestion;
    Common::QuestionTypes m_currentQuestion;


signals:
    void imageSourceChanged();

};


#endif // TRANSITIONPAGE_H
