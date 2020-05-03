#include "profile.h"
#include "worker.h"

#include <QtNetwork>
#include <QRegExp>

constexpr auto SLEEP_TIMEOUT = 2000;
constexpr auto keyword_found = "Found";
constexpr auto keyword_not_found = "Not found";
constexpr auto errorPrefix= "error: ";

worker::worker(concurrent_queue<std::string> &urls_queue,
               QString keyword,
               std::atomic<int> &status,
               int depth,
               std::function<void(URL_SEARCH_RESUlT)> callback,
               int workerId) :
        urls_queue_(urls_queue),
        keyword_(keyword),
        thread_status_(status),
        search_depth(depth),
        worker_callback_(callback),
        worker_id_(workerId) {
}

void worker::add_urls_to_queue(const QString& pageHtml) {
    LOG_DURATION("Add URLs to queue");
    QRegularExpression url_reg_exp("http[s]?:\\/\\/?[^\\s([\"<,>]*\\.[^\\s[\",><]*");
    QRegularExpressionMatchIterator i = url_reg_exp.globalMatch(pageHtml);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch()) {
            urls_queue_.push( match.captured(0).toStdString());
        }
    }
}

std::string worker::find_keyword(const QString& pageHtml, const QString& keyword) const {
    LOG_DURATION("Find keyword");
    if (pageHtml.contains(keyword)) {
        return keyword_found;
    } else {
        return keyword_not_found;
    }
}

QNetworkReply* worker::download_page() const {
    QTimer timer;
    timer.setSingleShot(true);

    QNetworkAccessManager manager;
    QEventLoop event;
    QObject::connect(&timer, SIGNAL(timeout()), &event, SLOT(quit()));
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(QString::fromStdString(url_))));
    QObject::connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    timer.start(SLEEP_TIMEOUT);
    event.exec();
    return response;
}


std::string worker::check_page() {
    LOG_DURATION("Download page");
    std::string threadResult;

    QTimer timer;
    timer.setSingleShot(true);

    QNetworkAccessManager manager;
    QEventLoop event;
    QObject::connect(&timer, SIGNAL(timeout()), &event, SLOT(quit()));
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(QString::fromStdString(url_))));
    QObject::connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    timer.start(SLEEP_TIMEOUT);
    event.exec();

    if (response->error() == QNetworkReply::NoError) {
        QString page = response->readAll();
        threadResult = find_keyword(page, keyword_);
        add_urls_to_queue(page);
    } else {
        threadResult = errorPrefix + response->errorString().toStdString();
    }
    response->deleteLater();
    return threadResult;
}

void worker::run() {
    while (true) {
        if (thread_status_ == STATUS_STOPPED ||
            current_search_depth == search_depth) {
            return;
        } else if (thread_status_ == STATUS_WORKING) {
            if (!urls_queue_.try_and_pop(url_)) {
                continue;
            } else {
                std::string thread_result = check_page();
                if (worker_callback_) {
                    worker_callback_({url_, thread_result, worker_id_});
                }
                ++current_search_depth;
            }
        }
    }
}
