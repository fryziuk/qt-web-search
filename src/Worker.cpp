#include "Worker.h"
#include <string>
#include <regex>
#include <QUrl>
#include <QString>


Worker::Worker(const QUrl& url, const QString& searchString,
        std::function<void(QString)> mThreadFinished, thread_safe_queue<QUrl>& urls)
    : url_(url), search_string_(searchString), finished_callback_(mThreadFinished), urls_(urls) {

}


QString Worker::lookForKeyword(QString pageHtml)
{
    if (pageHtml.contains(search_string_)) {
        return "found";
    } else {
        return "not found";
    }
}

void Worker::lookForUrls(QString pageHtml)
{
    std::string text = pageHtml.toStdString();
    const std::regex hl_regex("http[s]?:\\/\\/?[^\\s([\"<,>]*\\.[^\\s[\",><]*");

    std::sregex_iterator next(text.begin(), text.end(), hl_regex);
    std::sregex_iterator end;
    while (next != end) {
        std::smatch match = *next;
        auto val = match.str();
        urls_.push(QUrl(QString::fromStdString(val)));
        next++;
    }
}

void Worker::run() {
    QNetworkAccessManager manager;
    QEventLoop event;
    QNetworkReply *response = manager.get(QNetworkRequest(url_));
    QObject::connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();

    if (response->error() == QNetworkReply::NoError) {
        QString page = response->readAll();
        //qInfo() << page;


        result_ = lookForKeyword(page);
        lookForUrls(page);
    } else {
        result_ = response->errorString();
    }

    if (finished_callback_) {
        finished_callback_(result_);
    }
    response->deleteLater();

}
