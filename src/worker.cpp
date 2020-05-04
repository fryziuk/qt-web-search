#include "profile.h"
#include "worker.h"
#include "utils.h"
#include "downloader.h"
#include "url_searcher.h"

#include <stdexcept>


worker::worker(concurrent_queue<QString> &urls_queue,
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
    urls_queue_.push(url_searcher::get_urls_from_page(pageHtml));
}

QString worker::process_page() {
    QString threadResult;

    try {
        QString page = downloader::download_page(url_);
        threadResult = url_searcher::find_keyword(page, keyword_);
        add_urls_to_queue(page);
    }
    catch(exception& ex) {
        threadResult = errorPrefix + static_cast<QString>(ex.what());
    }

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
                QString thread_result = process_page();
                if (worker_callback_) {
                    worker_callback_({url_, thread_result, worker_id_});
                }
                ++current_search_depth;
            }
        }
    }
}
