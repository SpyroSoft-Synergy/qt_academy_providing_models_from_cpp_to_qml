#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <filesystem>

#include <fstreemodel.h>
#include <tree.h>

static void setupDataSource(TreeNode *root)
{
    std::filesystem::path r{root->data().toString().toStdString()};
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(r)) {
        auto item = std::make_unique<TreeNode>(QString::fromStdString(entry.path().string()), root);
        if (entry.is_directory()) {
            setupDataSource(item.get());
        }
        root->appendChild(std::move(item));
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    auto treeRoot = std::make_unique<TreeNode>(QString{"./CMakeFiles"});
    setupDataSource(treeRoot.get()); // Set up the filesystem data source.
    FSTreeModel model{std::move(treeRoot)};

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("FSModel", &model); // Export the model under FSModel name to QML.
    engine.loadFromModule("treefs", "Main");

    return app.exec();
}
