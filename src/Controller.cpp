#include "Controller.h"
#include "WebPageSearchResult.h"

#include <QtGui/QGuiApplication>
#include <QtQml>
#include <QFont>
#include <QStringList>
#include <QQuickView>
#include <Worker.h>
#include <functional>

Controller::Controller(QObject *parent)
        : QObject(parent), m_pUIContext(nullptr), url_cache() {
}

Controller::~Controller() {
    delete m_pUIContext;
}

QList<QString> Controller::getPages() {
    return searchResult;
}

void Controller::setupUI() {
    m_pUIContext = new QQuickView;
    m_pUIContext->setTitle(QString("qt-web-search"));

    QQmlContext *rootContext = m_pUIContext->rootContext();
    rootContext->setContextProperty("controller", this);

    //qmlRegisterType<WebPageSearchResult>("qt-weg-search", 1, 0, "WebPageSearchResult" );

    QFont f = qApp->font();
    f.setPixelSize(12);
    qApp->setFont(f);
    m_pUIContext->setResizeMode(QQuickView::SizeRootObjectToView);
    m_pUIContext->setSource(QUrl("qrc:/main.qml"));

    m_pUIContext->show();
}

void Controller::search(const QString& url, const QString& search_string, qint32 thread, qint32 pages) {
    qDebug() << url << " " << search_string << " " << thread << pages;

    if (url.size()) {
        QThreadPool threadPool;
        std::function<void(QString)> finish_cb = [this](QString retval) {onThreadFinished(retval);};
        Worker *downloadThread = new Worker(url, search_string, finish_cb, url_cache);

        threadPool.start(downloadThread);
    }

}

void Controller::onThreadFinished(QString str) {

    for (auto& el : url_cache.set_) {
        searchResult.push_back(el.toString());
    }
    emit(pagesChanged());
    qDebug() << str;
}

