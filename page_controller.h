#ifndef PAGECONTROLLER_H
#define PAGECONTROLLER_H

#include "common.h"
#include <QObject>
#include <QMap>

class PageInterface;
class JinglePage;
class ScorePage;
class QuestionsPage;


enum WQPage {
    E_PAGE_JINGLE,
    E_PAGE_SCORE,
    E_PAGE_QUESTION,
};


class PageController: public QObject
{
public:
    explicit PageController(QObject *parent = nullptr);

    void setupPages(JinglePage *jp, ScorePage *sp, QuestionsPage* qp);
    void updatePage();

    // Remote Controller callback
    void onKeyEvent(KeyEvents key);


private:
    void changePage(WQPage page);

    void updateTitle();
    void updateScore();
    void updateQuestion();
    void updateJingle();



private:
    KeyEvents m_keyEvent;
    WQPage m_currentPage;

    QMap<WQPage,PageInterface*> m_pages;
    JinglePage *m_pJingle;
    ScorePage *m_pScore;
    QuestionsPage *m_pQuestion;

};

#endif // PAGECONTROLLER_H
