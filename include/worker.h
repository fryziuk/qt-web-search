#pragma once

#include <QRunnable>
#include <QString>

#include <atomic>
#include <set>

#include "concurrent_queue.h"
#include "utils.h"

class QNetworkReply;

class worker : public QRunnable
{
public:
    worker(concurrent_queue<std::string> &urls_queue,
           QString keyword,
           std::atomic<int> &status,
           int depth,
           std::function<void(URL_SEARCH_RESUlT)> callback,
           int index);

protected:
    void run();

private:
    void add_urls_to_queue(QString pageHtml);
    std::string find_keyword(QString pageHtml);
    std::string check_page();

    concurrent_queue<std::string> &urls_queue_;
    std::string url_;
    QString keyword_;
    std::atomic<int> &thread_status;
    int search_depth{};
    int current_search_depth{};
    int worker_id_;
    std::function<void(URL_SEARCH_RESUlT)> worker_callbalk_;

};
