#ifndef COMMON_H
#define COMMON_H

#include <QtDebug>
#include <QObject>




namespace Common
{
    Q_NAMESPACE         // required for meta object creation
    enum MenuButtons {
        E_BUTTON_SCORE,
        E_BUTTON_CONTENT,
    };
    Q_ENUM_NS(MenuButtons)  // register the enum in meta object data


    enum QuestionTypes {
        E_MULTIPLE_CHOICE_QUESTION,
        E_QUICK_QUESTION
    };
    Q_ENUM_NS(QuestionTypes)  // register the enum in meta object data


    enum KeyEvents {
        E_KEY_NEXT,
        E_KEY_RETURN,
        E_KEY_ENTER,
        E_KEY_EDIT
    };

    enum Page {
        E_PAGE_JINGLE,
        E_PAGE_SCORE,
        E_PAGE_QUESTION,
        E_PAGE_MENU,
        E_PAGE_CONTENT,
        E_PAGE_TRANSITION
    };

    enum ScoreState {
        E_STATE_DISPLAY,
        E_STATE_EDIT
    };


    enum ContentState {
        E_STOP,
        E_PLAY,
        E_PAUSE
    };

}

#endif // COMMON_H
