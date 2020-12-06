#include <iostream>
#include <fstream>
#include <map>

int countAnswers( std::istream &input ) {
    int sum = 0;

    std::map< char, int > groupAnswers;
    int groupMembersCount = 0;
    std::string line;
    while ( std::getline( input, line )) {
        if ( line.empty()) {
            for ( auto[_, answersCount] : groupAnswers ) {
                if ( answersCount == groupMembersCount ) {
                    sum++;
                }
            }

            groupAnswers.clear();
            groupMembersCount = 0;
            continue;
        }

        groupMembersCount++;
        for ( auto c : line ) {
            groupAnswers[ c ]++;
        }
    }

    for ( auto[_, answersCount] : groupAnswers ) {
        if ( answersCount == groupMembersCount ) {
            sum++;
        }
    }

    return sum;
}

int main() {
    std::ifstream infile( "in.txt" );

    auto sum = countAnswers( infile );

    std::cout << sum << std::endl;

    return 0;
}
