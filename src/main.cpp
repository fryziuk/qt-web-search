#include "Controller.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

using namespace std;

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication application(argc, argv);

    qRegisterMetaType<web_search_result *>("web_search_result*");
    qRegisterMetaType<URL_SEARCH_RESUlT>("URL_SEARCH_RESUlT");
    qmlRegisterType<Controller>("App.Controller", 0, 1, "Controller");

    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/main.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;

    return application.exec();
}
