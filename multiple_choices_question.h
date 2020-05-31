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
    Q_PROPERTY(int suggestionIndex READ suggestionIndex NOTIFY suggestionIndexChanged);
    Q_PROPERTY(bool showAnswer READ showAnswer NOTIFY showAnswerChanged);

public:
    MultipleChoicesQuestion(QObject *parent = nullptr);
    ~MultipleChoicesQuestion();
    MultipleChoicesQuestion(const MultipleChoicesQuestion &copy);
    MultipleChoicesQuestion& operator=(const MultipleChoicesQuestion &copy);

    void readConfiguration(const QJsonObject &json);
    bool isNextable() const;
    bool isReturnable() const;
    void previous();
    void next();
    void enter();

    bool allSuggestionsShowed();

    // Getters
    const QString& team() const { return m_team; }
    int answer() const { return m_answer; }
    const QString& content() const { return m_content; }
    const QVector<QString>& suggestions() const { return m_suggestions; }
    int suggestionIndex() const { return m_suggestionIndex; }
    bool showAnswer() const { return m_showAnswer; }

    // Setters
    void setTeam(const QString& team) { m_team = team; emit teamChanged(); }
    void setAnswer(int answer) { m_answer = answer; emit answerChanged(); }
    void setContent(const QString& content) { m_content = content; emit contentChanged(); }
    void setSuggestions(const QVector<QString>& suggestions) { m_suggestions = suggestions; emit suggestionsChanged(); }
    void setSuggestionIndex(int index) { m_suggestionIndex = index; emit suggestionIndexChanged(); }
    void setShowAnswer(bool show) { m_showAnswer = show; emit showAnswerChanged(); }


private:
    QString m_team;
    int m_answer;
    QString m_content;
    QVector<QString> m_suggestions;

    int m_suggestionIndex;
    bool m_showAnswer;

signals:
    void teamChanged();
    void answerChanged();
    void contentChanged();
    void suggestionsChanged();
    void suggestionIndexChanged();
    void showAnswerChanged();
};

Q_DECLARE_METATYPE(MultipleChoicesQuestion);

#endif // MULTIPLECHOICESQUESTION_H
