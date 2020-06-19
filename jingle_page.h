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
//    void start() { setRun(true); }

    void launch() { emit start(); }
    void restore() { emit reset(); }

    bool run() const { return m_run; }
    void setRun(bool run) { m_run = run; emit runChanged(); }

    void setQmlObject(QObject *qmlObj);

private:
    bool m_run;


signals:
    void start();
    void reset();
    void runChanged();
};

#endif // JINGLEPAGE_H
