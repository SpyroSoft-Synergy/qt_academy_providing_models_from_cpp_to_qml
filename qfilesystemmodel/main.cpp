#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFileSystemModel>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QFileSystemModel model;
    model.setRootPath(QDir::currentPath() + "/CMakeFiles"); // Set up the filesystem model

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.setInitialProperties({
        { "fsModel", QVariant::fromValue(&model) }, // Export the model under fsModel name to QML.
    });
    engine.loadFromModule("qfilesystemmodel", "Main");

    return app.exec();
}
