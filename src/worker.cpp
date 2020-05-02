#include <QtNetwork>

#include <chrono>
#include <regex>

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
        worker_id_(workerId)
{
}

void worker::add_urls_to_queue(QString pageHtml)
{
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

std::string worker::find_keyword(QString pageHtml)
{
    if (pageHtml.contains(keyword_)) {
        return keyword_found;
    } else {
        return keyword_not_found;
    }
}

void worker::run()
{
    while (1) {
        if (thread_status == STATUS_PAUSED) {
            std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIMEOUT));
        } else
        if (thread_status == STATUS_STOPPED ||
            current_search_depth == search_depth) {
            return;
        } else
        if (thread_status == STATUS_WORKING) {
            if (!urls_queue_.try_and_pop(url_)) {
                continue;
            } else {
                std::string threadResult = workingOnThatStatus;

                QNetworkAccessManager manager;
                QEventLoop event;
                QNetworkReply *response = manager.get(QNetworkRequest(QUrl(QString::fromStdString(url_))));
                QObject::connect(response, SIGNAL(finished()), &event, SLOT(quit()));
                event.exec();

                if (response->error() == QNetworkReply::NoError) {
                    QString page = response->readAll();
                    threadResult = find_keyword(page);
                    add_urls_to_queue(page);
                } else {
                    threadResult = errorPrefix + response->errorString().toStdString();
                }

                if (worker_callbalk_) {
                    worker_callbalk_({url_, threadResult, worker_id_});
                }

                ++current_search_depth;

                response->deleteLater();
            }
        }
    }
}
