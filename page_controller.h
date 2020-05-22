#ifndef PAGECONTROLLER_H
#define PAGECONTROLLER_H

#include "common.h"
#include <QObject>
#include <QMap>

class PageInterface;
class TitlePage;
class ScorePage;
class JinglePage;


enum WQPage {
    E_PAGE_TITLE,
    E_PAGE_JINGLE,
    E_PAGE_SCORE,
    E_PAGE_QUESTION,
};


class PageController: public QObject
{
public:
    explicit PageController(QObject *parent = nullptr);

    void setupPages(TitlePage *tp, JinglePage *jp, ScorePage *sp);
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
    ScorePage *m_pScore;
    JinglePage *m_pJingle;
    TitlePage *m_pTitle;

};

#endif // PAGECONTROLLER_H
