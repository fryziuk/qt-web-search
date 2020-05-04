#include "url_searcher.h"
#include "profile.h"
#include <QRegularExpression>
#include <vector>

static constexpr auto keyword_found = "Found";
static constexpr auto keyword_not_found = "Not found";

QString url_searcher::find_keyword(const QString& pageHtml, const QString& keyword) {
    LOG_DURATION("Find keyword");
    if (pageHtml.contains(keyword)) {
        return keyword_found;
    } else {
        return keyword_not_found;
    }
}

std::vector<QString> url_searcher::get_urls_from_page(const QString& pageHtml) {
    std::vector<QString> result;
    //LOG_DURATION("Add URLs to queue");
    QRegularExpression url_reg_exp("http[s]?:\\/\\/?[^\\s([\"<,>]*\\.[^\\s[\",><]*");
    QRegularExpressionMatchIterator i = url_reg_exp.globalMatch(pageHtml);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch()) {
            result.push_back(match.captured(0));
        }
    }
    return result;
}
