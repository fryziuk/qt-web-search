#include "url_searcher.h"
#include "utils.h"
#include "profile.h"
#include <QRegularExpression>
#include <vector>


std::string url_searcher::find_keyword(const QString& pageHtml, const QString& keyword) {
    LOG_DURATION("Find keyword");
    if (pageHtml.contains(keyword)) {
        return keyword_found;
    } else {
        return keyword_not_found;
    }
}

std::vector<std::string> url_searcher::get_urls_from_page(const QString& pageHtml) {
    std::vector<std::string> result;
    LOG_DURATION("Add URLs to queue");
    QRegularExpression url_reg_exp("http[s]?:\\/\\/?[^\\s([\"<,>]*\\.[^\\s[\",><]*");
    QRegularExpressionMatchIterator i = url_reg_exp.globalMatch(pageHtml);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch()) {
            result.push_back(match.captured(0).toStdString());
        }
    }
    return result;
}
