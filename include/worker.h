#pragma once

#include "concurrent_queue.h"
#include "utils.h"

#include <QRunnable>
#include <QString>
#include <atomic>

class worker : public QRunnable {
public:
    worker(concurrent_queue<QString>& urls_queue,
        QString keyword,
        std::atomic<int>& status,
        int depth,
        std::function<void(URL_SEARCH_RESUlT)> callback,
        int index);

protected:
    void run();

private:
    void add_urls_to_queue(const QString& pageHtml);
    QString process_page();

    concurrent_queue<QString>& urls_queue_;
    QString url_;
    QString keyword_;
    std::atomic<int>& thread_status_;
    int search_depth {};
    int current_search_depth {};
    int worker_id_;
    std::function<void(URL_SEARCH_RESUlT)> worker_callback_;
};
