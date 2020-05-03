

#ifndef QT_WEB_SEARCH_WEB_SEARCH_RESULT_H
#define QT_WEB_SEARCH_WEB_SEARCH_RESULT_H
#include <QObject>
#include <QAbstractListModel>
#include <vector>
#include <map>
#include <concurrent_queue.h>
#include "utils.h"


class web_search_result: public QAbstractListModel {
Q_OBJECT
    enum {
        Url = Qt::UserRole,
        Status
    };

public:
    web_search_result();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;


public slots:
    bool insertRow(URL_SEARCH_RESUlT search_result);
    void clear();

private:
    std::map<int, URL_SEARCH_RESUlT> row_search_result;
    int current_index{0};

};



#endif //QT_WEB_SEARCH_WEB_SEARCH_RESULT_H
