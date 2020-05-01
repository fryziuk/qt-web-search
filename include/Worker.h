#ifndef DOWNLOAD_THREAD_H
#define DOWNLOAD_THREAD_H
#include <QRunnable>
#include <QString>
#include <QtNetwork>
#include <QQueue>

#include <atomic>
#include <set>

#include "thread_safe_queue.h"
class Worker : public QRunnable {
public:
    explicit Worker(const QUrl& url, const QString& searchString, std::function<void(QString)> finished_callback,
                    thread_safe_queue<QUrl>& urls);
    QString lookForKeyword(QString pageHtml);
    void lookForUrls(QString pageHtml);

protected:
    void run();

private:
    QUrl url_;
    QString search_string_;
    QString result_;
    std::function<void(QString)> finished_callback_;
    thread_safe_queue<QUrl>& urls_;

};


#endif // DOWNLOAD_THREAD_H
