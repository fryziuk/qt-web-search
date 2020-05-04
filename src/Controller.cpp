#include "Controller.h"
#include "web_search_result.h"
#include "worker.h"

#include <functional>

Controller::Controller(QObject *parent)
    : QObject(parent),
      p_result_model(new web_search_result),
      status_(STATUS_WORKING),
      url_index { 0 }
{

    connect(this, &Controller::insert_row, p_result_model, &web_search_result::insertRow,
            Qt::QueuedConnection);
    connect(this, &Controller::clear, p_result_model, &web_search_result::clear,
            Qt::QueuedConnection);
    connect(this, SIGNAL(update_status(int)), SLOT(set_status(int)), Qt::QueuedConnection);
}

Controller::~Controller()
{
    thread_pool_.waitForDone();
}

void Controller::start(const QString &url, const QString &search_string, qint32 max_threads,
                       qint32 max_urls)
{
    stop();
    set_status(STATUS_WORKING);

    max_urls_ = max_urls;
    urls_queue.push(url);

    thread_pool_.setMaxThreadCount(max_threads);
    auto finished_callback = [this](URL_SEARCH_RESUlT retval) { on_thread_finished(retval); };

    int how_many = std::min(max_threads, max_urls - url_index);

    for (int i = 0; i < how_many; ++i) {
        worker *thread = new worker(urls_queue, search_string, status_, max_urls, finished_callback,
                                    url_index);
        ++url_index;
        thread->setAutoDelete(true);
        thread_pool_.start(thread);
    }
}

web_search_result *Controller::getSearchResult() const
{
    return p_result_model;
}

void Controller::stop()
{
    set_status(STATUS_STOPPED);
}

void Controller::on_thread_finished(URL_SEARCH_RESUlT url_status)
{
    if (status_ == STATUS_WORKING) {
        emit insert_row(url_status);
        ++mAnalyzedUrlNum;
        emit progressBarChanged();

        if (mAnalyzedUrlNum == max_urls_) {
            emit update_status(STATUS_STOPPED);
        }
    }
}

void Controller::set_status(int status)
{
    status_ = status;
    if (status_ == STATUS_WORKING) {
        emit clear();
        emit progressBarChanged();
    } else if (status_ == STATUS_STOPPED) {
        thread_pool_.waitForDone();
        urls_queue.clear();
        mAnalyzedUrlNum = 0;
        url_index = 0;
    }
}

int Controller::progressBar() const
{
    return mAnalyzedUrlNum;
}
