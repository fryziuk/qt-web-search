#include <QtNetwork>

#include <chrono>
#include <regex>
#include <profile.h>

#include "worker.h"

namespace {
    constexpr auto SLEEP_TIMEOUT = 1500;
}

worker::worker(concurrent_queue<std::string> &urls_queue,
               QString keyword,
               std::atomic<int> &status,
               int depth,
               std::function<void(URL_SEARCH_RESUlT)> callback,
               int workerId) :
        urls_queue_(urls_queue),
        keyword_(keyword),
        thread_status(status),
        search_depth(depth),
        worker_callbalk_(callback),
        worker_id_(workerId) {
}

void worker::add_urls_to_queue(QString pageHtml) {
    LOG_DURATION("Add URLs to queue");

    std::string text = pageHtml.toStdString();
    const std::regex hl_regex("http[s]?:\\/\\/?[^\\s([\"<,>]*\\.[^\\s[\",><]*");

    std::sregex_iterator next(text.begin(), text.end(), hl_regex);
    std::sregex_iterator end;
    while (next != end) {
        std::smatch match = *next;
        auto val = match.str();
        urls_queue_.push(val);
        next++;
    }
}

std::string worker::find_keyword(QString pageHtml) {
    LOG_DURATION("Find keyword");
    if (pageHtml.contains(keyword_)) {
        return keyword_found;
    } else {
        return keyword_not_found;
    }
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
    timer.start(2000);
    event.exec();

    if (response->error() == QNetworkReply::NoError) {
        QString page = response->readAll();
        threadResult = find_keyword(page);
        add_urls_to_queue(page);
    } else {
        threadResult = errorPrefix + response->errorString().toStdString();
    }
    response->deleteLater();
    return threadResult;
}

void worker::run() {
    while (true) {
        if (thread_status == STATUS_STOPPED ||
            current_search_depth == search_depth) {
            return;
        } else if (thread_status == STATUS_WORKING) {
            if (!urls_queue_.try_and_pop(url_)) {
                continue;
            } else {
                std::string thread_result = check_page();
                if (worker_callbalk_) {
                    worker_callbalk_({url_, thread_result, worker_id_});
                }
                ++current_search_depth;
            }
        }
    }
}
