#include <iostream>
#include <fstream>
#include <set>

int countAnswers( std::istream &input ) {
    int sum = 0;

    std::set< char > groupAnswers;
    std::string line;
    while ( std::getline( input, line )) {
        if ( line.empty()) {
            sum += groupAnswers.size();
            groupAnswers.clear();
            continue;
        }

        for ( auto c : line ) {
            groupAnswers.insert( c );
        }
    }

    return static_cast<int>(sum + groupAnswers.size());
}

int main() {
    std::ifstream infile( "in.txt" );

    auto sum = countAnswers( infile );

    std::cout << sum << std::endl;

    return 0;
}
