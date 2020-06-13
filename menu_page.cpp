#include "menu_page.h"


using namespace Common;


MenuPage::MenuPage(QObject *parent) : PageInterface(parent)
{

    m_buttons.append(E_BUTTON_SCORE);
    m_buttons.append(E_BUTTON_CONTENT);
    m_bIndex = 0;
}

void MenuPage::next()
{
    m_bIndex = (m_bIndex+1) % m_buttons.size();
    emit currentButtonChanged();
}


void MenuPage::previous()
{
    m_bIndex = (m_bIndex-1) % m_buttons.size();
    if(m_bIndex < 0)
        m_bIndex = 0;
    emit currentButtonChanged();
}


