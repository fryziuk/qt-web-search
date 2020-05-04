#pragma once

#include "concurrent_queue.h"
#include "utils.h"
#include "web_search_result.h"

#include <QObject>
#include <QThreadPool>

class Controller : public QObject {
    Q_OBJECT
    Q_PROPERTY(web_search_result* searchResult READ getSearchResult NOTIFY searchResultChanged)
    Q_PROPERTY(int progressBar READ progressBar NOTIFY progressBarChanged)

public:
    explicit Controller(QObject* parent = nullptr);

    web_search_result* getSearchResult() const;
    int progressBar() const;

    ~Controller();

    void on_thread_finished(URL_SEARCH_RESUlT url_status);

signals:

    void searchResultChanged();
    void insert_row(URL_SEARCH_RESUlT search_result);
    void update_status(int status);
    void clear();
    void progressBarChanged();

public slots:

    void start(const QString& url, const QString& search_string, qint32 max_threads, qint32 max_urls);

    void stop();

    void set_status(int status);

private:
    web_search_result* p_result_model;

    QThreadPool thread_pool_;
    concurrent_queue<QString> urls_queue;

    std::atomic<int> status_;
    int max_urls_ {};
    int mAnalyzedUrlNum {};
    int url_index {};
};
