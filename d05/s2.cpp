#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

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

    std::vector< int > takenSeats;

    for ( auto &pass : boardingPasses ) {
        auto seat = findSeat( pass );

        auto seatId = seat.first * 8 + seat.second;
        takenSeats.push_back( seatId );
    }

    std::sort( takenSeats.begin(), takenSeats.end());

    for ( int i = 0; i < takenSeats.size() - 1; i++ ) {
        if ( takenSeats[ i + 1 ] == takenSeats[ i ] + 2 ) {
            auto possibleSeat = takenSeats[ i ] + 1;
            if ( 8 <= possibleSeat && possibleSeat <= ( 127 * 8 - 1 )) {
                std::cout << possibleSeat << std::endl;
                return 0;
            }
        }
    }

    return 0;
}
