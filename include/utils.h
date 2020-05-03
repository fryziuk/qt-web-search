#pragma once
#include <string>

struct URL_SEARCH_RESUlT{
    std::string url;
    std::string status;
    int index;
};

constexpr auto STATUS_WORKING = 0;
constexpr auto STATUS_STOPPED = 1;


