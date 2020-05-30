import QtQuick 2.14
import WeddingQuiz 1.0

Item {
    id: root

    property MultipleChoicesQuestionObject mcqModel: questionsPage.mcq
    property QuickQuestionObject qqModel: questionsPage.qq

    Component.onCompleted: print("completed", questionsPage.currentQuestion, questionsPage.E_QUICK, questionsPage.E_MULTIPLE_CHOICE)


    MultipleChoicesQuestionItem {
        id: mcq
        visible: questionsPage.currentQuestion === 0 //questionsPage.E_MULTIPLE_CHOICE
        anchors.fill: parent

        heading:  mcqModel.heading
        suggestions: mcqModel.suggestions
        answer: mcqModel.answer-1
        content: mcqModel.content

        showResponse: mcqModel.showAnswer
        suggestionIndex: mcqModel.suggestionIndex
    }

    QuickQuestionItem {
        id: qq
        visible: questionsPage.currentQuestion === 1 //questionsPage.E_QUICK
        anchors.fill: parent

        heading:  qqModel.heading
        title: qModel.title
    }


}
