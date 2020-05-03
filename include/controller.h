#ifndef QT_WEB_SEARCH_CONTROLLER_H
#define QT_WEB_SEARCH_CONTROLLER_H

#include "concurrent_queue.h"
#include "utils.h"
#include "web_search_result.h"

#include <QDebug>
#include <QObject>
#include <QThreadPool>
#include <QUrl>
#include <Qlist>
#include <QtCore/QList>
#include <QtQml/QQmlListProperty>
#include <Qtimer>
#include <unordered_set>

class QQuickView;


class controller : public QObject {
Q_OBJECT
    Q_PROPERTY(web_search_result* searchResult READ getSearchResult NOTIFY searchResultChanged)

public:
    explicit controller(QObject *parent = nullptr);

    web_search_result* getSearchResult() const;

    ~controller();

    void on_thread_finished(URL_SEARCH_RESUlT url_status);

    void setup_ui();

    signals:
    void searchResultChanged();
    void insert_row(URL_SEARCH_RESUlT search_result);
    void update_status(int status);
    void clear();



public slots:
    void start(const QString& url, const QString& search_string, qint32 thread, qint32 pages);
    void stop();
    void set_status(int status);


private:
    QQuickView *p_ui_context_;
    web_search_result* p_result_model;

    QThreadPool thread_pool;
    QTimer *timer;

    std::mutex callback_mutex;

    concurrent_queue<std::string> urls_queue;
    std::atomic<int> mCrawlStatus;

    QString url_;
    QString keyword_;
    int search_depth_{};
    int max_urls_{};

    int threads_num_{};
    int mAnalyzedUrlNum{};
    int mCurrentUrlIndex{};

    int url_index{};
    std::unordered_set<int> started_index;
};

#endif //QT_WEB_SEARCH_CONTROLLER_H
