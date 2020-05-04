#include "web_search_result.h"

int web_search_result::rowCount(const QModelIndex &parent) const
{
    return row_search_result.size();
}
QVariant web_search_result::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    URL_SEARCH_RESUlT result = row_search_result.at(index.row());
    switch (role) {
    case Url:
        return QVariant(result.url);
    case Status:
        return QVariant(result.status);
    }
    return QVariant();
}
QHash<int, QByteArray> web_search_result::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Url] = "url";
    names[Status] = "status";
    return names;
}

bool web_search_result::insertRow(URL_SEARCH_RESUlT search_result)
{
    beginInsertRows(QModelIndex(), current_index, current_index);
    row_search_result[current_index] = search_result;
    ++current_index;
    endInsertRows();
    return true;
}

void web_search_result::clear()
{
    beginRemoveRows(QModelIndex(), 0, current_index);
    row_search_result.clear();
    current_index = 0;
    endRemoveRows();
}
