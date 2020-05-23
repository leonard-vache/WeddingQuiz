#ifndef JINGLEPAGE_H
#define JINGLEPAGE_H

#include "page_interface.h"


class JinglePage : public PageInterface
{
    Q_OBJECT
    Q_PROPERTY(bool run READ run WRITE setRun NOTIFY runChanged);

public:
    JinglePage(QObject *parent = nullptr);

    bool isRunning() { return run(); }
    void start() { setRun(true); }

    bool run() const { return m_run; }
    void setRun(bool run) { m_run = run; emit runChanged(); }


private:
    bool m_run;


signals:
    void runChanged();
};

#endif // JINGLEPAGE_H
