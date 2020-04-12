#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "multiple_choices_question.h"
#include "questions_manager.h"
#include <QtDebug>
#include <QQmlContext>
#include <iostream>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QuestionsManager questionmManager;
    questionmManager.loadConfigurationFile(QStringLiteral("questions.json"));

    MultipleChoicesQuestion *q = dynamic_cast<MultipleChoicesQuestion*>(questionmManager.getQuestion(2));
    qInfo() << q->heading();
    engine.rootContext()->setContextProperty("qm", q);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
