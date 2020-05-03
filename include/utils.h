#pragma once
#include <string>

struct URL_SEARCH_RESUlT{
    std::string url;
    std::string status;
    int index;
};
constexpr auto SLEEP_TIMEOUT = 2000;
constexpr auto keyword_found = "Found";
constexpr auto keyword_not_found = "Not found";
constexpr auto errorPrefix= "error: ";

constexpr auto STATUS_WORKING = 0;
constexpr auto STATUS_STOPPED = 1;


