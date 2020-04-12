#ifndef MULTIPLECHOICESQUESTION_H
#define MULTIPLECHOICESQUESTION_H
#include "question.h"

#include <QObject>
#include <QString>
#include <QVector>

#include <QJsonObject>


class MultipleChoicesQuestion : public Question
{
    Q_OBJECT
    Q_PROPERTY(int     answer  READ answer  NOTIFY answerChanged);
    Q_PROPERTY(QString content READ content NOTIFY contentChanged);
    Q_PROPERTY(QVector<QString> suggestions READ suggestions NOTIFY suggestionsChanged);

public:
    MultipleChoicesQuestion(QObject *parent = nullptr);
    MultipleChoicesQuestion(const MultipleChoicesQuestion &copy);
    MultipleChoicesQuestion& operator=(const MultipleChoicesQuestion &copy);

    void readConfiguration(const QJsonObject &json);

    // Getters
    int answer() const { return m_answer; }
    const QString& content() const { return m_content; }
    const QVector<QString>& suggestions() const { return m_suggestions; }

    // Setters
    void setAnswer(int answer) { m_answer = answer; emit idChanged(); }
    void setContent(const QString& content) { m_content = content; emit contentChanged(); }
    void setSuggestions(const QVector<QString>& suggestions) { m_suggestions = suggestions; emit suggestionsChanged(); }

private:
    int m_answer;
    QString m_content;
    QVector<QString> m_suggestions;

signals:
    void answerChanged();
    void contentChanged();
    void suggestionsChanged();
};

#endif // MULTIPLECHOICESQUESTION_H
