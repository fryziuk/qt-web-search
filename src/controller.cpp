#include "controller.h"

#include <QtGui/QGuiApplication>
#include <QtQml>
#include <QFont>
#include <QStringList>
#include <QQuickView>

Controller::Controller(QObject *parent)
        : QObject(parent), m_pUIContext(nullptr) {

}

Controller::~Controller() {
    delete m_pUIContext;
}

void Controller::setupUI() {
    m_pUIContext = new QQuickView;
    m_pUIContext->setTitle(QString("qt-web-search"));

    QQmlContext *rootContext = m_pUIContext->rootContext();
    rootContext->setContextProperty("application", this);

    QFont f = qApp->font();
    f.setPixelSize(12);
    qApp->setFont(f);
    m_pUIContext->setResizeMode(QQuickView::SizeRootObjectToView);
    m_pUIContext->setSource(QUrl("qrc:/main.qml"));

    m_pUIContext->show();

}
