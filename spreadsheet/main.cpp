#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <editablespreadsheet.h>

namespace {
    Spreadsheet::Array2D source {
        std::array<Spreadsheet::value_type, Spreadsheet::MaxArraySize>{1, 2, 3, 4, 5, 6, 7, 8, 9},
        std::array<Spreadsheet::value_type, Spreadsheet::MaxArraySize>{1, 2, 3, 4, 5, 6, 7, 8, 9},
        std::array<Spreadsheet::value_type, Spreadsheet::MaxArraySize>{1, 2, 3, 4, 5, 6, 7, 8, 9},
        std::array<Spreadsheet::value_type, Spreadsheet::MaxArraySize>{1, 2, 3, 4, 5, 6, 7, 8, 9},
        std::array<Spreadsheet::value_type, Spreadsheet::MaxArraySize>{1, 2, 3, 4, 5, 6, 7, 8, 9},
        std::array<Spreadsheet::value_type, Spreadsheet::MaxArraySize>{1, 2, 3, 4, 5, 6, 7, 8, 9},
        std::array<Spreadsheet::value_type, Spreadsheet::MaxArraySize>{1, 2, 3, 4, 5, 6, 7, 8, 9},
        std::array<Spreadsheet::value_type, Spreadsheet::MaxArraySize>{1, 2, 3, 4, 5, 6, 7, 8, 9},
        std::array<Spreadsheet::value_type, Spreadsheet::MaxArraySize>{1, 2, 3, 4, 5, 6, 7, 8, 9},
    };
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    EditableSpreadsheet spreadsheet{source}; // Create the model.

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.setInitialProperties({
        { "spreadsheet", QVariant::fromValue(&spreadsheet) }, // Export the model under spreadsheet name to QML.
    });
    engine.loadFromModule("spreadsheet", "Main");

    return app.exec();
}
