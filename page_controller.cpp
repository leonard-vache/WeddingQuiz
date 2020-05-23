#include "page_controller.h"

#include "title_page.h"
#include "score_page.h"
#include "jingle_page.h"



PageController::PageController(QObject *parent) : QObject(parent),
    m_currentPage(E_PAGE_JINGLE)
{
}


void PageController::setupPages(JinglePage *jp, ScorePage *sp)
{
    m_pJingle = jp;
    m_pScore = sp;

    // Build Map
    m_pages[E_PAGE_SCORE] = m_pScore;
    m_pages[E_PAGE_JINGLE] = m_pJingle;

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
    }
}


void PageController::changePage(WQPage page)
{
    // Hide current page
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
        m_currentPage = E_PAGE_QUESTION;
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
            if(m_keyEvent == E_KEY_NEXT)
                m_pScore->increaseCurrentTeamScore(1);
            else if(m_keyEvent == E_KEY_RETURN)
                m_pScore->increaseCurrentTeamScore(-1);
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
    if(m_keyEvent == E_KEY_EDIT)
        changePage(E_PAGE_SCORE);

    if(m_keyEvent == E_KEY_ENTER)
        changePage(E_PAGE_SCORE);

}


void PageController::updateJingle()
{

    if(m_pJingle->isRunning() == false)
    {
        if(m_keyEvent == E_KEY_ENTER)
            m_pJingle->start();

        if(m_keyEvent == E_KEY_EDIT)
            changePage(E_PAGE_SCORE);

        if(m_keyEvent == E_KEY_NEXT)
            changePage(E_PAGE_QUESTION);
    }

}

