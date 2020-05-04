#include <QString>
#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "url_searcher.h"
//
//void test_web_page_search_algo() {
//    QString page = "A b A";
//    QString needle = "b";
//    auto res = url_searcher::find_keyword(page, needle);
//}



unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}
