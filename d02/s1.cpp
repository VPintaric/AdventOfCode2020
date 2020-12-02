#include <iostream>
#include <vector>
#include <sstream>

struct Entry {
    int policyFirstPlace{}, policySecondPlace{};
    char policyLetter{};
    std::string password;
};

std::vector< Entry > loadEntries() {
    std::vector< Entry > entries;

    std::string line;
    while ( std::getline( std::cin, line )) {
        std::istringstream iss( line );

        Entry entry;
        iss >> entry.policyFirstPlace;
        iss.ignore(); // ignore dash
        iss >> entry.policySecondPlace;
        iss >> entry.policyLetter;
        iss.ignore(); // ignore colon
        iss >> entry.password;

        entries.push_back( entry );
    }

    return entries;
}

bool isValid( Entry &entry ) {
    int letterCount = 0;

    for ( auto c : entry.password ) {
        if ( c == entry.policyLetter ) {
            letterCount++;
        }
    }

    return entry.policyFirstPlace <= letterCount && letterCount <= entry.policySecondPlace;
}

int main() {
    auto entries = loadEntries();

    int validCount = 0;
    for ( auto &entry : entries ) {
        if ( isValid( entry )) {
            validCount++;
        }
    }

    std::cout << validCount << std::endl;

    return 0;
}
