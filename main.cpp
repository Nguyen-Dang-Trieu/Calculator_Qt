#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Calculator.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Database
    if (!DatabaseManager::instance().openDB()) {
        qWarning() << "Could not open database";
    }


    qmlRegisterType<Calculator>("com.company.calculator", 1, 0, "Calculator");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/helloworld_Qt/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
