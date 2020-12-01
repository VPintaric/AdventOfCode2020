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

    for ( auto[firstEntry, _] : entries ) {
        entries[ firstEntry ]--;
        
        auto expectedRestOfSum = expectedSum - firstEntry;

        for ( auto[secondEntry, _] : entries ) {
            entries[ secondEntry ]--;
            
            auto expectedThirdEntry = expectedRestOfSum - secondEntry;

            auto iter = entries.find( expectedThirdEntry );
            if ( iter != entries.end() && iter->second > 0 ) {
                std::printf( "%d\n", firstEntry * secondEntry * iter->first );
                return 0;
            }

            entries[ secondEntry ]++;
        }
        entries[ firstEntry ]++;
    }

    return 0;
}
