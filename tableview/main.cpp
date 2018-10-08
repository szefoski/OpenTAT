#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "filterslistmodel.h"
#include "filtersmodel.h"
#include "mymodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    MyModel model;
    engine.rootContext()->setContextProperty("theModel", &model);

    FiltersModel filtersModel;
    engine.rootContext()->setContextProperty("filtersModel", &filtersModel);

    qmlRegisterType<FiltersListModel>("FiltersListModel", 1, 0, "FiltersListModel");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
