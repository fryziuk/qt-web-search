#pragma once

#include "concurrent_queue.h"
#include "utils.h"
#include "web_search_result.h"

#include <QObject>
#include <QThreadPool>

class QQuickView;

class controller : public QObject {
Q_OBJECT
    Q_PROPERTY(web_search_result *searchResult READ getSearchResult NOTIFY searchResultChanged)

public:
    explicit controller(QObject *parent = nullptr);

    web_search_result *getSearchResult() const;

    ~controller();

    void on_thread_finished(URL_SEARCH_RESUlT url_status);

    void setup_ui();

signals:

    void searchResultChanged();

    void insert_row(URL_SEARCH_RESUlT search_result);

    void update_status(int status);

    void clear();

public slots:

    void start(const QString &url, const QString &search_string, qint32 max_threads, qint32 max_urls);

    void stop();

    void set_status(int status);

private:
    QQuickView *p_ui_context_;
    web_search_result *p_result_model;

    QThreadPool thread_pool_;
    concurrent_queue<std::string> urls_queue;

    std::atomic<int> status_;
    int max_urls_{};
    int mAnalyzedUrlNum{};
    int url_index{};
};
