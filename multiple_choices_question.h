#ifndef MULTIPLECHOICESQUESTION_H
#define MULTIPLECHOICESQUESTION_H

#include "question.h"

#include <QString>
#include <QVector>

#include <QJsonObject>


class MultipleChoicesQuestion : public Question
{
    Q_OBJECT
    Q_PROPERTY(QString team    READ team    NOTIFY teamChanged);
    Q_PROPERTY(int     answer  READ answer  NOTIFY answerChanged);
    Q_PROPERTY(QString content READ content NOTIFY contentChanged);
    Q_PROPERTY(QVector<QString> suggestions READ suggestions NOTIFY suggestionsChanged);

public:
    MultipleChoicesQuestion(QObject *parent = nullptr);
    ~MultipleChoicesQuestion();
    MultipleChoicesQuestion(const MultipleChoicesQuestion &copy);
    MultipleChoicesQuestion& operator=(const MultipleChoicesQuestion &copy);

    void readConfiguration(const QJsonObject &json);

    // Getters
    const QString& team() const { return m_team; }
    int answer() const { return m_answer; }
    const QString& content() const { return m_content; }
    const QVector<QString>& suggestions() const { return m_suggestions; }

    // Setters
    void setTeam(const QString& team) { m_team = team; emit teamChanged(); }
    void setAnswer(int answer) { m_answer = answer; emit answerChanged(); }
    void setContent(const QString& content) { m_content = content; emit contentChanged(); }
    void setSuggestions(const QVector<QString>& suggestions) { m_suggestions = suggestions; emit suggestionsChanged(); }

private:
    QString m_team;
    int m_answer;
    QString m_content;
    QVector<QString> m_suggestions;

signals:
    void teamChanged();
    void answerChanged();
    void contentChanged();
    void suggestionsChanged();
};

#endif // MULTIPLECHOICESQUESTION_H
