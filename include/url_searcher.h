#pragma once

#include <string>
#include <QString>

class url_searcher{
public:
    static std::string find_keyword(const QString& pageHtml, const QString& keyword);
    static std::vector<std::string> get_urls_from_page(const QString& pageHtml);
};
