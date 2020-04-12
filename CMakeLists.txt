cmake_minimum_required(VERSION 3.5)

project(WeddingQuiz LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick  REQUIRED)


add_executable(${PROJECT_NAME}
                main.cpp
                question.cpp
                question.h
                questions_manager.cpp
                questions_manager.h
                multiple_choices_question.cpp
                multiple_choices_question.h
                qml.qrc )

target_compile_definitions( ${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt5::Core Qt5::Quick Qt5::Gui)
