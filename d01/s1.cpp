#include <cstdio>
#include <iostream>
#include <map>

std::map< int, int > loadEntries() {
    std::map< int, int > entries;

    int entry;
    while ( std::cin >> entry ) {
        entries[ entry ]++;
    }

    return entries;
}

int main() {
    constexpr int expectedSum = 2020;

    auto entries = loadEntries();

    for ( auto[entry, _] : entries ) {

        entries[ entry ]--;
        auto expectedOtherEntry = expectedSum - entry;

        auto iter = entries.find( expectedOtherEntry );
        if ( iter != entries.end() && iter->second > 0 ) {
            std::printf( "%d\n", entry * expectedOtherEntry );
            return 0;
        }

        entries[ entry ]++;
    }

    return 0;
}
