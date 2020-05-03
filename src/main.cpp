#include <QGuiApplication>
#include "controller.h"

using namespace std;

int main(int argc, char *argv[]) {
    QGuiApplication application(argc, argv);

    controller controller;
    controller.setup_ui();

    return application.exec();
}
