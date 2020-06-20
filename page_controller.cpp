#include "page_controller.h"

#include "question.h"
#include "jingle_page.h"
#include "score_page.h"
#include "questions_page.h"
#include "menu_page.h"
#include "content_page.h"


using namespace Common;


PageController::PageController(QObject *parent) : QObject(parent),
    m_currentPage(E_PAGE_JINGLE)
{
}


void PageController::setupPages(JinglePage *jp, ScorePage *sp, QuestionsPage *qp, MenuPage *mp, ContentPage *cp)
{
    m_pJingle = jp;
    m_pScore = sp;
    m_pQuestion = qp;
    m_pMenu = mp;
    m_pContent = cp;

    // Build Map
    m_pages[E_PAGE_JINGLE] = m_pJingle;
    m_pages[E_PAGE_SCORE] = m_pScore;
    m_pages[E_PAGE_QUESTION] = m_pQuestion;
    m_pages[E_PAGE_MENU] = m_pMenu;
    m_pages[E_PAGE_CONTENT] = m_pContent;

    // Display first page
    m_pages[m_currentPage]->setShowed(true);
}


void PageController::onKeyEvent( KeyEvents key )
{
    m_keyEvent = key;
    updatePage();
}


void PageController::updatePage()
{
    switch(m_currentPage)
    {
    case E_PAGE_SCORE:
        updateScore();
        break;

    case E_PAGE_QUESTION:
        updateQuestion();
        break;

    case E_PAGE_JINGLE:
        updateJingle();
        break;

    case E_PAGE_MENU:
        updateMenu();
        break;

    case E_PAGE_CONTENT:
        updateContent();
    }
}


void PageController::changePage(Page page, bool hide)
{
    // Hide current page
    if(hide)
        m_pages[m_currentPage]->setShowed(false);
    // Sow new page
    m_currentPage = page;
    m_pages[m_currentPage]->setShowed(true);
}


void PageController::updateScore()
{
    qInfo() << "In update Score";
    if(m_keyEvent == E_KEY_ENTER)
    {
        qInfo() << " > Enter -> reset";
        // reset score
        m_pScore->setState(E_STATE_DISPLAY);
        // go back to question
        changePage(E_PAGE_QUESTION);
    }

    if( E_STATE_EDIT == m_pScore->getState() )
    {
        if(m_keyEvent == E_KEY_EDIT)
            m_pScore->setState(E_STATE_DISPLAY);

        if(m_pScore->isTeamSelected() == false)
        {
            if(m_keyEvent == E_KEY_NEXT or m_keyEvent == E_KEY_RETURN)
                m_pScore->selectTeam(m_keyEvent);
        }
        else
        {
            // (De/In)crease depending on question reward
            int reward = m_pQuestion->getCurrentReward();
            if(m_keyEvent == E_KEY_NEXT)
                m_pScore->increaseCurrentTeamScore(+reward);
            else if(m_keyEvent == E_KEY_RETURN)
                m_pScore->increaseCurrentTeamScore(-reward);
        }

    }
    else if ( E_STATE_DISPLAY == m_pScore->getState())
    {
        if(m_keyEvent == E_KEY_EDIT)
            m_pScore->setState(E_STATE_EDIT);
    }
}


void PageController::updateQuestion()
{
    qInfo() << "Quetion" << m_keyEvent;
    if(m_keyEvent == E_KEY_EDIT)
        changePage(E_PAGE_MENU, false);

    if(m_keyEvent == E_KEY_ENTER)
        m_pQuestion->enter();

    if(m_keyEvent == E_KEY_NEXT)
        m_pQuestion->next();

    if(m_keyEvent == E_KEY_RETURN)
        m_pQuestion->previous();
}


void PageController::updateMenu()
{
    qInfo() << "Menu" << m_keyEvent;
    if(m_keyEvent == E_KEY_EDIT)
        changePage(E_PAGE_QUESTION);

    if(m_keyEvent == E_KEY_ENTER)
    {
        if(m_pMenu->currentButton() == E_BUTTON_SCORE)
        {
            changePage(E_PAGE_SCORE);
            m_pQuestion->setShowed(false);
        }
        else if(m_pMenu->currentButton() == E_BUTTON_CONTENT)
        {
            if(m_pQuestion->getCurrentQuestion()->hasContent())
            {
                changePage(E_PAGE_CONTENT);
                m_pContent->enter();
            }
            else
            {
                changePage(E_PAGE_QUESTION);
            }
        }
    }

    if(m_keyEvent == E_KEY_NEXT)
        m_pMenu->next();

    if(m_keyEvent == E_KEY_RETURN)
        m_pMenu->previous();
}


void PageController::updateContent()
{
    if(m_keyEvent == E_KEY_EDIT)
        changePage(E_PAGE_QUESTION);

    if(m_keyEvent == E_KEY_ENTER)
        m_pContent->enter();

    if(m_keyEvent == E_KEY_NEXT)
        m_pContent->next();

    if(m_keyEvent == E_KEY_RETURN)
        m_pContent->previous();
}


void PageController::updateJingle()
{

    if(m_pJingle->isRunning() == false)
    {
        if(m_keyEvent == E_KEY_ENTER)
            m_pJingle->launch();
    }

    if(m_keyEvent == E_KEY_NEXT)
    {
        changePage(E_PAGE_QUESTION);
        // Stop sound
        m_pJingle->restore();
    }

    if(m_keyEvent == E_KEY_RETURN)
        m_pJingle->restore();

}

