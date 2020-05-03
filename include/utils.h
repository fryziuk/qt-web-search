#pragma once
#include <vector>
#include <string>

struct URL_SEARCH_RESUlT{
    std::string url;
    std::string status;
    int index;
};

constexpr auto keyword_found = "found";
constexpr auto keyword_not_found = "not found";
constexpr auto errorPrefix= "error: ";
constexpr auto STATUS_WORKING = 0;
constexpr auto STATUS_STOPPED = 1;


