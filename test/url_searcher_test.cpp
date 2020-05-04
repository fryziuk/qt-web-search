#include <QString>
#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "url_searcher.h"

static constexpr auto keyword_found = "Found";
static constexpr auto keyword_not_found = "Not found";

TEST_CASE("Basic search test", "[find_keyword]")
{
    {
        QString page = "A b A";
        QString needle = "b";
        auto res = url_searcher::find_keyword(page, needle);
        REQUIRE(res == keyword_found);
    }
    {
        QString page = "A b A";
        QString needle = "c";
        auto res = url_searcher::find_keyword(page, needle);
        REQUIRE(res == keyword_not_found);
    }

    {
        QString page = "A b A";
        QString needle = "ba";
        auto res = url_searcher::find_keyword(page, needle);
        REQUIRE(res == keyword_not_found);
    }
}

TEST_CASE("Html search test", "[find_keyword]")
{
    QString page = "<!DOCTYPE html>\n"
                   "<html>\n"
                   "<body>\n"
                   "\n"
                   "<h1>My First Heading</h1>\n"
                   "\n"
                   "<p>My first paragraph.</p>\n"
                   "\n"
                   "</body>\n"
                   "</html>\n"
                   "";
    {

        QString needle = "first";
        auto res = url_searcher::find_keyword(page, needle);
        REQUIRE(res == keyword_found);
    }
    {
        QString needle = "firstt";
        auto res = url_searcher::find_keyword(page, needle);
        REQUIRE(res == keyword_not_found);
    }
}
TEST_CASE("Html search URLS no URLS", "[get_urls_from_page]")
{
    QString page = "<!DOCTYPE html>\n"
                   "<html>\n"
                   "<body>\n"
                   "\n"
                   "<h1>My First Heading</h1>\n"
                   "\n"
                   "<p>My first http paragraph.</p>\n"
                   "\n"
                   "</body>\n"
                   "</html>\n"
                   "";
    {
        auto res = url_searcher::get_urls_from_page(page);
        REQUIRE(res.size() == 0);
    }
}

// Probably not good idea to add this one to unittest
TEST_CASE("Html search URLS", "[get_urls_from_page]")
{
    QString page = "<!DOCTYPE html>\n"
                   "<html>\n"
                   "<body>\n"
                   "<a href=\"https://www.w3schools.com\">Visit W3Schools.com!</a>\n"
                   "<a href=\"https://www.google.com\">google</a>\n"
                   "<a href=\"https://www.facebook.com\">facebook</a>\n"
                   "\n"
                   "<h1>My First Heading</h1>\n"
                   "\n"
                   "<p>My first paragraph.</p>\n"
                   "\n"
                   "</body>\n"
                   "</html>\n"
                   "";
    {
        auto res = url_searcher::get_urls_from_page(page);
        REQUIRE(res.size() == 3);
        REQUIRE(res[0] == "https://www.w3schools.com");
        REQUIRE(res[1] == "https://www.google.com");
        REQUIRE(res[2] == "https://www.facebook.com");
    }
}
