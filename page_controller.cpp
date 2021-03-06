#include "page_controller.h"

#include "question.h"
#include "jingle_page.h"
#include "score_page.h"
#include "questions_page.h"
#include "menu_page.h"
#include "content_page.h"
#include "transition_page.h"


using namespace Common;


PageController::PageController(QObject *parent) : QObject(parent),
    m_currentPage(E_PAGE_JINGLE)
{
}


void PageController::setupPages(JinglePage *jp, ScorePage *sp, QuestionsPage *qp, MenuPage *mp, ContentPage *cp, TransitionPage *tp)
{
    m_pJingle = jp;
    m_pScore = sp;
    m_pQuestion = qp;
    m_pMenu = mp;
    m_pContent = cp;
    m_pTransition = tp;

    // Build Map
    m_pages[E_PAGE_JINGLE] = m_pJingle;
    m_pages[E_PAGE_SCORE] = m_pScore;
    m_pages[E_PAGE_QUESTION] = m_pQuestion;
    m_pages[E_PAGE_MENU] = m_pMenu;
    m_pages[E_PAGE_CONTENT] = m_pContent;
    m_pages[E_PAGE_TRANSITION] = m_pTransition;

    m_currentQuestionType = m_pQuestion->currentQuestion();

    // Conections
    connect(m_pQuestion, &QuestionsPage::currentQuestionChanged,
            this, &PageController::onCurrentQuestionChanged);

    connect(m_pQuestion, &QuestionsPage::ended,
            this, &PageController::onQuestionsEnded);

    // Display first page
    m_pages[m_currentPage]->setShowed(true);
}


void PageController::onKeyEvent( KeyEvents key )
{
    m_keyEvent = key;
    updatePage();
}


void PageController::onCurrentQuestionChanged()
{
    qInfo() << "onCurrentQuestionChanged" << m_currentQuestionType << m_pQuestion->currentQuestion();
    if( m_currentQuestionType != m_pQuestion->currentQuestion())
    {
        m_pTransition->setQuestionTransition(m_currentQuestionType);
        m_currentQuestionType = m_pQuestion->currentQuestion();

        changePage(E_PAGE_TRANSITION);
    }
}


void PageController::onQuestionsEnded()
{
    m_pTransition->setQuestionTransition(m_currentQuestionType);
    changePage(E_PAGE_TRANSITION);
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
        break;

    case E_PAGE_TRANSITION:
        updateTransition();
        break;
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
    if(m_keyEvent == E_KEY_ENTER)
    {
        // reset
        m_pScore->unselectTeam();
        // go back to question
        changePage(E_PAGE_QUESTION);
        return;
    }

    if(m_keyEvent == E_KEY_EDIT)
    {
        m_pScore->unselectTeam();
        return;
    }

    if(m_pScore->isTeamSelected() == false)
    {
        qInfo() << "No Team Selected" << m_keyEvent << E_KEY_NEXT <<E_KEY_RETURN << (m_keyEvent == E_KEY_NEXT || m_keyEvent == E_KEY_RETURN);
        if(m_keyEvent == E_KEY_NEXT || m_keyEvent == E_KEY_RETURN)
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


void PageController::updateQuestion()
{
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


void PageController::updateTransition()
{
    qInfo() << "In update Transition";
    if(m_keyEvent == E_KEY_EDIT)
        changePage(E_PAGE_SCORE);

    if(m_keyEvent == E_KEY_NEXT)
        changePage(E_PAGE_QUESTION);

    if(m_keyEvent == E_KEY_RETURN)
    {
        changePage(E_PAGE_QUESTION);
        m_pQuestion->previous();
    }
}

