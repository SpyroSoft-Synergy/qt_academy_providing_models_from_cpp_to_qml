#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSortFilterProxyModel>
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // First, an example-db database has to be open.
    QSqlDatabase sourceDb = QSqlDatabase::addDatabase("QSQLITE");
    sourceDb.setDatabaseName("./example-db");
    if (!sourceDb.open()) {
        return -1;
    }

    // We set up a QSqlTableModel model to the Products table from example-db database.
    QSqlTableModel model{nullptr, sourceDb};
    model.setTable("Products");
    model.setEditStrategy(QSqlTableModel::OnFieldChange); // See: https://doc.qt.io/qt-6/qsqltablemodel.html#EditStrategy-enum
    model.select();

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("SQLModel", &model); // Export the model under SQLModel name to QML.
    engine.loadFromModule("sqlmodel", "Main");

    return app.exec();
}
