#include "controller.h"
#include "web_search_result.h"

#include <QtGui/QGuiApplication>
#include <QtQml>
#include <QFont>
#include <QStringList>
#include <QQuickView>
#include <worker.h>
#include <functional>
#include <algorithm>

namespace {
    constexpr auto CONNECTION_TIMEOUT = 1500;
}

controller::controller(QObject *parent)
        : QObject(parent), p_ui_context_(nullptr), p_result_model(new web_search_result), url_index{0} {

    connect(this, &controller::insert_row, p_result_model, &web_search_result::insertRow, Qt::QueuedConnection);
    connect(this, &controller::clear, p_result_model, &web_search_result::clear, Qt::QueuedConnection);
    timer = new QTimer(this);
    timer->setInterval(CONNECTION_TIMEOUT);
    mCrawlStatus = STATUS_WORKING;
    thread_pool.waitForDone();
    QObject::connect(this, SIGNAL(update_status(int)),
                     SLOT(set_status(int)));
    url_index = 0;
}

controller::~controller() {
    thread_pool.waitForDone();
    delete p_ui_context_;
}


void controller::setup_ui() {
    p_ui_context_ = new QQuickView;
    p_ui_context_->setTitle(QString("qt-web-search"));

    qRegisterMetaType<web_search_result *>("web_search_result*");
    qRegisterMetaType<URL_SEARCH_RESUlT>("URL_SEARCH_RESUlT");

    QQmlContext *rootContext = p_ui_context_->rootContext();
    rootContext->setContextProperty("controller", this);


    QFont f = qApp->font();
    f.setPixelSize(12);
    qApp->setFont(f);
    p_ui_context_->setResizeMode(QQuickView::SizeRootObjectToView);
    p_ui_context_->setSource(QUrl("qrc:/main.qml"));

    p_ui_context_->show();
}

void controller::start(const QString &url, const QString &search_string, qint32 threadNum, qint32 pages) {

    set_status(STATUS_WORKING);
    qDebug() << url << " " << search_string << " " << threadNum << pages;


    max_urls_ = pages;
    urls_queue.push(url.toStdString());
    thread_pool.setMaxThreadCount(threadNum);
    keyword_ = search_string;
    threads_num_ = threadNum;
    std::function<void(URL_SEARCH_RESUlT)> finish_cb = [this](URL_SEARCH_RESUlT retval) { on_thread_finished(retval); };
    threads_num_ = threadNum;
    search_depth_ = pages;

    qInfo() << "Starting " << threads_num_ << " threads";
    qInfo() << "Initial URL: " << url_;
    qInfo() << "Depth: " << search_depth_;

    mCrawlStatus = STATUS_WORKING;

    timer->start();

    int how_many = std::min(threads_num_, max_urls_ - url_index);

    for (int i = 0; i < how_many; ++i) {
        worker *thread = new worker(urls_queue, keyword_, mCrawlStatus, search_depth_, finish_cb, url_index);
        ++url_index;
        thread->setAutoDelete(true);
        thread_pool.start(thread);
    }

    //thread_pool.waitForDone(1000);
}

web_search_result *controller::getSearchResult() const {
    return p_result_model;
}

void controller::stop() {
    set_status(STATUS_STOPPED);
    emit update_status(STATUS_STOPPED);
}


void controller::on_thread_finished(URL_SEARCH_RESUlT url_status) {
    if (mCrawlStatus == STATUS_WORKING) {
        //std::lock_guard<std::mutex>lock(callback_mutex);

        emit insert_row(url_status);

        ++mAnalyzedUrlNum;

        if (mAnalyzedUrlNum == max_urls_) {
            emit update_status(STATUS_STOPPED);
        }
    }
}

void controller::set_status(int status) {
    mCrawlStatus = status;
    if (mCrawlStatus == STATUS_WORKING) {
        emit clear();
    } else if (mCrawlStatus == STATUS_STOPPED) {
        thread_pool.waitForDone();
        urls_queue.clear();
        mAnalyzedUrlNum = 0;
    }
}

