#pragma once
#include <QString>
#include <vector>

class url_searcher{
public:
    static QString find_keyword(const QString& pageHtml, const QString& keyword);
    static std::vector<QString> get_urls_from_page(const QString& pageHtml);
};
