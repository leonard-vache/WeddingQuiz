#include <assert.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "common.h"
#include "configurator.h"
#include "multiple_choices_question.h"
#include "quick_question.h"

#include "remote_controller.h"


#include "jingle_page.h"
#include "score_page.h"
#include "questions_page.h"
#include "page_controller.h"




int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<MultipleChoicesQuestion>("WeddingQuiz", 1, 0, "MultipleChoicesQuestionObject");
    qmlRegisterType<QuickQuestion>("WeddingQuiz", 1, 0, "QuickQuestionObject");
//    qmlRegisterType<QuestionTypes>("WeddingQuiz", 1, 0, "QuestionTypesObject");

    qmlRegisterType<Team>("WeddingQuiz", 1, 0, "TeamObject");


    /* Create Object */
    Configurator conf;
    RemoteController remoteController;


    /* Pages */
    JinglePage jinglePage;
    ScorePage scorePage;
    QuestionsPage questionsPage;

    PageController pageController;
    pageController.setupPages(&jinglePage, &scorePage, &questionsPage);


    /* Load Configuration Sections */
    conf.loadConfigurationFile(QStringLiteral("wq_configuration.json"));

    assert( conf.isSection("RemoteController") );
    remoteController.readConfiguration(conf.getSection("RemoteController"));

    assert( conf.isSection("QuestionsPage") );
    questionsPage.readConfiguration(conf.getSection("QuestionsPage"));

    assert( conf.isSection("ScorePage") );
    scorePage.readConfiguration(conf.getSection("ScorePage"));

    qInfo() << "Configuration Loaded !";


    /* Connections */
    QObject::connect(&remoteController, &RemoteController::keyPressed,
                     &pageController, &PageController::onKeyEvent);



//    MultipleChoicesQuestion *q = dynamic_cast<MultipleChoicesQuestion*>(questionManager.getQuestion(2));
//    qInfo() << q->heading();
//    engine.rootContext()->setContextProperty("qm", q);


//    qInfo() << "supported codec" << QMediaRecorder::supportedVideoCodecs()
//    engine.rootContext()->setContextProperty("questions", questionManager.getQuestionList());
    engine.rootContext()->setContextProperty("remote", &remoteController);
    engine.rootContext()->setContextProperty("jinglePage", &jinglePage);
    engine.rootContext()->setContextProperty("scorePage", &scorePage);
    engine.rootContext()->setContextProperty("questionsPage", &questionsPage);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
