#pragma once
#include "utils.h"

#include <QAbstractListModel>
#include <QObject>
#include <map>

class web_search_result : public QAbstractListModel
{
    Q_OBJECT
    enum { Url = Qt::UserRole, Status };

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    bool insertRow(URL_SEARCH_RESUlT search_result);
    void clear();

private:
    std::map<int, URL_SEARCH_RESUlT> row_search_result;
    int current_index { 0 };
};
