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


class PageController: public QObject
{
public:
    explicit PageController(QObject *parent = nullptr);

    void setupPages(JinglePage *jp, ScorePage *sp, QuestionsPage* qp, MenuPage* mp, ContentPage* cp);
    void updatePage();

    // Remote Controller callback
    void onKeyEvent(Common::KeyEvents key);


private:
    void changePage(Common::Page page, bool hide=true);

    void updateTitle();
    void updateScore();
    void updateQuestion();
    void updateJingle();
    void updateMenu();
    void updateContent();



private:
    Common::KeyEvents m_keyEvent;
    Common::Page m_currentPage;

    QMap<Common::Page,PageInterface*> m_pages;
    JinglePage *m_pJingle;
    ScorePage *m_pScore;
    QuestionsPage *m_pQuestion;
    MenuPage *m_pMenu;
    ContentPage *m_pContent;

};

#endif // PAGECONTROLLER_H
