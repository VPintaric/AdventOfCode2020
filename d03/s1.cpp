#include <iostream>
#include <vector>
#include <sstream>

constexpr char TREE_TILE = '#';
constexpr char OUT_OF_BOUNDS_TILE = ' ';

constexpr int MOVE_X = 3;
constexpr int MOVE_Y = 1;

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

        x += MOVE_X;
        y += MOVE_Y;
    }
    return treeCount;
}


int main() {
    auto grid = loadGrid();


    int treeCount = getTreeCountOnSlope( grid, MOVE_X, MOVE_Y );

    std::cout << treeCount << std::endl;

    return 0;
}
