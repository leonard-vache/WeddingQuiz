#ifndef TITLEPAGE_H
#define TITLEPAGE_H

#include "page_interface.h"


class TitlePage : public PageInterface
{
public:
    TitlePage(QObject *parent = nullptr);
};

#endif // TITLEPAGE_H
