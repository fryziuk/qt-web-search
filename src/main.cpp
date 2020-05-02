#include <QGuiApplication>
#include "controller.h"

using namespace std;

int main(int argc, char *argv[]) {
    QGuiApplication application(argc, argv);

    controller controller;
    controller.setupUI();

    return application.exec();
}
