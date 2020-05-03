//
// Created by Oleksandr Fryziuk on 01.05.2020.
//

#ifndef QT_WEB_SEARCH_UTILS_H
#define QT_WEB_SEARCH_UTILS_H
#include <vector>
#include <string>

//using URL_SEARCH_RESUlT = std::pair<std::string, std::string>; //url, status

struct URL_SEARCH_RESUlT{
    std::string url;
    std::string status;
    int index;
};

constexpr auto invalidInpStringErr = "URL or keyword is empty, make no sense to start a program";
constexpr auto invalidInpIntErr = "Threads or Depth value = 0, make no sense to start a program";
constexpr auto invalidUrlErr = "Invalid URL provided or server is unavailable";
constexpr auto keyword_found = "found";
constexpr auto keyword_not_found = "not found";
constexpr auto workingOnThatStatus = "analyzing";
constexpr auto errorPrefix= "error: ";
constexpr auto STATUS_WORKING = 0;
constexpr auto STATUS_STOPPED = 2;

#endif //QT_WEB_SEARCH_UTILS_H
