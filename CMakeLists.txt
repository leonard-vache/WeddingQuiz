cmake_minimum_required(VERSION 3.5)

project(WeddingQuiz LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Multimedia REQUIRED)


add_executable(${PROJECT_NAME}
                main.cpp
                common.h
                configurator.cpp
                configurator.h
                question.cpp
                question.h
                multiple_choices_question.cpp
                multiple_choices_question.h
                quick_question.cpp
                quick_question.h
                questions_page.cpp
                questions_page.h
                content_page.cpp
                content_page.h
                remote_controller.cpp
                remote_controller.h
                page_controller.cpp
                page_controller.h
                score_page.cpp
                score_page.h
                page_interface.cpp
                page_interface.h
                jingle_page.cpp
                jingle_page.h
                menu_page.cpp
                menu_page.h
                qml.qrc )


target_compile_definitions( ${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt5::Core Qt5::Quick Qt5::Gui Qt5::Multimedia)
