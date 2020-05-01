#ifndef QT_WEB_SEARCH_CONTROLLER_H
#define QT_WEB_SEARCH_CONTROLLER_H

#include <QObject>
#include <QtCore/QList>
#include <QtQml/QQmlListProperty>
#include <Qlist>
#include <QDebug>
#include <QUrl>
#include "thread_safe_queue.h"

#include "WebPageSearchResult.h"

class QQuickView;


class Controller : public QObject {
Q_OBJECT

    Q_PROPERTY( QList<QString> pages READ getPages NOTIFY pagesChanged)
    Q_PROPERTY( QString name READ name NOTIFY nameChanged)

public:
    explicit Controller(QObject *parent = nullptr);

    QString name() const {
        return "you";
    }

    QList<QString> getPages();

    ~Controller();

    void setupUI();

    signals:
    void pagesChanged();
    void nameChanged();



    public slots:
    void search(const QString& url, const QString& search_string, qint32 thread, qint32 pages);

private:
    QQuickView *m_pUIContext;
    QList<QString> searchResult;
    thread_safe_queue<QUrl> url_cache;

private:
    void onThreadFinished(QString);
};

#endif //QT_WEB_SEARCH_CONTROLLER_H
