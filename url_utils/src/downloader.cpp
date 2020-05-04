#include "downloader.h"
#include "profile.h"

#include <stdexcept>
#include <QtNetwork>

constexpr auto SLEEP_TIMEOUT = 2000;

QString downloader::download_page(const QString& url) {
    LOG_DURATION("Download page");
    QTimer timer;
    timer.setSingleShot(true);

    QNetworkAccessManager manager;
    QEventLoop event;
    QObject::connect(&timer, SIGNAL(timeout()), &event, SLOT(quit()));
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));
    QObject::connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    timer.start(SLEEP_TIMEOUT);
    event.exec();

    QString res;

    if (response->error() == QNetworkReply::NoError) {
        res = response->readAll();
    } else {
        throw std::runtime_error(response->errorString().toStdString());
    }
    response->deleteLater();
    return res;
}