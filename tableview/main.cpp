#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "sortfilterproxymodel.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

     qmlRegisterType<SortFilterProxyModel>("org.qtproject.example", 1, 0, "SortFilterProxyModel");

    QQmlApplicationEngine engine;
    SortFilterProxyModel people;
    engine.rootContext()->setContextProperty("people", &people);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}