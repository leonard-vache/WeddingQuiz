#ifndef PAGECONTROLLER_H
#define PAGECONTROLLER_H

#include "common.h"
#include <QObject>
#include <QMap>

class PageInterface;
class JinglePage;
class ScorePage;
class QuestionsPage;
class ContentPage;
class MenuPage;
class TransitionPage;


class PageController: public QObject
{
public:
    explicit PageController(QObject *parent = nullptr);

    void setupPages(JinglePage *jp, ScorePage *sp, QuestionsPage* qp, MenuPage* mp, ContentPage* cp, TransitionPage* tp);
    void updatePage();

    // Remote Controller callback
    void onKeyEvent(Common::KeyEvents key);

public slots:
    void onCurrentQuestionChanged();
    void onQuestionsEnded();


private:
    void changePage(Common::Page page, bool hide=true);

    void updateTitle();
    void updateScore();
    void updateQuestion();
    void updateJingle();
    void updateMenu();
    void updateContent();
    void updateTransition();



private:
    Common::KeyEvents m_keyEvent;
    Common::Page m_currentPage;
    Common::QuestionTypes m_currentQuestionType;

    QMap<Common::Page,PageInterface*> m_pages;
    JinglePage *m_pJingle;
    ScorePage *m_pScore;
    QuestionsPage *m_pQuestion;
    MenuPage *m_pMenu;
    ContentPage *m_pContent;
    TransitionPage *m_pTransition;

};

#endif // PAGECONTROLLER_H
