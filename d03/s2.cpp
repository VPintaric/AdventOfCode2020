#include <iostream>
#include <vector>
#include <sstream>

constexpr char TREE_TILE = '#';
constexpr char OUT_OF_BOUNDS_TILE = ' ';

const std::vector< std::pair< int, int>> slopes = {
    std::make_pair( 1, 1 ),
    std::make_pair( 3, 1 ),
    std::make_pair( 5, 1 ),
    std::make_pair( 7, 1 ),
    std::make_pair( 1, 2 ),
};

struct Grid {
    std::vector< std::string > grid;

    const char getTile( int x, int y ) {
        if ( y >= grid.size()) {
            return OUT_OF_BOUNDS_TILE;
        }

        auto &line = grid[ y ];
        return line[ x % line.size() ];
    }
};

Grid loadGrid() {
    Grid grid;

    std::string line;
    while ( std::getline( std::cin, line )) {
        grid.grid.push_back( line );
    }

    return grid;
}

int getTreeCountOnSlope( Grid &grid, int moveX, int moveY ) {
    auto treeCount = 0;
    auto x = moveX, y = moveY;

    while ( true ) {
        auto tile = grid.getTile( x, y );
        if ( tile == TREE_TILE ) {
            treeCount++;
        } else if ( tile == OUT_OF_BOUNDS_TILE ) {
            break;
        }

        x += moveX;
        y += moveY;
    }
    return treeCount;
}


int main() {
    auto grid = loadGrid();

    long treeCountMultiplied = 1;

    for ( auto &slope : slopes ) {
        auto treeCount = getTreeCountOnSlope( grid, slope.first, slope.second );
        std::cout << treeCount << std::endl;

        treeCountMultiplied *= treeCount;
    }

    std::cout << treeCountMultiplied << std::endl;

    return 0;
}
