#include <iostream>
#include <vector>
#include <fstream>

std::vector< std::string > loadBoardingPasses( std::istream &input ) {
    std::vector< std::string > boardingPasses;

    std::string line;
    while ( std::getline( input, line )) {
        boardingPasses.push_back( line );
    }

    return boardingPasses;
}

std::pair< int, int > findSeat( const std::string &pass ) {
    int loRow = 0, hiRow = 127;

    for ( int i = 0; i < 7; ++i ) {
        int mid = ( loRow + hiRow ) / 2;

        if ( pass[ i ] == 'F' ) {
            hiRow = mid;
        } else {
            loRow = mid + 1;
        }
    }

    int loCol = 0, hiCol = 7;
    for ( int i = 7; i < 10; ++i ) {
        int mid = ( loCol + hiCol ) / 2;

        if ( pass[ i ] == 'L' ) {
            hiCol = mid;
        } else {
            loCol = mid + 1;
        }
    }

    return std::make_pair( loRow, loCol );
}

int main() {
    std::ifstream infile( "in.txt" );

    auto boardingPasses = loadBoardingPasses( infile );

    int maxId = 0;
    for ( auto &pass : boardingPasses ) {
        auto seat = findSeat( pass );

        auto seatId = seat.first * 8 + seat.second;

        maxId = std::max( seatId, maxId );
    }

    std::cout << maxId << std::endl;

    return 0;
}
