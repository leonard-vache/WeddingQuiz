#ifndef PAGEINTERFACE_H
#define PAGEINTERFACE_H

#include <QObject>

class PageInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool showed READ showed NOTIFY showedChanged)

public:
    explicit PageInterface(QObject *parent = nullptr);

    // Getters
    int showed() const { return m_showed; }
    void setShowed(bool showed) { m_showed = showed; emit showedChanged(); }


private:
    bool m_showed;


signals:
    void showedChanged();

};

#endif // PAGEINTERFACE_H
