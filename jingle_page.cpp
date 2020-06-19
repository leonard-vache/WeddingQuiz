#include "jingle_page.h"

JinglePage::JinglePage(QObject *parent) : PageInterface(parent),
    m_run(false)
{
}


void JinglePage::setQmlObject(QObject *qmlObj)
{
    // C++ To QML
    QObject::connect(this, SIGNAL(reset()),
                     qmlObj, SIGNAL(reset()) );

    QObject::connect(this, SIGNAL(start()),
                     qmlObj, SIGNAL(start()) );
}
