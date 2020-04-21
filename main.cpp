#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "multiple_choices_question.h"
#include "questions_manager.h"
#include "questions_list.h"

#include <QQmlContext>
#include <QMediaPlayer>
#include <QMediaPlaylist>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<MultipleChoicesQuestion>("WeddingQuiz", 1, 0, "MultipleChoicesQuestionObject");

    QuestionsManager questionManager;
    questionManager.loadConfigurationFile(QStringLiteral("questions.json"));

//    MultipleChoicesQuestion *q = dynamic_cast<MultipleChoicesQuestion*>(questionManager.getQuestion(2));
//    qInfo() << q->heading();
//    engine.rootContext()->setContextProperty("qm", q);

    QMediaPlayer *player = new QMediaPlayer();

    QMediaPlaylist *playlist = new QMediaPlaylist(player);
    playlist->addMedia(QUrl("jingleWQ.mp4"));

//    QVideoWidget videoWidget = new QVideoWidget();
//    player->setVideoOutput(videoWidget);

//    videoWidget->show();
//    playlist->setCurrentIndex(1);
//    player->play();

//    qInfo() << "supported codec" << QMediaRecorder::supportedVideoCodecs()
    engine.rootContext()->setContextProperty("questions", questionManager.getQuestionList());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
