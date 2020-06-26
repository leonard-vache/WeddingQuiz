import QtQuick 2.14
import WeddingQuiz.Common 1.0

Item {
    id: root

    ScorePage {
        id: score
        visible: scorePage.showed
        anchors.fill: parent
    }

    Jingle {
        id: jingle
        objectName: "JinglePage"
        visible: jinglePage.showed
        anchors.fill: parent
        onRunningChanged: if(running == false) jinglePage.run = false
    }

    MenuPage {
        id: menu
        visible: questionsPage.showed
        enabled: menuPage.showed
        width: root.width

        anchors { top:root.top; topMargin: height * 0.5 }

        currentButton: menuPage.currentButton
    }

    QuestionsPage {
        id: questions
        visible: questionsPage.showed
        anchors.fill: parent
    }

    ContentPage {
        id: content
        objectName: "ContentPage"
        anchors.fill: parent
        visible: questions.visible && contentPage.showed
        source: questions.currentContent
        running: contentPage.running

        onSourceChanged:
        {
            contentPage.clear()
            content.isImage = contentPage.isImage(content.source)
            content.isVideo = contentPage.isVideo(content.source)
            content.autopause = contentPage.getAutoPause(content.source)
            content.autopauseDone = false
        }
    }

    TransitionPage {
        id: transition
        visible: transitionPage.showed
        anchors.fill: parent
        source: transitionPage.imageSource
    }
}
