import QtQuick 2.14
import WeddingQuiz 1.0
import WeddingQuiz.Common 1.0

Item {
    id: root

    objectName: "QuestionsPage"
    signal resetContent

    property MultipleChoicesQuestionObject mcqModel: questionsPage.mcq
    property QuickQuestionObject qqModel: questionsPage.qq

    property string currentContent: questionsPage.currentQuestion === Common.E_MULTIPLE_CHOICE_QUESTION ? mcqModel.content : qqModel.content



    MultipleChoicesQuestionItem {
        id: mcq
        visible: questionsPage.currentQuestion === Common.E_MULTIPLE_CHOICE_QUESTION
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
        visible: questionsPage.currentQuestion === Common.E_QUICK_QUESTION
        anchors.fill: parent

        heading:  qqModel.heading
        title: qqModel.title

    }

}
