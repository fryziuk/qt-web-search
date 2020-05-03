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
        : QObject(parent), p_ui_context_(nullptr), p_result_model(new web_search_result), url_index{0}, crawl_status_(STATUS_WORKING) {

    connect(this, &controller::insert_row, p_result_model, &web_search_result::insertRow, Qt::QueuedConnection);
    connect(this, &controller::clear, p_result_model, &web_search_result::clear, Qt::QueuedConnection);
    connect(this, SIGNAL(update_status(int)),
                     SLOT(set_status(int)));
}

controller::~controller() {
    thread_pool_.waitForDone();
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
    stop();

    set_status(STATUS_WORKING);
    max_urls_ = pages;
    urls_queue.push(url.toStdString());

    thread_pool_.setMaxThreadCount(threadNum);
    keyword_ = search_string;
    threads_num_ = threadNum;

    std::function<void(URL_SEARCH_RESUlT)> finish_cb = [this](URL_SEARCH_RESUlT retval) { on_thread_finished(retval); };
    threads_num_ = threadNum;
    search_depth_ = pages;

    crawl_status_ = STATUS_WORKING;

    int how_many = std::min(threads_num_, max_urls_ - url_index);

    for (int i = 0; i < how_many; ++i) {
        worker *thread = new worker(urls_queue, keyword_, crawl_status_, search_depth_, finish_cb, url_index);
        ++url_index;
        thread->setAutoDelete(true);
        thread_pool_.start(thread);
    }
}

web_search_result *controller::getSearchResult() const {
    return p_result_model;
}

void controller::stop() {
    set_status(STATUS_STOPPED);
    emit update_status(STATUS_STOPPED);
}


void controller::on_thread_finished(URL_SEARCH_RESUlT url_status) {
    if (crawl_status_ == STATUS_WORKING) {
        emit insert_row(url_status);
        ++mAnalyzedUrlNum;

        if (mAnalyzedUrlNum == max_urls_) {
            emit update_status(STATUS_STOPPED);
        }
    }
}

void controller::set_status(int status) {
    crawl_status_ = status;
    if (crawl_status_ == STATUS_WORKING) {
        emit clear();
    } else if (crawl_status_ == STATUS_STOPPED) {
        thread_pool_.waitForDone();
        urls_queue.clear();
        mAnalyzedUrlNum = 0;
    }
}
