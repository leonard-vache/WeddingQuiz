#ifndef MENUPAGE_H
#define MENUPAGE_H

#include <QObject>
#include "common.h"
#include "page_interface.h"


class MenuPage : public PageInterface
{
    Q_OBJECT
    Q_PROPERTY(Common::MenuButtons currentButton READ currentButton NOTIFY currentButtonChanged)

public:
    explicit MenuPage(QObject *parent = nullptr);


    Common::MenuButtons currentButton() const { return m_buttons[m_bIndex]; }

    void next();
    void previous();


private:
    int m_bIndex;
    QList<Common::MenuButtons> m_buttons;


signals:
    void currentButtonChanged();
};

#endif // MENUPAGE_H
