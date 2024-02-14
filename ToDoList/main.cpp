#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <vector>
#include <task.h>
#include <todolist.h>

namespace {
    std::vector<Task> tasks{
        {"Empty the bin", Task::State::ToDo},
        {"Review the code", Task::State::ToDo},
        {"Learn Qt", Task::State::InProgress},
        {"Buy a book", Task::State::Done}
    };
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ToDoList list{tasks}; // Create the model.

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("ToDoList", &list); // Export the model under ToDoList name to QML.
    engine.loadFromModule("todolist", "Main");

    return app.exec();
}
