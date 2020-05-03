#pragma once
#include <QString>
#include <string>

class downloader {
public:
    static QString download_page(const std::string& url);
};