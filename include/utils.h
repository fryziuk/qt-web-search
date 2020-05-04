#pragma once
#include <QString>

struct URL_SEARCH_RESUlT{
    QString url;
    QString status;
    int index;
};
constexpr auto errorPrefix= "error: ";

constexpr auto STATUS_WORKING = 0;
constexpr auto STATUS_STOPPED = 1;


