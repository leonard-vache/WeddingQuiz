#include <assert.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "configurator.h"
#include "multiple_choices_question.h"
#include "questions_manager.h"
#include "questions_list.h"
#include "remote_controller.h"

#include "score_page.h"
#include "jingle_page.h"
#include "title_page.h"
#include "page_controller.h"

#include <QQmlContext>
#include <QMediaPlayer>
#include <QMediaPlaylist>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<MultipleChoicesQuestion>("WeddingQuiz", 1, 0, "MultipleChoicesQuestionObject");
    qmlRegisterType<TeamObject>("WeddingQuiz", 1, 0, "TeamItem");


    /* Create Object */
    Configurator conf;
    RemoteController remoteController;


    /* Pages */
    TitlePage titlePage;
    JinglePage jinglePage;
    ScorePage scorePage;
    QuestionsManager questionManager;

    PageController pageController;
    pageController.setupPages(&titlePage, &jinglePage, &scorePage);


    /* Load Configuration Sections */
    conf.loadConfigurationFile(QStringLiteral("wq_configuration.json"));

    assert( conf.isSection("RemoteController") );
    remoteController.readConfiguration(conf.getSection("RemoteController"));

    assert( conf.isSection("QuestionsManager") );
    questionManager.readConfiguration(conf.getSection("QuestionsManager"));

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
    engine.rootContext()->setContextProperty("questions", questionManager.getQuestionList());
    engine.rootContext()->setContextProperty("remote", &remoteController);
    engine.rootContext()->setContextProperty("scorePage", &titlePage);
    engine.rootContext()->setContextProperty("scorePage", &scorePage);
    engine.rootContext()->setContextProperty("jinglePage", &jinglePage);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
