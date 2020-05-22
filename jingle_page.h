#ifndef JINGLEPAGE_H
#define JINGLEPAGE_H

#include "page_interface.h"


class JinglePage : public PageInterface
{
public:
    JinglePage(QObject *parent = nullptr);
    bool isRunning() { return true; }
};

#endif // JINGLEPAGE_H
